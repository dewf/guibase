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
NIHANDLE(icon);
NIHANDLE(accelerator);
NIHANDLE(action);
NIHANDLE(menuItem);
NIHANDLE(menu);
NIHANDLE(menuBar);

void Accelerator__push(Accelerator value) {
    ni_pushPtr(value);
}

Accelerator Accelerator__pop() {
    return (Accelerator)ni_popPtr();
}

void Action__push(Action value) {
    ni_pushPtr(value);
}

Action Action__pop() {
    return (Action)ni_popPtr();
}

void Icon__push(Icon value) {
    ni_pushPtr(value);
}

Icon Icon__pop() {
    return (Icon)ni_popPtr();
}

inline void Key__push(Key value) {
    ni_pushInt32((int32_t)value);
}

inline Key Key__pop() {
    auto tag = ni_popInt32();
    return (Key)tag;
}

void Menu__push(Menu value) {
    ni_pushPtr(value);
}

Menu Menu__pop() {
    return (Menu)ni_popPtr();
}

void MenuActionFunc__push(std::function<MenuActionFunc> f) {
    size_t uniqueKey = 0;
    if (f) {
        MenuActionFunc* ptr_fun = f.target<MenuActionFunc>();
        if (ptr_fun != nullptr) {
            uniqueKey = (size_t)ptr_fun;
        }
    }
    auto wrapper = [f]() {
        f();
    };
    pushServerFuncVal(wrapper, uniqueKey);
}

std::function<MenuActionFunc> MenuActionFunc__pop() {
    auto id = ni_popClientFunc();
    auto cf = std::shared_ptr<ClientFuncVal>(new ClientFuncVal(id));
    auto wrapper = [cf]() {
        cf->remoteExec();
    };
    return wrapper;
}

void MenuBar__push(MenuBar value) {
    ni_pushPtr(value);
}

MenuBar MenuBar__pop() {
    return (MenuBar)ni_popPtr();
}

void MenuItem__push(MenuItem value) {
    ni_pushPtr(value);
}

MenuItem MenuItem__pop() {
    return (MenuItem)ni_popPtr();
}

inline void Modifiers__push(uint32_t value) {
    ni_pushUInt32(value);
}

inline uint32_t Modifiers__pop() {
    return ni_popUInt32();
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
    void mouseDown(int32_t x, int32_t y, MouseButton button, uint32_t modifiers) override {
        Modifiers__push(modifiers);
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

void createIcon__wrapper() {
    auto filename = popStringInternal();
    auto sizeToWidth = ni_popInt32();
    Icon__push(createIcon(filename, sizeToWidth));
}

void createAccelerator__wrapper() {
    auto key = Key__pop();
    auto modifiers = Modifiers__pop();
    Accelerator__push(createAccelerator(key, modifiers));
}

void createAction__wrapper() {
    auto label = popStringInternal();
    auto icon = Icon__pop();
    auto accel = Accelerator__pop();
    auto func = MenuActionFunc__pop();
    Action__push(createAction(label, icon, accel, func));
}

void createMenu__wrapper() {
    Menu__push(createMenu());
}

void createMenuBar__wrapper() {
    MenuBar__push(createMenuBar());
}

void Window_show__wrapper() {
    auto _this = Window__pop();
    Window_show(_this);
}

void Window_destroy__wrapper() {
    auto _this = Window__pop();
    Window_destroy(_this);
}

void Window_setMenuBar__wrapper() {
    auto _this = Window__pop();
    auto menuBar = MenuBar__pop();
    Window_setMenuBar(_this, menuBar);
}

void Window_showContextMenu__wrapper() {
    auto _this = Window__pop();
    auto x = ni_popInt32();
    auto y = ni_popInt32();
    auto menu = Menu__pop();
    Window_showContextMenu(_this, x, y, menu);
}

void Window_invalidate__wrapper() {
    auto _this = Window__pop();
    auto x = ni_popInt32();
    auto y = ni_popInt32();
    auto width = ni_popInt32();
    auto height = ni_popInt32();
    Window_invalidate(_this, x, y, width, height);
}

void Menu_addAction__wrapper() {
    auto _this = Menu__pop();
    auto action = Action__pop();
    MenuItem__push(Menu_addAction(_this, action));
}

void Menu_addSubmenu__wrapper() {
    auto _this = Menu__pop();
    auto label = popStringInternal();
    auto sub = Menu__pop();
    MenuItem__push(Menu_addSubmenu(_this, label, sub));
}

void Menu_addSeparator__wrapper() {
    auto _this = Menu__pop();
    Menu_addSeparator(_this);
}

void MenuBar_addMenu__wrapper() {
    auto _this = MenuBar__pop();
    auto label = popStringInternal();
    auto menu = Menu__pop();
    MenuItem__push(MenuBar_addMenu(_this, label, menu));
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
    auto modifiers = Modifiers__pop();
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
    ni_registerModuleMethod(m, "createIcon", &createIcon__wrapper);
    ni_registerModuleMethod(m, "createAccelerator", &createAccelerator__wrapper);
    ni_registerModuleMethod(m, "createAction", &createAction__wrapper);
    ni_registerModuleMethod(m, "createMenu", &createMenu__wrapper);
    ni_registerModuleMethod(m, "createMenuBar", &createMenuBar__wrapper);
    ni_registerModuleMethod(m, "Window_show", &Window_show__wrapper);
    ni_registerModuleMethod(m, "Window_destroy", &Window_destroy__wrapper);
    ni_registerModuleMethod(m, "Window_setMenuBar", &Window_setMenuBar__wrapper);
    ni_registerModuleMethod(m, "Window_showContextMenu", &Window_showContextMenu__wrapper);
    ni_registerModuleMethod(m, "Window_invalidate", &Window_invalidate__wrapper);
    ni_registerModuleMethod(m, "Menu_addAction", &Menu_addAction__wrapper);
    ni_registerModuleMethod(m, "Menu_addSubmenu", &Menu_addSubmenu__wrapper);
    ni_registerModuleMethod(m, "Menu_addSeparator", &Menu_addSeparator__wrapper);
    ni_registerModuleMethod(m, "MenuBar_addMenu", &MenuBar_addMenu__wrapper);
    auto windowDelegate = ni_registerInterface(m, "WindowDelegate");
    windowDelegate_canClose = ni_registerInterfaceMethod(windowDelegate, "canClose", &WindowDelegate_canClose__wrapper);
    windowDelegate_closed = ni_registerInterfaceMethod(windowDelegate, "closed", &WindowDelegate_closed__wrapper);
    windowDelegate_destroyed = ni_registerInterfaceMethod(windowDelegate, "destroyed", &WindowDelegate_destroyed__wrapper);
    windowDelegate_mouseDown = ni_registerInterfaceMethod(windowDelegate, "mouseDown", &WindowDelegate_mouseDown__wrapper);
    windowDelegate_repaint = ni_registerInterfaceMethod(windowDelegate, "repaint", &WindowDelegate_repaint__wrapper);
    windowDelegate_resized = ni_registerInterfaceMethod(windowDelegate, "resized", &WindowDelegate_resized__wrapper);
    return 0; // = OK
}
