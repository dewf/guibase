#include "generated/Windowing.h"

#include "deps/openwl/source/openwl.h"
#include "deps/opendl/source/opendl.h"

#include <stdio.h>

namespace Windowing
{
    static std::map<int, std::function<MenuAction::ActionFunc>> menuActionFuncs;
    static int _nextMenuActionId = 1;

    static std::function<MenuAction::ActionFunc> actionFuncForId(int id) {
        return menuActionFuncs[id];
    }

    static void convertProps(Window::Options& opts, wl_WindowProperties& output) {
        int minWidth, minHeight, maxWidth, maxHeight;
        Window::Style style;
        size_t nativeParent; // HWND

        // make sure nothing by default
        output.usedFields = 0;

        if (opts.hasMinWidth(&minWidth)) {
            output.usedFields |= wl_kWindowPropMinWidth;
            output.minWidth = minWidth;
        }
        if (opts.hasMinHeight(&minHeight)) {
            output.usedFields |= wl_kWindowPropMinHeight;
            output.minHeight = minHeight;
        }
        if (opts.hasMaxWidth(&maxWidth)) {
            output.usedFields |= wl_kWindowPropMaxWidth;
            output.maxWidth = maxWidth;
        }
        if (opts.hasMaxHeight(&maxHeight)) {
            output.usedFields |= wl_kWindowPropMaxHeight;
            output.maxHeight = maxHeight;
        }
        if (opts.hasStyle(&style)) {
            output.usedFields |= wl_kWindowPropStyle;
            output.style = (wl_WindowStyleEnum)style; // 1:1 mapping at the moment
        }
        if (opts.hasNativeParent(&nativeParent)) {
            output.usedFields |= wl_kWindowPropNativeParent;
            output.nativeParent = (HWND)nativeParent;
        }
    }

    class InternalWindow {
    private:
        wl_WindowRef wlWindow = nullptr;
        std::shared_ptr<WindowDelegate> del;
        std::map<CursorStyle, wl_CursorRef> cachedCursors;
    public:
        static InternalWindow* create(int width, int height, std::string title, std::shared_ptr<WindowDelegate> del, Window::Options& opts) {
            wl_WindowProperties wlProps;
            convertProps(opts, wlProps);

            auto win2 = new InternalWindow();
            win2->wlWindow = wl_WindowCreate(width, height, title.c_str(), win2, &wlProps);
            win2->del = del;

            return win2;
        }
        // util
        wl_WindowRef getWlWindow() {
            return wlWindow;
        }
        // opaque methods ==========================
        void show() {
            wl_WindowShow(wlWindow);
        }
        void showRelativeTo(InternalWindow* other, int x, int y, int newWidth, int newHeight) {
            wl_WindowShowRelative(wlWindow, other->wlWindow, x, y, newWidth, newHeight);
        }
        void hide() {
            wl_WindowHide(wlWindow);
        }
        void destroy() {
            wl_WindowDestroy(wlWindow);
        }
        void setMenuBar(MenuBarRef mb) {
            wl_WindowSetMenuBar(wlWindow, (wl_MenuBarRef)mb);
        }
        void showContextMenu(int x, int y, MenuRef menu) {
            wl_WindowShowContextMenu(wlWindow, x, y, (wl_MenuRef)menu, nullptr);
        }
        void setCursor(CursorStyle style) {
            wl_CursorRef wlCursor;
            if (cachedCursors.contains(style)) {
                wlCursor = cachedCursors[style];
            }
            else {
                wlCursor = wl_CursorCreate((wl_CursorStyle)style);
                cachedCursors[style] = wlCursor;
            }
            wl_WindowSetCursor(wlWindow, wlCursor);
        }
        void invalidate(int x, int y, int width, int height) {
            wl_WindowInvalidate(wlWindow, x, y, width, height);
        }
        void setTitle(std::string title) {
            wl_WindowSetTitle(wlWindow, title.c_str());
        }
        void enableDrops(bool enable) {
            wl_WindowEnableDrops(wlWindow, enable);
        }
        void showModal(InternalWindow* parent) {
            wl_WindowShowModal(wlWindow, parent->wlWindow);
        }
        void endModal() {
            wl_WindowEndModal(wlWindow);
        }
        void focus() {
            wl_WindowSetFocus(wlWindow);
        }
        void mouseGrab() {
            wl_MouseGrab(wlWindow);
        }
        static void mouseUngrab() {
            wl_MouseUngrab();
        }
        size_t getOSHandle() {
            return wl_WindowGetOSHandle(wlWindow);
        }
        // OpenWL event handling ==========================
        void onDestroyed() {
            del->destroyed();
        }
        bool canClose() {
            return del->canClose();
        }
        void onAction(wl_ActionEvent& actionEvent) {
            auto func = actionFuncForId(actionEvent.id);
            func();
        }
        void onRepaint(wl_RepaintEvent& paintEvent) {
            auto context = dl_CGContextCreateD2D(paintEvent.platformContext.d2d.target);
            del->repaint((DrawContextRef)context, paintEvent.x, paintEvent.y, paintEvent.width, paintEvent.height);
            dl_CGContextRelease(context);
        }
        void onMoved(wl_MoveEvent& moveEvent) {
            del->moved(moveEvent.x, moveEvent.y);
        }
        void onResized(wl_ResizeEvent& resizeEvent) {
            del->resized(resizeEvent.newWidth, resizeEvent.newHeight);
        }
        void onMouse(wl_MouseEvent& mouseEvent) {
            switch (mouseEvent.eventType) {
            case wl_kMouseEventTypeMouseDown:
                del->mouseDown(mouseEvent.x, mouseEvent.y, (MouseButton)mouseEvent.button, mouseEvent.modifiers);
                break;
            case wl_kMouseEventTypeMouseUp:
                del->mouseUp(mouseEvent.x, mouseEvent.y, (MouseButton)mouseEvent.button, mouseEvent.modifiers);
                break;
            case wl_kMouseEventTypeMouseMove:
                del->mouseMove(mouseEvent.x, mouseEvent.y, mouseEvent.modifiers);
                break;
            case wl_kMouseEventTypeMouseEnter:
                del->mouseEnter(mouseEvent.x, mouseEvent.y, mouseEvent.modifiers);
                break;
            case wl_kMouseEventTypeMouseLeave:
                del->mouseLeave(mouseEvent.modifiers);
                break;
            }
        }
        void onKey(wl_KeyEvent& keyEvent) {
            switch (keyEvent.eventType) {
            case wl_kKeyEventTypeDown:
                del->keyDown((Key)keyEvent.key, keyEvent.modifiers, (KeyLocation)keyEvent.location);
                break;
            }
        }
        void onDrop(wl_DropEvent& dropEvent) {
            switch (dropEvent.eventType) {
            case wl_kDropEventTypeFeedback: {
                auto allowed = del->dropFeedback((DropDataRef)dropEvent.data, dropEvent.x, dropEvent.y, dropEvent.modifiers, dropEvent.defaultModifierAction);
                dropEvent.allowedEffectMask = allowed;
                break;
            }
            case wl_kDropEventTypeLeave:
                del->dropLeave();
                break;
            case wl_kDropEventTypeDrop:
                del->dropSubmit((DropDataRef)dropEvent.data, dropEvent.x, dropEvent.y, dropEvent.modifiers, dropEvent.defaultModifierAction);
                break;
            }
        }
    };

    struct __Timer {
    private:
        wl_TimerRef wlTimer = nullptr;
        std::function<Timer::TimerFunc> func;
    public:
        ~__Timer() {
            wl_TimerDestroy(wlTimer);
        }
        void tick(double secondsSinceLast) {
            func(secondsSinceLast);
        }
        static TimerRef create(int32_t msTimeout, std::function<Timer::TimerFunc> func)
        {
            auto ret = new __Timer();
            ret->func = func;
            ret->wlTimer = wl_TimerCreate(msTimeout, ret);
            return ret;
        }
    };

    CDECL int eventHandler(wl_WindowRef wlWindow, struct wl_Event* event, void* userData) {
        if (userData != nullptr) {
            auto win = (InternalWindow*)userData;
            event->handled = true;
            switch (event->eventType) {
            case wl_kEventTypeWindowCloseRequest:
                event->closeRequestEvent.cancelClose = !win->canClose();
                break;
            case wl_kEventTypeWindowDestroyed:
                win->onDestroyed();
                // we should be able to delete the window instance now, after destroy there should be no more uses of it
                printf("Windowing event handler deleting wl private window instance\n");
                delete win;
                break;
            case wl_kEventTypeAction:
                win->onAction(event->actionEvent);
                break;
            case wl_kEventTypeMouse:
                win->onMouse(event->mouseEvent);
                break;
            case wl_kEventTypeKey:
                win->onKey(event->keyEvent);
                break;
            case wl_kEventTypeWindowRepaint:
                win->onRepaint(event->repaintEvent);
                break;
            case wl_kEventTypeD2DTargetRecreated:
                dl_D2DTargetRecreated(event->d2dTargetRecreatedEvent.newTarget, event->d2dTargetRecreatedEvent.oldTarget);
                break;
            case wl_kEventTypeWindowMoved:
                win->onMoved(event->moveEvent);
                break;
            case wl_kEventTypeWindowResized:
                win->onResized(event->resizeEvent);
                break;
            case wl_kEventTypeDrop:
                win->onDrop(event->dropEvent);
                break;
            default:
                //printf("unhandled event type: %d\n", event->eventType);
                event->handled = false;
            }
        }
        else {
            // stuff unrelated to any window (app-level events)
            event->handled = true;
            switch (event->eventType) {
            case wl_kEventTypeTimer:
                ((TimerRef)event->timerEvent.userData)->tick(event->timerEvent.secondsSinceLast);
                break;
            default:
                printf("app-level unhandled event (null userData): %d\n", event->eventType);
                event->handled = false;
            }
        }
        return 0;
    }

    // ==== module functions begin =====================================

    void moduleInit() {
        wl_PlatformOptions wlOpts = {};
        wlOpts.useDirect2D = true;
        wl_Init(&eventHandler, &wlOpts);

        dl_PlatformOptions dlOpts = {};
        dlOpts.factory = wlOpts.outParams.factory;
        dl_Init(&dlOpts);
    }

    void moduleShutdown() {
        // always flush the clipboard to render any pending stuff
        wl_ClipboardFlush();

        // final shutdown
        wl_Shutdown();
        dl_Shutdown();
    }

    void runloop() {
        wl_Runloop();
    }

    void exitRunloop() {
        wl_ExitRunloop();
    }

    namespace Icon {
        IconRef create(std::string filename, int32_t sizeToWidth) {
            return (IconRef)wl_IconLoadFromFile(filename.c_str(), sizeToWidth);
        }
    }

    void Icon_dispose(IconRef _this) {
        // TODO
    }

    namespace Accelerator {
        AcceleratorRef create(Key key, uint32_t modifiers) {
            return (AcceleratorRef)wl_AccelCreate((wl_KeyEnum)key, modifiers);
        }
    }

    void Accelerator_dispose(AcceleratorRef _this) {
        // TODO
    }

    namespace MenuAction {
        MenuActionRef create(std::string label, IconRef icon, AcceleratorRef accel, std::function<ActionFunc> func) {
            auto id = _nextMenuActionId++;
            menuActionFuncs[id] = func;
            return (MenuActionRef)wl_ActionCreate(id, label.c_str(), (wl_IconRef)icon, (wl_AcceleratorRef)accel);
        }
    }

    void MenuAction_dispose(MenuActionRef _this) {
        // TODO
    }

    void MenuItem_dispose(MenuItemRef _this) {
        // TODO
    }

    namespace Menu {
        MenuRef create() {
            return (MenuRef)wl_MenuCreate();
        }
    }

    MenuItemRef Menu_addAction(MenuRef _this, MenuActionRef action) {
        return (MenuItemRef)wl_MenuAddAction((wl_MenuRef)_this, (wl_ActionRef)action);
    }

    MenuItemRef Menu_addSubmenu(MenuRef _this, std::string label, MenuRef sub) {
        return (MenuItemRef)wl_MenuAddSubmenu((wl_MenuRef)_this, label.c_str(), (wl_MenuRef)sub);
    }

    void Menu_addSeparator(MenuRef _this) {
        wl_MenuAddSeparator((wl_MenuRef)_this);
    }

    void Menu_dispose(MenuRef _this) {
        // TODO
    }

    namespace MenuBar {
        MenuBarRef create() {
            return (MenuBarRef)wl_MenuBarCreate();
        }
    }

    void MenuBar_addMenu(MenuBarRef _this, std::string label, MenuRef menu) {
        wl_MenuBarAddMenu((wl_MenuBarRef)_this, label.c_str(), (wl_MenuRef)menu);
    }

    void MenuBar_dispose(MenuBarRef _this) {
        // TODO
    }

    const std::string kDragFormatUTF8 = wl_kDragFormatUTF8;
    const std::string kDragFormatFiles = wl_kDragFormatFiles;

    bool DropData_hasFormat(DropDataRef _this, std::string mimeFormat) {
        return wl_DropHasFormat((wl_DropDataRef)_this, mimeFormat.c_str());
    }

    std::vector<std::string> DropData_getFiles(DropDataRef _this) { // throws DropData::BadFormat
        const wl_Files* files; // not owned by us
        if (wl_DropGetFiles((wl_DropDataRef)_this, &files)) {
            std::vector<std::string> ret;
            for (auto i = 0; i < files->numFiles; i++) {
                ret.push_back(files->filenames[i]);
            }
            return ret;
        }
        else {
            throw DropData::BadFormat("wl_DropGetFiles() failed");
        }
    }

    std::string DropData_getTextUTF8(DropDataRef _this) { // throws DropData::BadFormat
        const void* data;
        size_t dataSize;
        if (wl_DropGetFormat((wl_DropDataRef)_this, wl_kDragFormatUTF8, &data, &dataSize)) {
            return std::string((const char*)data, dataSize); // pretty sure it's null-terminated but let's be safe anyway
            // we don't own or have to worry about 'data' ptr
        }
        else {
            throw DropData::BadFormat("DropData_getUTF8 failed");
        }
    }

    std::shared_ptr<NativeBuffer<uint8_t>> DropData_getFormat(DropDataRef _this, std::string mimeFormat) { // throws DropData::BadFormat
        const void* wlData;
        size_t wlDataSize;
        if (wl_DropGetFormat((wl_DropDataRef)_this, mimeFormat.c_str(), &wlData, &wlDataSize)) {
            std::vector<int> dims;
            dims.push_back((int)wlDataSize);
            auto buffer = new ServerBuffer<uint8_t>(dims);

            size_t spanSize;
            void* span = buffer->getSpan(&spanSize);
            memcpy(span, wlData, spanSize);

            return std::shared_ptr<NativeBuffer<uint8_t>>(buffer);
        }
        else
        {
            throw DropData::BadFormat("wl_DropDataGetFormat() failed");
        }
    }

    void DropData_dispose(DropDataRef _this) {
        // not necessary, it's taken care of by OpenWL
        // however we'll have a separate ClipData that will inherit, and WILL have a release because that is client responsibility
        printf("!!! DropData_dispose called, why?\n");
    }

    struct __DragData {
        // your content here
        // (or delete this and cast your own opaque ptr to 'DragDataRef' in the stubs below)
    };

    namespace DragData {
        // some ugly wrapper stuff for the drag render delegate
        // this because we're still dealing with WL's C API and can't just pass a std::function
        struct __renderFuncWrapper {
            std::function<RenderFunc> outerFunc;
            ~__renderFuncWrapper() {
                printf("~~ internal renderFuncWrapper destroyed!\n");
            }
        };

        static bool __renderFuncExec(const char* requestedFormat, wl_RenderPayloadRef payload, void* data)
        {
            __renderFuncWrapper* wrapper = (__renderFuncWrapper*)data;
            return wrapper->outerFunc(requestedFormat, (RenderPayloadRef)payload);
        }

        static void __renderFuncRelease(void* data)
        {
            delete (__renderFuncWrapper*)data;
        }

        // ========================

        void RenderPayload_renderUTF8(RenderPayloadRef _this, std::string text) {
            wl_DragRenderUTF8((wl_RenderPayloadRef)_this, text.c_str());
        }

        void RenderPayload_renderFiles(RenderPayloadRef _this, std::vector<std::string> filenames) {
            wl_Files files;
            files.numFiles = (int)filenames.size();
            files.filenames = new const char* [files.numFiles];
            for (auto i = 0; i < files.numFiles; i++) {
                files.filenames[i] = filenames[i].c_str();
            }
            wl_DragRenderFiles((wl_RenderPayloadRef)_this, &files);
            delete[] files.filenames;
        }

        void RenderPayload_renderFormat(RenderPayloadRef _this, std::string formatMIME, std::shared_ptr<NativeBuffer<uint8_t>> data) {
            size_t dataLength;
            void* dataPtr = data->getSpan(&dataLength);
            wl_DragRenderFormat((wl_RenderPayloadRef)_this, formatMIME.c_str(), dataPtr, dataLength);
        }

        void RenderPayload_dispose(RenderPayloadRef _this) {
            // we don't own these, do nothing
        }

        DragDataRef create(std::vector<std::string> supportedFormats, std::function<RenderFunc> renderFunc) {
            wl_DragRenderDelegate renderDelegate;
            renderDelegate.data = new __renderFuncWrapper{ renderFunc };
            renderDelegate.renderFunc = __renderFuncExec;
            renderDelegate.release = __renderFuncRelease;

            // don't forget to add formats!
            auto ret = wl_DragDataCreate(renderDelegate);
            for (auto i = supportedFormats.begin(); i != supportedFormats.end(); i++) {
                wl_DragAddFormat(ret, i->c_str());
            }
            return (DragDataRef)ret;
        }
    }

    uint32_t DragData_dragExec(DragDataRef _this, uint32_t canDoMask) {
        return wl_DragExec((wl_DragDataRef)_this, canDoMask, nullptr); // I think 'fromEvent' was only necessary for GTK/linux ...
    }

    void DragData_dispose(DragDataRef _this) {
        wl_DragDataRelease((wl_DragDataRef)_this);
    }

    namespace ClipData {
        void setClipboard(DragDataRef dragData) {
            wl_ClipboardSet((wl_DragDataRef)dragData);
        }

        ClipDataRef get() {
            // really just a DropDataRef
            // but we extend with ClipData so we can use wl_ClipboardRelease on dispose! fancy
            return (ClipDataRef)wl_ClipboardGet();
        }

        void flushClipboard() {
            wl_ClipboardFlush();
        }
    }

    void ClipData_dispose(ClipDataRef _this) {
        wl_ClipboardRelease((wl_DropDataRef)_this);
    }

    namespace Window {
        WindowRef create(int32_t width, int32_t height, std::string title, std::shared_ptr<WindowDelegate> del, Options opts) {
            return (WindowRef)InternalWindow::create(width, height, title, del, opts);
        }
        void mouseUngrab() {
            InternalWindow::mouseUngrab();
        }
    }

    void Window_destroy(WindowRef _this) {
        ((InternalWindow*)_this)->destroy();
    }

    void Window_show(WindowRef _this) {
        ((InternalWindow*)_this)->show();
    }

    void Window_showRelativeTo(WindowRef _this, WindowRef other, int32_t x, int32_t y, int32_t newWidth, int32_t newHeight) {
        ((InternalWindow*)_this)->showRelativeTo((InternalWindow*)other, x, y, newWidth, newHeight);
    }

    void Window_showModal(WindowRef _this, WindowRef parent) {
        ((InternalWindow*)_this)->showModal((InternalWindow*)parent);
    }

    void Window_endModal(WindowRef _this) {
        ((InternalWindow*)_this)->endModal();
    }

    void Window_hide(WindowRef _this) {
        ((InternalWindow*)_this)->hide();
    }

    void Window_invalidate(WindowRef _this, int32_t x, int32_t y, int32_t width, int32_t height) {
        ((InternalWindow*)_this)->invalidate(x, y, width, height);
    }

    void Window_setTitle(WindowRef _this, std::string title) {
        ((InternalWindow*)_this)->setTitle(title);
    }

    void Window_focus(WindowRef _this) {
        ((InternalWindow*)_this)->focus();
    }

    void Window_mouseGrab(WindowRef _this) {
        ((InternalWindow*)_this)->mouseGrab();
    }

    size_t Window_getOSHandle(WindowRef _this) {
        return ((InternalWindow*)_this)->getOSHandle();
    }

    void Window_enableDrops(WindowRef _this, bool enable) {
        ((InternalWindow*)_this)->enableDrops(enable);
    }

    void Window_setMenuBar(WindowRef _this, MenuBarRef menuBar) {
        ((InternalWindow*)_this)->setMenuBar(menuBar);
    }

    void Window_showContextMenu(WindowRef _this, int32_t x, int32_t y, MenuRef menu) {
        ((InternalWindow*)_this)->showContextMenu(x, y, menu);
    }

    void Window_setCursor(WindowRef _this, CursorStyle style) {
        ((InternalWindow*)_this)->setCursor(style);
    }

    void Window_dispose(WindowRef _this) {
        // not using this currently, requires formal destruction
    }

    namespace Timer {
        TimerRef create(int32_t msTimeout, std::function<TimerFunc> func) {
            return __Timer::create(msTimeout, func);
        }
    }

    void Timer_dispose(TimerRef _this) {
        delete _this;
    }

    namespace FileDialog {
        static std::string joinStrings(std::vector<std::string> strings, const char* delim) {
            std::string output = strings[0];
            for (auto i = 1; i < strings.size(); i++) {
                output += delim;
                output += strings[i];
            }
            return output;
        }

        // this is just complexity necessitated by sending everything over in C-friendly structs
        // namely, allocating and deallocating the various pointers that go in the wl_FileDialogOpts structure
        // another approach would have been to allocate a meta-struct holding not only the
        // wl file options, but also the string buffers holding the data whose pointers we're using
        // no compelling reason to do it this way, just having fun with C++ lambdas

        template <typename F>
        static void execWithDialogOpts(Options& src, const F& func)
        {
            wl_FileDialogOpts dest;
            dest.forWindow = src.forWindow
                ? ((InternalWindow*)src.forWindow)->getWlWindow()
                : nullptr;
            dest.mode = (wl_FileDialogOpts::Mode)src.mode;
            auto destFilters = new wl_FileDialogOpts::FilterSpec[src.filters.size()];

            std::vector<std::string> joinedExtensions; // to keep the joined strings alive until we're done

            int i = 0;
            for (auto f = src.filters.begin(); f != src.filters.end(); f++) {
                destFilters[i].desc = f->description.c_str();

                auto joined = joinStrings(f->extensions, ";");
                joinedExtensions.push_back(joined);
                destFilters[i].exts = joined.c_str();

                i++;
            }
            dest.filters = destFilters;
            dest.numFilters = (int)src.filters.size();
            dest.allowAll = src.allowAll;
            dest.defaultExt = src.defaultExt.c_str();
            dest.allowMultiple = src.allowMultiple;
            dest.suggestedFilename = src.suggestedFilename.c_str();
            //
            func(&dest);
            //
            delete[] destFilters;
        }

        DialogResult openFile(Options opts) {
            DialogResult ret;
            ret.success = false;

            execWithDialogOpts(opts, [&ret](wl_FileDialogOpts* wlOpts) {
                wl_FileResults* results;
                if (wl_FileOpenDialog(wlOpts, &results)) {
                    ret.success = true;
                    for (auto i = 0; i < results->numResults; i++) {
                        ret.filenames.push_back(results->results[i]);
                    }
                    wl_FileResultsFree(&results);
                }
                });
            return ret;
        }

        DialogResult saveFile(Options opts) {
            DialogResult ret;
            ret.success = false;

            execWithDialogOpts(opts, [&ret](wl_FileDialogOpts* wlOpts) {
                wl_FileResults* results;
                if (wl_FileSaveDialog(wlOpts, &results)) {
                    ret.success = true;
                    for (auto i = 0; i < results->numResults; i++) {
                        ret.filenames.push_back(results->results[i]);
                    }
                    wl_FileResultsFree(&results);
                }
                });
            return ret;
        }
    }

    namespace MessageBoxModal {
        MessageBoxResult show(WindowRef forWindow, Params mbParams) {
            wl_MessageBoxParams wlParams;
            wlParams.title = mbParams.title.c_str();
            wlParams.message = mbParams.message.c_str();
            wlParams.withHelpButton = mbParams.withHelpButton;
            wlParams.icon = (wl_MessageBoxParams::Icon)mbParams.icon;
            wlParams.buttons = (wl_MessageBoxParams::Buttons)mbParams.buttons;
            return (MessageBoxResult)wl_MessageBox(((InternalWindow*)forWindow)->getWlWindow(), &wlParams);
        }
    }
}
