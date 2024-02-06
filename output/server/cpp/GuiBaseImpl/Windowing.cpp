#include "generated/Windowing.h"
#include "deps/openwl/source/openwl.h"
#include "deps/opendl/source/opendl.h"

#include "generated/Drawing.h"

#include <stdio.h>

static std::map<int, std::function<MenuActionFunc>> menuActionFuncs;
static int _nextMenuActionId = 1;

static std::function<MenuActionFunc> actionFuncForId(int id) {
    return menuActionFuncs[id];
}

const std::string kDragFormatUTF8 = wl_kDragFormatUTF8;
const std::string kDragFormatFiles = wl_kDragFormatFiles;

static void convertProps(WindowOptions& opts, wl_WindowProperties& output) {
    int minWidth, minHeight, maxWidth, maxHeight;
    WindowStyle style;
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
public:
    static InternalWindow* create(int width, int height, std::string title, std::shared_ptr<WindowDelegate> del, WindowOptions &opts) {
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
    void setMenuBar(MenuBar mb) {
        wl_WindowSetMenuBar(wlWindow, (wl_MenuBarRef)mb);
    }
    void showContextMenu(int x, int y, Menu menu) {
        wl_WindowShowContextMenu(wlWindow, x, y, (wl_MenuRef)menu, nullptr);
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
        del->repaint((DrawContext)context, paintEvent.x, paintEvent.y, paintEvent.width, paintEvent.height);
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
            auto allowed = del->dropFeedback((DropData)dropEvent.data, dropEvent.x, dropEvent.y, dropEvent.modifiers, dropEvent.defaultModifierAction);
            dropEvent.allowedEffectMask = allowed;
            break;
        }
        case wl_kDropEventTypeLeave:
            del->dropLeave();
            break;
        case wl_kDropEventTypeDrop:
            del->dropSubmit((DropData)dropEvent.data, dropEvent.x, dropEvent.y, dropEvent.modifiers, dropEvent.defaultModifierAction);
            break;
        }
    }
};

struct __Timer {
private:
    wl_TimerRef wlTimer = nullptr;
    std::function<TimerFunc> func;
public:
    ~__Timer() {
        wl_TimerDestroy(wlTimer);
    }
    void tick(double secondsSinceLast) {
        func(secondsSinceLast);
    }
    static Timer create(int32_t msTimeout, std::function<TimerFunc> func)
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
            ((Timer)event->timerEvent.userData)->tick(event->timerEvent.secondsSinceLast);
            break;
        default:
            printf("app-level unhandled event (null userData): %d\n", event->eventType);
            event->handled = false;
        }
    }
    return 0;
}

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

bool DropData_hasFormat(DropData _this, std::string mimeFormat)
{
    return wl_DropHasFormat((wl_DropDataRef)_this, mimeFormat.c_str());
}

std::shared_ptr<NativeBuffer<uint8_t>> DropData_getFormat(DropData _this, std::string mimeFormat)
{
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
        throw DropDataBadFormat("wl_DropDataGetFormat() failed");
    }
}

std::vector<std::string> DropData_getFiles(DropData _this)
{
    const wl_Files* files; // not owned by us
    if (wl_DropGetFiles((wl_DropDataRef)_this, &files)) {
        std::vector<std::string> ret;
        for (auto i = 0; i < files->numFiles; i++) {
            ret.push_back(files->filenames[i]);
        }
        return ret;
    }
    else {
        throw DropDataBadFormat("wl_DropGetFiles() failed");
    }
}

std::string DropData_getTextUTF8(DropData _this)
{
    const void* data;
    size_t dataSize;
    if (wl_DropGetFormat((wl_DropDataRef)_this, wl_kDragFormatUTF8, &data, &dataSize)) {
        return std::string((const char *)data, dataSize); // pretty sure it's null-terminated but let's be safe anyway
        // we don't own or have to worry about 'data' ptr
    }
    else {
        throw DropDataBadFormat("DropData_getUTF8 failed");
    }
}

void DropData_dispose(DropData _this)
{
    // not necessary, it's taken care of by OpenWL
    // however we'll have a separate ClipData that will inherit, and WILL have a release because that is client responsibility
    printf("!!! DropData_dispose called, why?\n");
}

void DragData_addFormat(DragData _this, std::string dragFormatMIME)
{
    wl_DragAddFormat((wl_DragDataRef)_this, dragFormatMIME.c_str());
}


// some ugly wrapper stuff for the drag render delegate
// this because we're still dealing with WL's C API and can't just pass a std::function

struct __renderFuncWrapper {
    std::function<DragRenderFunc> outerFunc;
    ~__renderFuncWrapper() {
        printf("~~ internal renderFuncWrapper destroyed!\n");
    }
};

static bool __renderFuncExec(const char* requestedFormat, wl_RenderPayloadRef payload, void* data)
{
    __renderFuncWrapper *wrapper = (__renderFuncWrapper*)data;
    return wrapper->outerFunc(requestedFormat, (DragRenderPayload)payload);
}

static void __renderFuncRelease(void* data)
{
    delete (__renderFuncWrapper*)data;
}

DragData DragData_create(std::vector<std::string> supportedFormats, std::function<DragRenderFunc> renderFunc)
{
    wl_DragRenderDelegate renderDelegate;
    renderDelegate.data = new __renderFuncWrapper{ renderFunc };
    renderDelegate.renderFunc = __renderFuncExec;
    renderDelegate.release = __renderFuncRelease;

    // don't forget to add formats!
    auto ret = wl_DragDataCreate(renderDelegate);
    for (auto i = supportedFormats.begin(); i != supportedFormats.end(); i++) {
        wl_DragAddFormat(ret, i->c_str());
    }
    return (DragData)ret;
}

uint32_t DragData_dragExec(DragData _this, uint32_t canDoMask)
{
    return wl_DragExec((wl_DragDataRef)_this, canDoMask, nullptr); // I think 'fromEvent' was only necessary for GTK/linux ...
}

void DragData_dispose(DragData _this)
{
    wl_DragDataRelease((wl_DragDataRef)_this);
}

void DragRenderPayload_renderUTF8(DragRenderPayload _this, std::string text)
{
    wl_DragRenderUTF8((wl_RenderPayloadRef)_this, text.c_str());
}

void DragRenderPayload_renderFiles(DragRenderPayload _this, std::vector<std::string> filenames)
{
    wl_Files files;
    files.numFiles = (int) filenames.size();
    files.filenames = new const char*[files.numFiles];
    for (auto i = 0; i < files.numFiles; i++) {
        files.filenames[i] = filenames[i].c_str();
    }
    wl_DragRenderFiles((wl_RenderPayloadRef)_this, &files);
    delete[] files.filenames;
}

void DragRenderPayload_renderFormat(DragRenderPayload _this, std::string formatMIME, std::shared_ptr<NativeBuffer<uint8_t>> data)
{
    size_t dataLength;
    void* dataPtr = data->getSpan(&dataLength);
    wl_DragRenderFormat((wl_RenderPayloadRef)_this, formatMIME.c_str(), dataPtr, dataLength);
}

void DragRenderPayload_dispose(DragRenderPayload _this)
{
    // we don't own these, do nothing
}

void Window_show(Window _this) {
    ((InternalWindow*)_this)->show();
}

void Window_showRelativeTo(Window _this, Window other, int32_t x, int32_t y, int32_t newWidth, int32_t newHeight)
{
    ((InternalWindow*)_this)->showRelativeTo((InternalWindow*)other, x, y, newWidth, newHeight);
}

void Window_hide(Window _this)
{
    ((InternalWindow*)_this)->hide();
}

void Window_destroy(Window _this) {
    ((InternalWindow*)_this)->destroy();
}

void Window_setMenuBar(Window _this, MenuBar menuBar) {
    ((InternalWindow*)_this)->setMenuBar(menuBar);
}

void Window_showContextMenu(Window _this, int32_t x, int32_t y, Menu menu) {
    ((InternalWindow*)_this)->showContextMenu(x, y, menu);
}

void Window_invalidate(Window _this, int32_t x, int32_t y, int32_t width, int32_t height)
{
    ((InternalWindow*)_this)->invalidate(x, y, width, height);
}

void Window_setTitle(Window _this, std::string title)
{
    ((InternalWindow*)_this)->setTitle(title);
}

void Window_enableDrops(Window _this, bool enable)
{
    ((InternalWindow*)_this)->enableDrops(enable);
}

Window Window_create(int32_t width, int32_t height, std::string title, std::shared_ptr<WindowDelegate> del, WindowOptions opts)
{
    return (Window)InternalWindow::create(width, height, title, del, opts);
}

void Window_dispose(Window _this)
{
    // not using this currently, requires formal destruction
}

Timer Timer_create(int32_t msTimeout, std::function<TimerFunc> func)
{
    return __Timer::create(msTimeout, func);
}

void Timer_dispose(Timer _this)
{
    delete _this;
}

Icon Icon_create(std::string filename, int32_t sizeToWidth)
{
    return (Icon)wl_IconLoadFromFile(filename.c_str(), sizeToWidth);
}

void Icon_dispose(Icon _this)
{
}

void Accelerator_dispose(Accelerator _this)
{
}

Accelerator Accelerator_create(Key key, uint32_t modifiers)
{
    return (Accelerator)wl_AccelCreate((wl_KeyEnum)key, modifiers);
}

Action Action_create(std::string label, Icon icon, Accelerator accel, std::function<MenuActionFunc> func)
{
    auto id = _nextMenuActionId++;
    menuActionFuncs[id] = func;
    return (Action)wl_ActionCreate(id, label.c_str(), (wl_IconRef)icon, (wl_AcceleratorRef)accel);
}

void Action_dispose(Action _this)
{
}

void MenuItem_dispose(MenuItem _this)
{
}

void Menu_dispose(Menu _this)
{
}

MenuItem Menu_addAction(Menu _this, Action action) {
    return (MenuItem)wl_MenuAddAction((wl_MenuRef)_this, (wl_ActionRef)action);
}

MenuItem Menu_addSubmenu(Menu _this, std::string label, Menu sub) {
    return (MenuItem)wl_MenuAddSubmenu((wl_MenuRef)_this, label.c_str(), (wl_MenuRef)sub);
}

void Menu_addSeparator(Menu _this) {
    wl_MenuAddSeparator((wl_MenuRef)_this);
}

Menu Menu_create()
{
    return (Menu)wl_MenuCreate();
}

void MenuBar_dispose(MenuBar _this)
{
}

void ClipData_setClipboard(DragData dragData)
{
    wl_ClipboardSet((wl_DragDataRef)dragData);
}

ClipData ClipData_get()
{
    // really just a DropDataRef
    // but we extend with ClipData so we can use wl_ClipboardRelease on dispose! fancy
    return (ClipData)wl_ClipboardGet(); 
}

void ClipData_flushClipboard()
{
    wl_ClipboardFlush();
}

void ClipData_dispose(ClipData _this)
{
    wl_ClipboardRelease((wl_DropDataRef)_this);
}

void MenuBar_addMenu(MenuBar _this, std::string label, Menu menu) {
    wl_MenuBarAddMenu((wl_MenuBarRef)_this, label.c_str(), (wl_MenuRef)menu);
}

MenuBar MenuBar_create()
{
    return (MenuBar)wl_MenuBarCreate();
}

static std::string joinStrings(std::vector<std::string> strings, const char* delim) {
    std::string output = strings[0];
    for (auto i = 1; i < strings.size(); i++) {
        output += delim;
        output += strings[i];
    }
    return output;
}

template <typename F>
static void execWithDialogOpts(FileDialogOptions& src, const F& func)
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

FileDialogResult FileDialog_openFile(FileDialogOptions opts)
{
    FileDialogResult ret;
    ret.success = false;

    execWithDialogOpts(opts, [&ret](wl_FileDialogOpts *wlOpts) {
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

FileDialogResult FileDialog_saveFile(FileDialogOptions opts)
{
    FileDialogResult x;
    x.success = false;
    printf("FileDialog_saveFile: TODO\n");
    return x;
}

void FileDialog_dispose(FileDialog _this)
{
    // nothing to do, it's a namespace prefix only!
}
