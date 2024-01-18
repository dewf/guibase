#include "../support/NativeImplServer.h"
#include "Windowing_wrappers.h"
#include "Windowing.h"
#include "Drawing_wrappers.h"

ni_InterfaceMethodRef windowDelegate_canClose;
ni_InterfaceMethodRef windowDelegate_closed;
ni_InterfaceMethodRef windowDelegate_destroyed;
ni_InterfaceMethodRef windowDelegate_mouseDown;
ni_InterfaceMethodRef windowDelegate_repaint;
ni_InterfaceMethodRef windowDelegate_resized;
NIHANDLE(window);

inline void Modifiers__push(Modifiers value) {
    ni_pushInt32((int32_t)value);
}

inline Modifiers Modifiers__pop() {
    auto tag = ni_popInt32();
    return (Modifiers)tag;
}

inline void MouseButton__push(MouseButton value) {
    ni_pushInt32((int32_t)value);
}

inline MouseButton MouseButton__pop() {
    auto tag = ni_popInt32();
    return (MouseButton)tag;
}

void Window__push(Window value) {
    ni_pushPtr(value);
}

Window Window__pop() {
    return (Window)ni_popPtr();
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

class ClientWindowDelegate : public ClientObject, public WindowDelegate {
public:
    ClientWindowDelegate(int id) : ClientObject(id) {}
    bool canClose() override {
        invokeMethod(windowDelegate_canClose);
        return ni_popBool();
    }
    void closed() override {
        invokeMethod(windowDelegate_closed);
    }
    void destroyed() override {
        invokeMethod(windowDelegate_destroyed);
    }
    void mouseDown(int32_t x, int32_t y, MouseButton button, std::set<Modifiers> modifiers) override {
        __ModifiersSet__push(modifiers, false);
        MouseButton__push(button);
        ni_pushInt32(y);
        ni_pushInt32(x);
        invokeMethod(windowDelegate_mouseDown);
    }
    void repaint(DrawContext context, int32_t x, int32_t y, int32_t width, int32_t height) override {
        ni_pushInt32(height);
        ni_pushInt32(width);
        ni_pushInt32(y);
        ni_pushInt32(x);
        DrawContext__push(context);
        invokeMethod(windowDelegate_repaint);
    }
    void resized(int32_t width, int32_t height) override {
        ni_pushInt32(height);
        ni_pushInt32(width);
        invokeMethod(windowDelegate_resized);
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

std::shared_ptr<WindowDelegate> WindowDelegate__pop() {
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

inline void WindowStyle__push(WindowStyle value) {
    ni_pushInt32((int32_t)value);
}

inline WindowStyle WindowStyle__pop() {
    auto tag = ni_popInt32();
    return (WindowStyle)tag;
}

void WindowOptions__push(WindowOptions value, bool isReturn) {
    size_t nativeParent;
    if (value.hasNativeParent(&nativeParent)) {
        ni_pushSizeT(nativeParent);
    }
    WindowStyle style;
    if (value.hasStyle(&style)) {
        WindowStyle__push(style);
    }
    int32_t maxHeight;
    if (value.hasMaxHeight(&maxHeight)) {
        ni_pushInt32(maxHeight);
    }
    int32_t maxWidth;
    if (value.hasMaxWidth(&maxWidth)) {
        ni_pushInt32(maxWidth);
    }
    int32_t minHeight;
    if (value.hasMinHeight(&minHeight)) {
        ni_pushInt32(minHeight);
    }
    int32_t minWidth;
    if (value.hasMinWidth(&minWidth)) {
        ni_pushInt32(minWidth);
    }
    ni_pushInt32(value.getUsedFields());
}

WindowOptions WindowOptions__pop() {
    WindowOptions value = {};
    value._usedFields =  ni_popInt32();
    if (value._usedFields & WindowOptions::Fields::MinWidth) {
        auto x = ni_popInt32();
        value.setMinWidth(x);
    }
    if (value._usedFields & WindowOptions::Fields::MinHeight) {
        auto x = ni_popInt32();
        value.setMinHeight(x);
    }
    if (value._usedFields & WindowOptions::Fields::MaxWidth) {
        auto x = ni_popInt32();
        value.setMaxWidth(x);
    }
    if (value._usedFields & WindowOptions::Fields::MaxHeight) {
        auto x = ni_popInt32();
        value.setMaxHeight(x);
    }
    if (value._usedFields & WindowOptions::Fields::Style) {
        auto x = WindowStyle__pop();
        value.setStyle(x);
    }
    if (value._usedFields & WindowOptions::Fields::NativeParent) {
        auto x = ni_popSizeT();
        value.setNativeParent(x);
    }
    return value;
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
    auto opts = WindowOptions__pop();
    Window__push(createWindow(width, height, title, del, opts));
}

void Window_show__wrapper() {
    auto _this = Window__pop();
    Window_show(_this);
}

void Window_destroy__wrapper() {
    auto _this = Window__pop();
    Window_destroy(_this);
}

void WindowDelegate_canClose__wrapper(int serverID) {
    auto inst = ServerWindowDelegate::getByID(serverID);
    ni_pushBool(inst->canClose());
}

void WindowDelegate_closed__wrapper(int serverID) {
    auto inst = ServerWindowDelegate::getByID(serverID);
    inst->closed();
}

void WindowDelegate_destroyed__wrapper(int serverID) {
    auto inst = ServerWindowDelegate::getByID(serverID);
    inst->destroyed();
}

void WindowDelegate_mouseDown__wrapper(int serverID) {
    auto inst = ServerWindowDelegate::getByID(serverID);
    auto x = ni_popInt32();
    auto y = ni_popInt32();
    auto button = MouseButton__pop();
    auto modifiers = __ModifiersSet__pop();
    inst->mouseDown(x, y, button, modifiers);
}

void WindowDelegate_repaint__wrapper(int serverID) {
    auto inst = ServerWindowDelegate::getByID(serverID);
    auto context = DrawContext__pop();
    auto x = ni_popInt32();
    auto y = ni_popInt32();
    auto width = ni_popInt32();
    auto height = ni_popInt32();
    inst->repaint(context, x, y, width, height);
}

void WindowDelegate_resized__wrapper(int serverID) {
    auto inst = ServerWindowDelegate::getByID(serverID);
    auto width = ni_popInt32();
    auto height = ni_popInt32();
    inst->resized(width, height);
}

int Windowing__register() {
    auto m = ni_registerModule("Windowing");
    ni_registerModuleMethod(m, "moduleInit", &moduleInit__wrapper);
    ni_registerModuleMethod(m, "moduleShutdown", &moduleShutdown__wrapper);
    ni_registerModuleMethod(m, "runloop", &runloop__wrapper);
    ni_registerModuleMethod(m, "exitRunloop", &exitRunloop__wrapper);
    ni_registerModuleMethod(m, "createWindow", &createWindow__wrapper);
    ni_registerModuleMethod(m, "Window_show", &Window_show__wrapper);
    ni_registerModuleMethod(m, "Window_destroy", &Window_destroy__wrapper);
    auto windowDelegate = ni_registerInterface(m, "WindowDelegate");
    windowDelegate_canClose = ni_registerInterfaceMethod(windowDelegate, "canClose", &WindowDelegate_canClose__wrapper);
    windowDelegate_closed = ni_registerInterfaceMethod(windowDelegate, "closed", &WindowDelegate_closed__wrapper);
    windowDelegate_destroyed = ni_registerInterfaceMethod(windowDelegate, "destroyed", &WindowDelegate_destroyed__wrapper);
    windowDelegate_mouseDown = ni_registerInterfaceMethod(windowDelegate, "mouseDown", &WindowDelegate_mouseDown__wrapper);
    windowDelegate_repaint = ni_registerInterfaceMethod(windowDelegate, "repaint", &WindowDelegate_repaint__wrapper);
    windowDelegate_resized = ni_registerInterfaceMethod(windowDelegate, "resized", &WindowDelegate_resized__wrapper);
    return 0; // = OK
}
