#pragma once

#include "../support/NativeImplServer.h"
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <set>
#include <optional>
#include "../support/result.h"

#include "Keys.h"
using namespace Keys;
#include "Drawing.h"
using namespace Drawing;

namespace Windowing
{

    struct __Icon; typedef struct __Icon* IconRef;
    struct __Accelerator; typedef struct __Accelerator* AcceleratorRef;
    struct __MenuAction; typedef struct __MenuAction* MenuActionRef;
    struct __MenuItem; typedef struct __MenuItem* MenuItemRef;
    struct __Menu; typedef struct __Menu* MenuRef;
    struct __MenuBar; typedef struct __MenuBar* MenuBarRef;
    struct __DropData; typedef struct __DropData* DropDataRef;
    struct __DragData; typedef struct __DragData* DragDataRef;
    struct __ClipData; typedef struct __ClipData* ClipDataRef; // extends DropDataRef
    struct __Window; typedef struct __Window* WindowRef;
    struct __Timer; typedef struct __Timer* TimerRef;
    void moduleInit();
    void moduleShutdown();
    void runloop();
    void exitRunloop();

    enum Modifiers {
        Shift = 1,
        Control = 1 << 1,
        Alt = 1 << 2,
        MacControl = 1 << 3
    };

    namespace Icon {
        IconRef create(std::string filename, int32_t sizeToWidth);
    }
    void Icon_dispose(IconRef _this);

    namespace Accelerator {
        AcceleratorRef create(Key key, uint32_t modifiers);
    }
    void Accelerator_dispose(AcceleratorRef _this);

    namespace MenuAction {

        typedef void ActionFunc();
        MenuActionRef create(std::string label, IconRef icon, AcceleratorRef accel, std::function<ActionFunc> func);
    }
    void MenuAction_dispose(MenuActionRef _this);

    void MenuItem_dispose(MenuItemRef _this);

    namespace Menu {
        MenuRef create();
    }
    MenuItemRef Menu_addAction(MenuRef _this, MenuActionRef action);
    MenuItemRef Menu_addSubmenu(MenuRef _this, std::string label, MenuRef sub);
    void Menu_addSeparator(MenuRef _this);
    void Menu_dispose(MenuRef _this);

    namespace MenuBar {
        MenuBarRef create();
    }
    void MenuBar_addMenu(MenuBarRef _this, std::string label, MenuRef menu);
    void MenuBar_dispose(MenuBarRef _this);
    extern const std::string kDragFormatUTF8;
    extern const std::string kDragFormatFiles;

    namespace DropData {

        class BadFormat {
        public:
            std::string format;
            BadFormat(std::string format)
                : format(format) {}
        };
    }
    bool DropData_hasFormat(DropDataRef _this, std::string mimeFormat);
    std::vector<std::string> DropData_getFiles(DropDataRef _this); // throws DropData::BadFormat
    std::string DropData_getTextUTF8(DropDataRef _this); // throws DropData::BadFormat
    std::shared_ptr<NativeBuffer<uint8_t>> DropData_getFormat(DropDataRef _this, std::string mimeFormat); // throws DropData::BadFormat
    void DropData_dispose(DropDataRef _this);

    enum DropEffect {
        None = 0,
        Copy = 1,
        Move = 1 << 1,
        Link = 1 << 2,
        Other = 1 << 3
    };

    namespace DragData {

        struct __RenderPayload; typedef struct __RenderPayload* RenderPayloadRef;

        void RenderPayload_renderUTF8(RenderPayloadRef _this, std::string text);
        void RenderPayload_renderFiles(RenderPayloadRef _this, std::vector<std::string> filenames);
        void RenderPayload_renderFormat(RenderPayloadRef _this, std::string formatMIME, std::shared_ptr<NativeBuffer<uint8_t>> data);
        void RenderPayload_dispose(RenderPayloadRef _this);

        typedef bool RenderFunc(std::string requestedFormat, RenderPayloadRef payload);
        DragDataRef create(std::vector<std::string> supportedFormats, std::function<RenderFunc> renderFunc);
    }
    uint32_t DragData_dragExec(DragDataRef _this, uint32_t canDoMask);
    void DragData_dispose(DragDataRef _this);

    namespace ClipData {
        void setClipboard(DragDataRef dragData);
        ClipDataRef get();
        void flushClipboard();
    }
    void ClipData_dispose(ClipDataRef _this);

    enum class MouseButton {
        None,
        Left,
        Middle,
        Right,
        Other
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
        virtual void repaint(DrawContextRef context, int32_t x, int32_t y, int32_t width, int32_t height) = 0;
        virtual void moved(int32_t x, int32_t y) = 0;
        virtual void resized(int32_t width, int32_t height) = 0;
        virtual void keyDown(Key key, uint32_t modifiers, KeyLocation location) = 0;
        virtual uint32_t dropFeedback(DropDataRef data, int32_t x, int32_t y, uint32_t modifiers, uint32_t suggested) = 0;
        virtual void dropLeave() = 0;
        virtual void dropSubmit(DropDataRef data, int32_t x, int32_t y, uint32_t modifiers, uint32_t effect) = 0;
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

    namespace Window {

        enum class Style {
            Default,
            Frameless,
            PluginWindow
        };

        struct Options {
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
            Style _style;
            size_t _nativeParent;
        protected:
            int32_t getUsedFields() {
                return _usedFields;
            }
            friend void Options__push(Options value, bool isReturn);
            friend Options Options__pop();
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
            void setStyle(Style value) {
                _style = value;
                _usedFields |= Fields::StyleField;
            }
            bool hasStyle(Style *value) {
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
        WindowRef create(int32_t width, int32_t height, std::string title, std::shared_ptr<WindowDelegate> del, Options opts);
        void mouseUngrab();
    }
    void Window_destroy(WindowRef _this);
    void Window_show(WindowRef _this);
    void Window_showRelativeTo(WindowRef _this, WindowRef other, int32_t x, int32_t y, int32_t newWidth, int32_t newHeight);
    void Window_showModal(WindowRef _this, WindowRef parent);
    void Window_endModal(WindowRef _this);
    void Window_hide(WindowRef _this);
    void Window_invalidate(WindowRef _this, int32_t x, int32_t y, int32_t width, int32_t height);
    void Window_setTitle(WindowRef _this, std::string title);
    void Window_focus(WindowRef _this);
    void Window_mouseGrab(WindowRef _this);
    size_t Window_getOSHandle(WindowRef _this);
    void Window_enableDrops(WindowRef _this, bool enable);
    void Window_setMenuBar(WindowRef _this, MenuBarRef menuBar);
    void Window_showContextMenu(WindowRef _this, int32_t x, int32_t y, MenuRef menu);
    void Window_setCursor(WindowRef _this, CursorStyle style);
    void Window_dispose(WindowRef _this);

    namespace Timer {

        typedef void TimerFunc(double secondsSinceLast);
        TimerRef create(int32_t msTimeout, std::function<TimerFunc> func);
    }
    void Timer_dispose(TimerRef _this);
    namespace FileDialog {

        enum class Mode {
            File,
            Folder
        };

        struct FilterSpec {
            std::string description;
            std::vector<std::string> extensions;
        };

        struct Options {
            WindowRef forWindow;
            Mode mode;
            std::vector<FilterSpec> filters;
            bool allowAll;
            std::string defaultExt;
            bool allowMultiple;
            std::string suggestedFilename;
        };

        struct DialogResult {
            bool success;
            std::vector<std::string> filenames;
        };
        DialogResult openFile(Options opts);
        DialogResult saveFile(Options opts);
    }
    namespace MessageBoxModal {

        enum class Buttons {
            Default = 0,
            AbortRetryIgnore,
            CancelTryContinue,
            Ok,
            OkCancel,
            RetryCancel,
            YesNo,
            YesNoCancel
        };

        enum class Icon {
            Default = 0,
            Information,
            Warning,
            Question,
            Error
        };

        struct Params {
            std::string title;
            std::string message;
            bool withHelpButton;
            Icon icon;
            Buttons buttons;
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
        MessageBoxResult show(WindowRef forWindow, Params mbParams);
    }
}
