#pragma once
#include "Windowing.h"

namespace Windowing
{

    inline void __Native_UInt8_Buffer__push(std::shared_ptr<NativeBuffer<uint8_t>> buf, bool isReturn);
    std::shared_ptr<NativeBuffer<uint8_t>> __Native_UInt8_Buffer__pop();

    void moduleInit__wrapper();

    void moduleShutdown__wrapper();

    void runloop__wrapper();

    void exitRunloop__wrapper();

    void Modifiers__push(uint32_t value);
    uint32_t Modifiers__pop();

    void Icon__push(IconRef value);
    IconRef Icon__pop();
    namespace Icon {

        void create__wrapper();
    }

    void Icon_dispose__wrapper();

    void Accelerator__push(AcceleratorRef value);
    AcceleratorRef Accelerator__pop();
    namespace Accelerator {

        void create__wrapper();
    }

    void Accelerator_dispose__wrapper();

    void MenuAction__push(MenuActionRef value);
    MenuActionRef MenuAction__pop();
    namespace MenuAction {
        void ActionFunc__push(std::function<ActionFunc> f);
        std::function<ActionFunc> ActionFunc__pop();

        void create__wrapper();
    }

    void MenuAction_dispose__wrapper();

    void MenuItem__push(MenuItemRef value);
    MenuItemRef MenuItem__pop();

    void MenuItem_dispose__wrapper();

    void Menu__push(MenuRef value);
    MenuRef Menu__pop();
    namespace Menu {

        void create__wrapper();
    }

    void Menu_addAction__wrapper();

    void Menu_addSubmenu__wrapper();

    void Menu_addSeparator__wrapper();

    void Menu_dispose__wrapper();

    void MenuBar__push(MenuBarRef value);
    MenuBarRef MenuBar__pop();
    namespace MenuBar {

        void create__wrapper();
    }

    void MenuBar_addMenu__wrapper();

    void MenuBar_dispose__wrapper();

    void DropData__push(DropDataRef value);
    DropDataRef DropData__pop();
    namespace DropData {

        void BadFormat__push(BadFormat e);
        void BadFormat__buildAndThrow();
    }

    void DropData_hasFormat__wrapper();

    void DropData_getFiles__wrapper();

    void DropData_getTextUTF8__wrapper();

    void DropData_getFormat__wrapper();

    void DropData_dispose__wrapper();

    void DropEffect__push(uint32_t value);
    uint32_t DropEffect__pop();

    void DragData__push(DragDataRef value);
    DragDataRef DragData__pop();
    namespace DragData {

        void RenderPayload__push(RenderPayloadRef value);
        RenderPayloadRef RenderPayload__pop();

        void RenderPayload_renderUTF8__wrapper();

        void RenderPayload_renderFiles__wrapper();

        void RenderPayload_renderFormat__wrapper();

        void RenderPayload_dispose__wrapper();
        void RenderFunc__push(std::function<RenderFunc> f);
        std::function<RenderFunc> RenderFunc__pop();

        void create__wrapper();
    }

    void DragData_dragExec__wrapper();

    void DragData_dispose__wrapper();

    void ClipData__push(ClipDataRef value);
    ClipDataRef ClipData__pop();
    namespace ClipData {

        void setClipboard__wrapper();

        void get__wrapper();

        void flushClipboard__wrapper();
    }

    void ClipData_dispose__wrapper();

    void MouseButton__push(MouseButton value);
    MouseButton MouseButton__pop();

    void WindowDelegate__push(std::shared_ptr<WindowDelegate> inst, bool isReturn);
    std::shared_ptr<WindowDelegate> WindowDelegate__pop();

    void WindowDelegate_canClose__wrapper(int serverID);

    void WindowDelegate_closed__wrapper(int serverID);

    void WindowDelegate_destroyed__wrapper(int serverID);

    void WindowDelegate_mouseDown__wrapper(int serverID);

    void WindowDelegate_mouseUp__wrapper(int serverID);

    void WindowDelegate_mouseMove__wrapper(int serverID);

    void WindowDelegate_mouseEnter__wrapper(int serverID);

    void WindowDelegate_mouseLeave__wrapper(int serverID);

    void WindowDelegate_repaint__wrapper(int serverID);

    void WindowDelegate_moved__wrapper(int serverID);

    void WindowDelegate_resized__wrapper(int serverID);

    void WindowDelegate_keyDown__wrapper(int serverID);

    void WindowDelegate_dropFeedback__wrapper(int serverID);

    void WindowDelegate_dropLeave__wrapper(int serverID);

    void WindowDelegate_dropSubmit__wrapper(int serverID);

    void CursorStyle__push(CursorStyle value);
    CursorStyle CursorStyle__pop();

    void Window__push(WindowRef value);
    WindowRef Window__pop();
    namespace Window {

        void Style__push(Style value);
        Style Style__pop();

        void Options__push(Options value, bool isReturn);
        Options Options__pop();

        void create__wrapper();

        void mouseUngrab__wrapper();
    }

    void Window_destroy__wrapper();

    void Window_show__wrapper();

    void Window_showRelativeTo__wrapper();

    void Window_showModal__wrapper();

    void Window_endModal__wrapper();

    void Window_hide__wrapper();

    void Window_invalidate__wrapper();

    void Window_setTitle__wrapper();

    void Window_focus__wrapper();

    void Window_mouseGrab__wrapper();

    void Window_getOSHandle__wrapper();

    void Window_enableDrops__wrapper();

    void Window_setMenuBar__wrapper();

    void Window_showContextMenu__wrapper();

    void Window_setCursor__wrapper();

    void Window_dispose__wrapper();

    void Timer__push(TimerRef value);
    TimerRef Timer__pop();
    namespace Timer {
        void TimerFunc__push(std::function<TimerFunc> f);
        std::function<TimerFunc> TimerFunc__pop();

        void create__wrapper();
    }

    void Timer_dispose__wrapper();
    namespace FileDialog {

        void Mode__push(Mode value);
        Mode Mode__pop();

        void FilterSpec__push(FilterSpec value, bool isReturn);
        FilterSpec FilterSpec__pop();

        void Options__push(Options value, bool isReturn);
        Options Options__pop();

        void DialogResult__push(DialogResult value, bool isReturn);
        DialogResult DialogResult__pop();

        void openFile__wrapper();

        void saveFile__wrapper();
    }
    namespace MessageBoxModal {

        void Buttons__push(Buttons value);
        Buttons Buttons__pop();

        void Icon__push(Icon value);
        Icon Icon__pop();

        void Params__push(Params value, bool isReturn);
        Params Params__pop();

        void MessageBoxResult__push(MessageBoxResult value);
        MessageBoxResult MessageBoxResult__pop();

        void show__wrapper();
    }

    int __register();
}
