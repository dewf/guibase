#include "../support/NativeImplServer.h"
#include "Windowing.h"

ni_InterfaceMethodRef iWindowDelegate_buttonClicked;
ni_InterfaceMethodRef iWindowDelegate_closed;
ni_InterfaceMethodRef iWindow_show;
ni_InterfaceMethodRef iWindow_destroy;

class ClientIWindow : public ClientObject, public IWindow {
public:
    ClientIWindow(int id) : ClientObject(id) {}
    void show() override {
        invokeMethod(iWindow_show);
    }
    void destroy() override {
        invokeMethod(iWindow_destroy);
    }
};

void IWindow__push(std::shared_ptr<IWindow> inst, bool isReturn) {
    if (inst != nullptr) {
        auto pushable = std::dynamic_pointer_cast<Pushable>(inst);
        pushable->push(pushable, isReturn);
    }
    else {
        ni_pushNull();
    }
}

std::shared_ptr<IWindow> IWindow__pop()
{
    bool isClientID;
    auto id = ni_popInstance(&isClientID);
    if (id != 0) {
        if (isClientID) {
            return std::shared_ptr<IWindow>(new ClientIWindow(id));
        }
        else {
            return ServerIWindow::getByID(id);
        }
    }
    else {
        return std::shared_ptr<IWindow>();
    }
}

inline void MouseButton__push(MouseButton value) {
    ni_pushInt32((int32_t)value);
}

inline MouseButton MouseButton__pop() {
    auto tag = ni_popInt32();
    return (MouseButton)tag;
}

class ClientIWindowDelegate : public ClientObject, public IWindowDelegate {
public:
    ClientIWindowDelegate(int id) : ClientObject(id) {}
    void buttonClicked(int32_t x, int32_t y, MouseButton button) override {
        MouseButton__push(button);
        ni_pushInt32(y);
        ni_pushInt32(x);
        invokeMethod(iWindowDelegate_buttonClicked);
    }
    void closed() override {
        invokeMethod(iWindowDelegate_closed);
    }
};

void IWindowDelegate__push(std::shared_ptr<IWindowDelegate> inst, bool isReturn) {
    if (inst != nullptr) {
        auto pushable = std::dynamic_pointer_cast<Pushable>(inst);
        pushable->push(pushable, isReturn);
    }
    else {
        ni_pushNull();
    }
}

std::shared_ptr<IWindowDelegate> IWindowDelegate__pop()
{
    bool isClientID;
    auto id = ni_popInstance(&isClientID);
    if (id != 0) {
        if (isClientID) {
            return std::shared_ptr<IWindowDelegate>(new ClientIWindowDelegate(id));
        }
        else {
            return ServerIWindowDelegate::getByID(id);
        }
    }
    else {
        return std::shared_ptr<IWindowDelegate>();
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
    auto del = IWindowDelegate__pop();
    IWindow__push(createWindow(width, height, title, del), true);
}

void IWindowDelegate_buttonClicked__wrapper(int serverID) {
    auto inst = ServerIWindowDelegate::getByID(serverID);
    auto x = ni_popInt32();
    auto y = ni_popInt32();
    auto button = MouseButton__pop();
    inst->buttonClicked(x, y, button);
}

void IWindowDelegate_closed__wrapper(int serverID) {
    auto inst = ServerIWindowDelegate::getByID(serverID);
    inst->closed();
}

void IWindow_show__wrapper(int serverID) {
    auto inst = ServerIWindow::getByID(serverID);
    inst->show();
}

void IWindow_destroy__wrapper(int serverID) {
    auto inst = ServerIWindow::getByID(serverID);
    inst->destroy();
}

extern "C" int nativeLibraryInit() {
    auto m = ni_registerModule("Windowing");
    ni_registerModuleMethod(m, "moduleInit", &moduleInit__wrapper);
    ni_registerModuleMethod(m, "moduleShutdown", &moduleShutdown__wrapper);
    ni_registerModuleMethod(m, "runloop", &runloop__wrapper);
    ni_registerModuleMethod(m, "exitRunloop", &exitRunloop__wrapper);
    ni_registerModuleMethod(m, "createWindow", &createWindow__wrapper);
    auto iWindowDelegate = ni_registerInterface(m, "IWindowDelegate");
    iWindowDelegate_buttonClicked = ni_registerInterfaceMethod(iWindowDelegate, "buttonClicked", &IWindowDelegate_buttonClicked__wrapper);
    iWindowDelegate_closed = ni_registerInterfaceMethod(iWindowDelegate, "closed", &IWindowDelegate_closed__wrapper);
    auto iWindow = ni_registerInterface(m, "IWindow");
    iWindow_show = ni_registerInterfaceMethod(iWindow, "show", &IWindow_show__wrapper);
    iWindow_destroy = ni_registerInterfaceMethod(iWindow, "destroy", &IWindow_destroy__wrapper);
    return 0; // = OK
}

extern "C" void nativeLibraryShutdown() {
}
