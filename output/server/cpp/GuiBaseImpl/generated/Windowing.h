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

struct __DropData; typedef struct __DropData* DropData;
struct __DragRenderPayload; typedef struct __DragRenderPayload* DragRenderPayload;
struct __DragData; typedef struct __DragData* DragData;
struct __Window; typedef struct __Window* Window;
struct __Timer; typedef struct __Timer* Timer;
struct __Icon; typedef struct __Icon* Icon;
struct __Accelerator; typedef struct __Accelerator* Accelerator;
struct __MenuAction; typedef struct __MenuAction* MenuAction;
struct __MenuItem; typedef struct __MenuItem* MenuItem;
struct __Menu; typedef struct __Menu* Menu;
struct __MenuBar; typedef struct __MenuBar* MenuBar;
struct __ClipData; typedef struct __ClipData* ClipData;
struct __FileDialog; typedef struct __FileDialog* FileDialog;
struct __MessageBoxModal; typedef struct __MessageBoxModal* MessageBoxModal;

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

enum Modifiers {
    Shift = 1,
    Control = 1 << 1,
    Alt = 1 << 2,
    MacControl = 1 << 3
};



enum class CursorStyle {
    Default,
    TextSelect,
    BusyWait,
    Cross,
    UpArrow,
    ResizeTopLeftBottomRight,
    ResizeTopRightBottomLeft,
    ResizeLeftRight,
    ResizeUpDown,
    Move,
    Unavailable,
    HandSelect,
    PointerWorking,
    HelpSelect,
    LocationSelect,
    PersonSelect,
    Handwriting
};

enum DropEffect {
    None = 0,
    Copy = 1,
    Move = 1 << 1,
    Link = 1 << 2,
    Other = 1 << 3
};

// std::vector<std::string>

typedef bool DragRenderFunc(std::string requestedFormat, DragRenderPayload payload);


// std::shared_ptr<NativeBuffer<uint8_t>>


class DropDataBadFormat {
public:
    std::string format;
    DropDataBadFormat(std::string format)
        : format(format) {}
};


struct FileDialogResult {
    bool success;
    std::vector<std::string> filenames;
};

enum class FileDialogMode {
    File,
    Folder
};

// std::vector<std::vector<std::string>>

struct FileDialogFilterSpec {
    std::string description;
    std::vector<std::string> extensions;
};

// std::vector<FileDialogFilterSpec>

struct FileDialogOptions {
    Window forWindow;
    FileDialogMode mode;
    std::vector<FileDialogFilterSpec> filters;
    bool allowAll;
    std::string defaultExt;
    bool allowMultiple;
    std::string suggestedFilename;
};



enum class KeyLocation {
    Default,
    Left,
    Right,
    NumPad
};


typedef void MenuActionFunc();




enum class MessageBoxButtons {
    Default = 0,
    AbortRetryIgnore,
    CancelTryContinue,
    Ok,
    OkCancel,
    RetryCancel,
    YesNo,
    YesNoCancel
};

enum class MessageBoxIcon {
    Default = 0,
    Information,
    Warning,
    Question,
    Error
};

enum class MessageBoxResult {
    Abort,
    Cancel,
    Continue,
    Ignore,
    No,
    Ok,
    Retry,
    TryAgain,
    Yes
};

struct MessageBoxParams {
    std::string title;
    std::string message;
    bool withHelpButton;
    MessageBoxIcon icon;
    MessageBoxButtons buttons;
};


enum class MouseButton {
    None,
    Left,
    Middle,
    Right,
    Other
};

typedef void TimerFunc(double secondsSinceLast);


class WindowDelegate; // fwd decl

enum class WindowStyle {
    Default,
    Frameless,
    PluginWindow
};

struct WindowOptions {
private:
    enum Fields {
        MinWidthField = 1,
        MinHeightField = 2,
        MaxWidthField = 4,
        MaxHeightField = 8,
        StyleField = 16,
        NativeParentField = 32
    };
    int32_t _usedFields = 0;
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
        _usedFields |= Fields::MinWidthField;
    }
    bool hasMinWidth(int32_t *value) {
        if (_usedFields & Fields::MinWidthField) {
            *value = _minWidth;
            return true;
        }
        return false;
    }
    void setMinHeight(int32_t value) {
        _minHeight = value;
        _usedFields |= Fields::MinHeightField;
    }
    bool hasMinHeight(int32_t *value) {
        if (_usedFields & Fields::MinHeightField) {
            *value = _minHeight;
            return true;
        }
        return false;
    }
    void setMaxWidth(int32_t value) {
        _maxWidth = value;
        _usedFields |= Fields::MaxWidthField;
    }
    bool hasMaxWidth(int32_t *value) {
        if (_usedFields & Fields::MaxWidthField) {
            *value = _maxWidth;
            return true;
        }
        return false;
    }
    void setMaxHeight(int32_t value) {
        _maxHeight = value;
        _usedFields |= Fields::MaxHeightField;
    }
    bool hasMaxHeight(int32_t *value) {
        if (_usedFields & Fields::MaxHeightField) {
            *value = _maxHeight;
            return true;
        }
        return false;
    }
    void setStyle(WindowStyle value) {
        _style = value;
        _usedFields |= Fields::StyleField;
    }
    bool hasStyle(WindowStyle *value) {
        if (_usedFields & Fields::StyleField) {
            *value = _style;
            return true;
        }
        return false;
    }
    void setNativeParent(size_t value) {
        _nativeParent = value;
        _usedFields |= Fields::NativeParentField;
    }
    bool hasNativeParent(size_t *value) {
        if (_usedFields & Fields::NativeParentField) {
            *value = _nativeParent;
            return true;
        }
        return false;
    }
};


class WindowDelegate {
public:
    virtual bool canClose() = 0;
    virtual void closed() = 0;
    virtual void destroyed() = 0;
    virtual void mouseDown(int32_t x, int32_t y, MouseButton button, uint32_t modifiers) = 0;
    virtual void mouseUp(int32_t x, int32_t y, MouseButton button, uint32_t modifiers) = 0;
    virtual void mouseMove(int32_t x, int32_t y, uint32_t modifiers) = 0;
    virtual void mouseEnter(int32_t x, int32_t y, uint32_t modifiers) = 0;
    virtual void mouseLeave(uint32_t modifiers) = 0;
    virtual void repaint(DrawContext context, int32_t x, int32_t y, int32_t width, int32_t height) = 0;
    virtual void moved(int32_t x, int32_t y) = 0;
    virtual void resized(int32_t width, int32_t height) = 0;
    virtual void keyDown(Key key, uint32_t modifiers, KeyLocation location) = 0;
    virtual uint32_t dropFeedback(DropData data, int32_t x, int32_t y, uint32_t modifiers, uint32_t suggested) = 0;
    virtual void dropLeave() = 0;
    virtual void dropSubmit(DropData data, int32_t x, int32_t y, uint32_t modifiers, uint32_t effect) = 0;
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

extern const std::string kDragFormatUTF8;
extern const std::string kDragFormatFiles;

void moduleInit();
void moduleShutdown();
void runloop();
void exitRunloop();
bool DropData_hasFormat(DropData _this, std::string mimeFormat);
std::vector<std::string> DropData_getFiles(DropData _this); // throws DropDataBadFormat
std::string DropData_getTextUTF8(DropData _this); // throws DropDataBadFormat
std::shared_ptr<NativeBuffer<uint8_t>> DropData_getFormat(DropData _this, std::string mimeFormat); // throws DropDataBadFormat
void DropData_dispose(DropData _this);
void DragRenderPayload_renderUTF8(DragRenderPayload _this, std::string text);
void DragRenderPayload_renderFiles(DragRenderPayload _this, std::vector<std::string> filenames);
void DragRenderPayload_renderFormat(DragRenderPayload _this, std::string formatMIME, std::shared_ptr<NativeBuffer<uint8_t>> data);
void DragRenderPayload_dispose(DragRenderPayload _this);
uint32_t DragData_dragExec(DragData _this, uint32_t canDoMask);
void DragData_dispose(DragData _this);
DragData DragData_create(std::vector<std::string> supportedFormats, std::function<DragRenderFunc> renderFunc);
void Window_destroy(Window _this);
void Window_show(Window _this);
void Window_showRelativeTo(Window _this, Window other, int32_t x, int32_t y, int32_t newWidth, int32_t newHeight);
void Window_showModal(Window _this, Window parent);
void Window_endModal(Window _this);
void Window_hide(Window _this);
void Window_invalidate(Window _this, int32_t x, int32_t y, int32_t width, int32_t height);
void Window_setTitle(Window _this, std::string title);
void Window_focus(Window _this);
void Window_mouseGrab(Window _this);
size_t Window_getOSHandle(Window _this);
void Window_enableDrops(Window _this, bool enable);
void Window_setMenuBar(Window _this, MenuBar menuBar);
void Window_showContextMenu(Window _this, int32_t x, int32_t y, Menu menu);
void Window_setCursor(Window _this, CursorStyle style);
void Window_dispose(Window _this);
Window Window_create(int32_t width, int32_t height, std::string title, std::shared_ptr<WindowDelegate> del, WindowOptions opts);
void Window_mouseUngrab();
void Timer_dispose(Timer _this);
Timer Timer_create(int32_t msTimeout, std::function<TimerFunc> func);
void Icon_dispose(Icon _this);
Icon Icon_create(std::string filename, int32_t sizeToWidth);
void Accelerator_dispose(Accelerator _this);
Accelerator Accelerator_create(Key key, uint32_t modifiers);
void MenuAction_dispose(MenuAction _this);
MenuAction MenuAction_create(std::string label, Icon icon, Accelerator accel, std::function<MenuActionFunc> func);
void MenuItem_dispose(MenuItem _this);
MenuItem Menu_addAction(Menu _this, MenuAction action);
MenuItem Menu_addSubmenu(Menu _this, std::string label, Menu sub);
void Menu_addSeparator(Menu _this);
void Menu_dispose(Menu _this);
Menu Menu_create();
void MenuBar_addMenu(MenuBar _this, std::string label, Menu menu);
void MenuBar_dispose(MenuBar _this);
MenuBar MenuBar_create();
void ClipData_dispose(ClipData _this);
void ClipData_setClipboard(DragData dragData);
ClipData ClipData_get();
void ClipData_flushClipboard();
void FileDialog_dispose(FileDialog _this);
FileDialogResult FileDialog_openFile(FileDialogOptions opts);
FileDialogResult FileDialog_saveFile(FileDialogOptions opts);
void MessageBoxModal_dispose(MessageBoxModal _this);
MessageBoxResult MessageBoxModal_show(Window forWindow, MessageBoxParams mbParams);
