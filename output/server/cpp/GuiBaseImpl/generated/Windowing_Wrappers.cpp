#include "../support/NativeImplServer.h"
#include "Windowing.h"

ni_InterfaceMethodRef windowDelegate_buttonClicked;
ni_InterfaceMethodRef windowDelegate_closed;
ni_InterfaceMethodRef window_show;
ni_InterfaceMethodRef window_destroy;

inline void MouseButton__push(MouseButton value) {
    ni_pushInt32((int32_t)value);
}

inline MouseButton MouseButton__pop() {
    auto tag = ni_popInt32();
    return (MouseButton)tag;
}

class ClientWindow : public ClientObject, public Window {
public:
    ClientWindow(int id) : ClientObject(id) {}
    void show() override {
        invokeMethod(window_show);
    }
    void destroy() override {
        invokeMethod(window_destroy);
    }
};

void Window__push(std::shared_ptr<Window> inst, bool isReturn) {
    if (inst != nullptr) {
        auto pushable = std::dynamic_pointer_cast<Pushable>(inst);
        pushable->push(pushable, isReturn);
    }
    else {
        ni_pushNull();
    }
}

std::shared_ptr<Window> Window__pop()
{
    bool isClientID;
    auto id = ni_popInstance(&isClientID);
    if (id != 0) {
        if (isClientID) {
            return std::shared_ptr<Window>(new ClientWindow(id));
        }
        else {
            return ServerWindow::getByID(id);
        }
    }
    else {
        return std::shared_ptr<Window>();
    }
}

class ClientWindowDelegate : public ClientObject, public WindowDelegate {
public:
    ClientWindowDelegate(int id) : ClientObject(id) {}
    void buttonClicked(int32_t x, int32_t y, MouseButton button) override {
        MouseButton__push(button);
        ni_pushInt32(y);
        ni_pushInt32(x);
        invokeMethod(windowDelegate_buttonClicked);
    }
    void closed() override {
        invokeMethod(windowDelegate_closed);
    }
};

void WindowDelegate__push(std::shared_ptr<WindowDelegate> inst, bool isReturn) {
    if (inst != nullptr) {
        auto pushable = std::dynamic_pointer_cast<Pushable>(inst);
        pushable->push(pushable, isReturn);
    }
    else {
        ni_pushNull();
    }
}

std::shared_ptr<WindowDelegate> WindowDelegate__pop()
{
    bool isClientID;
    auto id = ni_popInstance(&isClientID);
    if (id != 0) {
        if (isClientID) {
            return std::shared_ptr<WindowDelegate>(new ClientWindowDelegate(id));
        }
        else {
            return ServerWindowDelegate::getByID(id);
        }
    }
    else {
        return std::shared_ptr<WindowDelegate>();
    }
}

void moduleInit__wrapper() {
    moduleInit();
}

void moduleShutdown__wrapper() {
    moduleShutdown();
}

void runloop__wrapper() {
    runloop();
}

void exitRunloop__wrapper() {
    exitRunloop();
}

void createWindow__wrapper() {
    auto width = ni_popInt32();
    auto height = ni_popInt32();
    auto title = popStringInternal();
    auto del = WindowDelegate__pop();
    Window__push(createWindow(width, height, title, del), true);
}

void WindowDelegate_buttonClicked__wrapper(int serverID) {
    auto inst = ServerWindowDelegate::getByID(serverID);
    auto x = ni_popInt32();
    auto y = ni_popInt32();
    auto button = MouseButton__pop();
    inst->buttonClicked(x, y, button);
}

void WindowDelegate_closed__wrapper(int serverID) {
    auto inst = ServerWindowDelegate::getByID(serverID);
    inst->closed();
}

void Window_show__wrapper(int serverID) {
    auto inst = ServerWindow::getByID(serverID);
    inst->show();
}

void Window_destroy__wrapper(int serverID) {
    auto inst = ServerWindow::getByID(serverID);
    inst->destroy();
}

extern "C" int nativeLibraryInit() {
    auto m = ni_registerModule("Windowing");
    ni_registerModuleMethod(m, "moduleInit", &moduleInit__wrapper);
    ni_registerModuleMethod(m, "moduleShutdown", &moduleShutdown__wrapper);
    ni_registerModuleMethod(m, "runloop", &runloop__wrapper);
    ni_registerModuleMethod(m, "exitRunloop", &exitRunloop__wrapper);
    ni_registerModuleMethod(m, "createWindow", &createWindow__wrapper);
    auto windowDelegate = ni_registerInterface(m, "WindowDelegate");
    windowDelegate_buttonClicked = ni_registerInterfaceMethod(windowDelegate, "buttonClicked", &WindowDelegate_buttonClicked__wrapper);
    windowDelegate_closed = ni_registerInterfaceMethod(windowDelegate, "closed", &WindowDelegate_closed__wrapper);
    auto window = ni_registerInterface(m, "Window");
    window_show = ni_registerInterfaceMethod(window, "show", &Window_show__wrapper);
    window_destroy = ni_registerInterfaceMethod(window, "destroy", &Window_destroy__wrapper);
    return 0; // = OK
}

extern "C" void nativeLibraryShutdown() {
}
