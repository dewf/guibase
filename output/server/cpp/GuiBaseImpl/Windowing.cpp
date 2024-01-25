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
        }
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
        case wl_kEventTypeWindowRepaint:
            win->onRepaint(event->repaintEvent);
            break;
        case wl_kEventTypeD2DTargetRecreated:
            dl_D2DTargetRecreated(event->d2dTargetRecreatedEvent.newTarget, event->d2dTargetRecreatedEvent.oldTarget);
            break;
        case wl_kEventTypeWindowResized:
            win->onResized(event->resizeEvent);
            break;
        default:
            //printf("unhandled event type: %d\n", event->eventType);
            event->handled = false;
        }
    }
    else {
        //printf("unhandled event type (null userData): %d\n", event->eventType);
        event->handled = false;
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

Window Window_create(int32_t width, int32_t height, std::string title, std::shared_ptr<WindowDelegate> del, WindowOptions opts)
{
    return (Window)InternalWindow::create(width, height, title, del, opts);
}

void Window_dispose(Window _this)
{
    // not using this currently, requires formal destruction
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

