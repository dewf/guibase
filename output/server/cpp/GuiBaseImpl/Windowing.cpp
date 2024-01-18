#include "generated/Windowing.h"
#include "deps/openwl/source/openwl.h"
#include "deps/opendl/source/opendl.h"

#include "generated/Drawing.h"

#include <stdio.h>

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

class MyWindow {
private:
    wl_WindowRef wlWindow = nullptr;
    std::shared_ptr<WindowDelegate> del;
public:
    static MyWindow* create(int width, int height, std::string title, std::shared_ptr<WindowDelegate> del, WindowOptions &opts) {
        wl_WindowProperties wlProps;
        convertProps(opts, wlProps);

        auto win2 = new MyWindow();
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
    // OpenWL event handling ==========================
    void onDestroyed() {
        del->destroyed();
    }
    bool canClose() {
        return del->canClose();
    }
    void onRepaint(wl_RepaintEvent& paintEvent) {
        auto context = dl_CGContextCreateD2D(paintEvent.platformContext.d2d.target);
        del->repaint((DrawContext)context, paintEvent.x, paintEvent.y, paintEvent.width, paintEvent.height);
        dl_CGContextRelease(context);
    }
    void onResized(wl_ResizeEvent& resizeEvent) {
        del->resized(resizeEvent.newWidth, resizeEvent.newHeight);
    }
};


CDECL int eventHandler(wl_WindowRef wlWindow, struct wl_Event* event, void* userData) {
    if (userData != nullptr) {
        auto win = (MyWindow*)userData;

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

Window createWindow(int32_t width, int32_t height, std::string title, std::shared_ptr<WindowDelegate> del, WindowOptions opts) {
    return (Window)MyWindow::create(width, height, title, del, opts);
}

void Window_show(Window _this) {
    ((MyWindow*)_this)->show();
}

void Window_destroy(Window _this) {
    ((MyWindow*)_this)->destroy();
}
