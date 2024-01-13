#include "../support/NativeImplServer.h"
#include "Windowing.h"

ni_InterfaceMethodRef iWindowDelegate_canClose;
ni_InterfaceMethodRef iWindowDelegate_closed;
ni_InterfaceMethodRef iWindowDelegate_destroyed;
ni_InterfaceMethodRef iWindowDelegate_mouseDown;
ni_InterfaceMethodRef iWindowDelegate_repaint;
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

inline void Modifiers__push(Modifiers value) {
    ni_pushInt32((int32_t)value);
}

inline Modifiers Modifiers__pop() {
    auto tag = ni_popInt32();
    return (Modifiers)tag;
}

void __ModifiersSet__push(std::set<Modifiers> values, bool isReturn) {
    std::vector<int8_t> intValues;
    for (auto i = values.begin(); i != values.end(); i++) {
        intValues.push_back((int8_t)*i);
    }
    pushInt8ArrayInternal(intValues);
}

std::set<Modifiers> __ModifiersSet__pop() {
    auto intValues = popInt8ArrayInternal();
    std::set<Modifiers> __ret;
    for (auto i = intValues.begin(); i != intValues.end(); i++) {
        __ret.insert((Modifiers)*i);
    }
    return __ret;
}

void CGContext__push(std::shared_ptr<CGContext> thing, bool isReturn);
std::shared_ptr<CGContext> CGContext__pop();

class ClientIWindowDelegate : public ClientObject, public IWindowDelegate {
public:
    ClientIWindowDelegate(int id) : ClientObject(id) {}
    bool canClose() override {
        invokeMethod(iWindowDelegate_canClose);
        return ni_popBool();
    }
    void closed() override {
        invokeMethod(iWindowDelegate_closed);
    }
    void destroyed() override {
        invokeMethod(iWindowDelegate_destroyed);
    }
    void mouseDown(int32_t x, int32_t y, MouseButton button, std::set<Modifiers> modifiers) override {
        __ModifiersSet__push(modifiers, false);
        MouseButton__push(button);
        ni_pushInt32(y);
        ni_pushInt32(x);
        invokeMethod(iWindowDelegate_mouseDown);
    }
    void repaint(std::shared_ptr<CGContext> context, int32_t x, int32_t y, int32_t width, int32_t height) override {
        ni_pushInt32(height);
        ni_pushInt32(width);
        ni_pushInt32(y);
        ni_pushInt32(x);
        CGContext__push(context, false);
        invokeMethod(iWindowDelegate_repaint);
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

inline void PropFlags__push(uint32_t value) {
    ni_pushUInt32(value);
}

inline uint32_t PropFlags__pop() {
    return ni_popUInt32();
}

inline void WindowStyle__push(WindowStyle value) {
    ni_pushInt32((int32_t)value);
}

inline WindowStyle WindowStyle__pop() {
    auto tag = ni_popInt32();
    return (WindowStyle)tag;
}

void WindowProperties__push(WindowProperties value, bool isReturn) {
    WindowStyle__push(value.style);
    ni_pushInt32(value.maxHeight);
    ni_pushInt32(value.maxWidth);
    ni_pushInt32(value.minHeight);
    ni_pushInt32(value.minWidth);
    PropFlags__push(value.usedFields);
}

WindowProperties WindowProperties__pop() {
    auto usedFields = PropFlags__pop();
    auto minWidth = ni_popInt32();
    auto minHeight = ni_popInt32();
    auto maxWidth = ni_popInt32();
    auto maxHeight = ni_popInt32();
    auto style = WindowStyle__pop();
    return WindowProperties { usedFields, minWidth, minHeight, maxWidth, maxHeight, style };
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
    auto props = WindowProperties__pop();
    IWindow__push(createWindow(width, height, title, del, props), true);
}

void IWindowDelegate_canClose__wrapper(int serverID) {
    auto inst = ServerIWindowDelegate::getByID(serverID);
    ni_pushBool(inst->canClose());
}

void IWindowDelegate_closed__wrapper(int serverID) {
    auto inst = ServerIWindowDelegate::getByID(serverID);
    inst->closed();
}

void IWindowDelegate_destroyed__wrapper(int serverID) {
    auto inst = ServerIWindowDelegate::getByID(serverID);
    inst->destroyed();
}

void IWindowDelegate_mouseDown__wrapper(int serverID) {
    auto inst = ServerIWindowDelegate::getByID(serverID);
    auto x = ni_popInt32();
    auto y = ni_popInt32();
    auto button = MouseButton__pop();
    auto modifiers = __ModifiersSet__pop();
    inst->mouseDown(x, y, button, modifiers);
}

void IWindowDelegate_repaint__wrapper(int serverID) {
    auto inst = ServerIWindowDelegate::getByID(serverID);
    auto context = CGContext__pop();
    auto x = ni_popInt32();
    auto y = ni_popInt32();
    auto width = ni_popInt32();
    auto height = ni_popInt32();
    inst->repaint(context, x, y, width, height);
}

void IWindow_show__wrapper(int serverID) {
    auto inst = ServerIWindow::getByID(serverID);
    inst->show();
}

void IWindow_destroy__wrapper(int serverID) {
    auto inst = ServerIWindow::getByID(serverID);
    inst->destroy();
}

int Windowing__init() {
    auto m = ni_registerModule("Windowing");
    ni_registerModuleMethod(m, "moduleInit", &moduleInit__wrapper);
    ni_registerModuleMethod(m, "moduleShutdown", &moduleShutdown__wrapper);
    ni_registerModuleMethod(m, "runloop", &runloop__wrapper);
    ni_registerModuleMethod(m, "exitRunloop", &exitRunloop__wrapper);
    ni_registerModuleMethod(m, "createWindow", &createWindow__wrapper);
    auto iWindowDelegate = ni_registerInterface(m, "IWindowDelegate");
    iWindowDelegate_canClose = ni_registerInterfaceMethod(iWindowDelegate, "canClose", &IWindowDelegate_canClose__wrapper);
    iWindowDelegate_closed = ni_registerInterfaceMethod(iWindowDelegate, "closed", &IWindowDelegate_closed__wrapper);
    iWindowDelegate_destroyed = ni_registerInterfaceMethod(iWindowDelegate, "destroyed", &IWindowDelegate_destroyed__wrapper);
    iWindowDelegate_mouseDown = ni_registerInterfaceMethod(iWindowDelegate, "mouseDown", &IWindowDelegate_mouseDown__wrapper);
    iWindowDelegate_repaint = ni_registerInterfaceMethod(iWindowDelegate, "repaint", &IWindowDelegate_repaint__wrapper);
    auto iWindow = ni_registerInterface(m, "IWindow");
    iWindow_show = ni_registerInterfaceMethod(iWindow, "show", &IWindow_show__wrapper);
    iWindow_destroy = ni_registerInterfaceMethod(iWindow, "destroy", &IWindow_destroy__wrapper);
    return 0; // = OK
}

void Windowing__shutdown() {
}
