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
    // opaque methods ==========================
    void show() {
        wl_WindowShow(wlWindow);
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

void DropData_dispose(DropData _this)
{
    // not necessary, it's taken care of by OpenWL
    // however we'll have a separate ClipData that will inherit, and WILL have a release because that is client responsibility
    printf("!!! DropData_dispose called, why?\n");
}

void Window_show(Window _this) {
    ((InternalWindow*)_this)->show();
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

MenuItem MenuBar_addMenu(MenuBar _this, std::string label, Menu menu) {
    return (MenuItem)wl_MenuBarAddMenu((wl_MenuBarRef)_this, label.c_str(), (wl_MenuRef)menu);
}

MenuBar MenuBar_create()
{
    return (MenuBar)wl_MenuBarCreate();
}

