#pragma once

#include "../support/NativeImplServer.h"
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <set>

#include "Drawing.h"

struct __Accelerator; typedef struct __Accelerator* Accelerator;

struct __Action; typedef struct __Action* Action;

struct __Icon; typedef struct __Icon* Icon;

enum class Key {
    Unknown,
    Escape,
    Tab,
    Backspace,
    Return,
    Space,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    F13,
    F14,
    F15,
    F16,
    F17,
    F18,
    F19,
    _0,
    _1,
    _2,
    _3,
    _4,
    _5,
    _6,
    _7,
    _8,
    _9,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    Control,
    Shift,
    AltOption,
    WinCommand,
    Fn,
    Insert,
    Delete,
    PageUp,
    PageDown,
    Home,
    End,
    LeftArrow,
    UpArrow,
    RightArrow,
    DownArrow,
    KP0,
    KP1,
    KP2,
    KP3,
    KP4,
    KP5,
    KP6,
    KP7,
    KP8,
    KP9,
    KPClear,
    KPEquals,
    KPDivide,
    KPMultiply,
    KPSubtract,
    KPAdd,
    KPEnter,
    KPDecimal,
    CapsLock,
    NumLock,
    ScrollLock,
    PrintScreen,
    Pause,
    Cancel,
    MediaMute,
    MediaVolumeDown,
    MediaVolumeUp,
    MediaNext,
    MediaPrev,
    MediaStop,
    MediaPlayPause
};

struct __Menu; typedef struct __Menu* Menu;

typedef void MenuActionFunc();

struct __MenuBar; typedef struct __MenuBar* MenuBar;

struct __MenuItem; typedef struct __MenuItem* MenuItem;

enum Modifiers {
    Shift = 1,
    Control = 2,
    Alt = 4,
    MacControl = 8
};

enum class MouseButton {
    None,
    Left,
    Middle,
    Right,
    Other
};

struct __Window; typedef struct __Window* Window;

class WindowDelegate {
public:
    virtual bool canClose() = 0;
    virtual void closed() = 0;
    virtual void destroyed() = 0;
    virtual void mouseDown(int32_t x, int32_t y, MouseButton button, uint32_t modifiers) = 0;
    virtual void repaint(DrawContext context, int32_t x, int32_t y, int32_t width, int32_t height) = 0;
    virtual void resized(int32_t width, int32_t height) = 0;
};

// inherit from this to create server instances of WindowDelegate
class ServerWindowDelegate : public WindowDelegate, public ServerObject {
public:
    virtual ~ServerWindowDelegate() {}
    static std::shared_ptr<ServerWindowDelegate> getByID(int id) {
        auto obj = ServerObject::getByID(id);
        return std::static_pointer_cast<ServerWindowDelegate>(obj);
    }
};

enum class WindowStyle {
    Default,
    Frameless,
    PluginWindow
};

struct WindowOptions {
private:
    enum Fields {
        MinWidth = 1,
        MinHeight = 2,
        MaxWidth = 4,
        MaxHeight = 8,
        Style = 16,
        NativeParent = 32
    };
    int32_t _usedFields;
    int32_t _minWidth;
    int32_t _minHeight;
    int32_t _maxWidth;
    int32_t _maxHeight;
    WindowStyle _style;
    size_t _nativeParent;
protected:
    int32_t getUsedFields() {
        return _usedFields;
    }
    friend void WindowOptions__push(WindowOptions value, bool isReturn);
    friend WindowOptions WindowOptions__pop();
public:
    void setMinWidth(int32_t value) {
        _minWidth = value;
        _usedFields |= Fields::MinWidth;
    }
    bool hasMinWidth(int32_t *value) {
        if (_usedFields & Fields::MinWidth) {
            *value = _minWidth;
            return true;
        }
        return false;
    }
    void setMinHeight(int32_t value) {
        _minHeight = value;
        _usedFields |= Fields::MinHeight;
    }
    bool hasMinHeight(int32_t *value) {
        if (_usedFields & Fields::MinHeight) {
            *value = _minHeight;
            return true;
        }
        return false;
    }
    void setMaxWidth(int32_t value) {
        _maxWidth = value;
        _usedFields |= Fields::MaxWidth;
    }
    bool hasMaxWidth(int32_t *value) {
        if (_usedFields & Fields::MaxWidth) {
            *value = _maxWidth;
            return true;
        }
        return false;
    }
    void setMaxHeight(int32_t value) {
        _maxHeight = value;
        _usedFields |= Fields::MaxHeight;
    }
    bool hasMaxHeight(int32_t *value) {
        if (_usedFields & Fields::MaxHeight) {
            *value = _maxHeight;
            return true;
        }
        return false;
    }
    void setStyle(WindowStyle value) {
        _style = value;
        _usedFields |= Fields::Style;
    }
    bool hasStyle(WindowStyle *value) {
        if (_usedFields & Fields::Style) {
            *value = _style;
            return true;
        }
        return false;
    }
    void setNativeParent(size_t value) {
        _nativeParent = value;
        _usedFields |= Fields::NativeParent;
    }
    bool hasNativeParent(size_t *value) {
        if (_usedFields & Fields::NativeParent) {
            *value = _nativeParent;
            return true;
        }
        return false;
    }
};

void moduleInit();
void moduleShutdown();
void runloop();
void exitRunloop();
Window createWindow(int32_t width, int32_t height, std::string title, std::shared_ptr<WindowDelegate> del, WindowOptions opts);
Icon createIcon(std::string filename, int32_t sizeToWidth);
Accelerator createAccelerator(Key key, uint32_t modifiers);
Action createAction(std::string label, Icon icon, Accelerator accel, std::function<MenuActionFunc> func);
Menu createMenu();
MenuBar createMenuBar();
void Window_show(Window _this);
void Window_destroy(Window _this);
void Window_setMenuBar(Window _this, MenuBar menuBar);
void Window_showContextMenu(Window _this, int32_t x, int32_t y, Menu menu);
MenuItem Menu_addAction(Menu _this, Action action);
MenuItem Menu_addSubmenu(Menu _this, std::string label, Menu sub);
void Menu_addSeparator(Menu _this);
MenuItem MenuBar_addMenu(MenuBar _this, std::string label, Menu menu);
