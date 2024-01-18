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

enum class Modifiers {
    Shift,
    Control,
    Alt,
    MacControl
};

enum class MouseButton {
    None,
    Left,
    Middle,
    Right,
    Other
};

struct __Window; typedef struct __Window* Window;

// std::set<Modifiers>

class WindowDelegate {
public:
    virtual bool canClose() = 0;
    virtual void closed() = 0;
    virtual void destroyed() = 0;
    virtual void mouseDown(int32_t x, int32_t y, MouseButton button, std::set<Modifiers> modifiers) = 0;
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
void Window_show(Window _this);
void Window_destroy(Window _this);
