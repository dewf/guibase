#include "generated/Windowing.h"
#include "deps/openwl/source/openwl.h"
#include "deps/opendl/source/opendl.h"

#include "generated/Drawing.h"

#include <stdio.h>

class Window2;

struct WlPrivateWrapper {
    std::shared_ptr<Window2> window;
};

static void convertProps(WindowProperties& props, wl_WindowProperties& output) {
    int minWidth, minHeight, maxWidth, maxHeight;
    WindowStyle style;
    size_t nativeParent; // HWND

    // make sure nothing by default
    output.usedFields = 0;

    if (props.hasMinWidth(&minWidth)) {
        output.usedFields |= wl_kWindowPropMinWidth;
        output.minWidth = minWidth;
    }
    if (props.hasMinHeight(&minHeight)) {
        output.usedFields |= wl_kWindowPropMinHeight;
        output.minHeight = minHeight;
    }
    if (props.hasMaxWidth(&maxWidth)) {
        output.usedFields |= wl_kWindowPropMaxWidth;
        output.maxWidth = maxWidth;
    }
    if (props.hasMaxHeight(&maxHeight)) {
        output.usedFields |= wl_kWindowPropMaxHeight;
        output.maxHeight = maxHeight;
    }
    if (props.hasStyle(&style)) {
        output.usedFields |= wl_kWindowPropStyle;
        output.style = (wl_WindowStyleEnum)style; // 1:1 mapping at the moment
    }
    if (props.hasNativeParent(&nativeParent)) {
        output.usedFields |= wl_kWindowPropNativeParent;
        output.nativeParent = (HWND)nativeParent;
    }
}

class DrawContextImpl : public ServerDrawContext {
private:
    dl_CGContextRef context;
public:
    DrawContextImpl(ID2D1RenderTarget* target) {
        context = dl_CGContextCreateD2D(target);
    }
    ~DrawContextImpl() {
        dl_CGContextRelease(context);
    }
    void setRGBFillColor(double red, double green, double blue, double alpha) override {
        dl_CGContextSetRGBFillColor(context, red, green, blue, alpha);
    }
    void fillRect(Rect rect) override {
        dl_CGContextFillRect(context, *((dl_CGRect*)&rect));
    }
};

class Window2 : public ServerIWindow {
private:
    wl_WindowRef wlWindow = nullptr;
    std::shared_ptr<IWindowDelegate> delegate_;
public:
    static std::shared_ptr<IWindow> create(int width, int height, std::string title, std::shared_ptr<IWindowDelegate> del, WindowProperties &props) {
        auto wrapper = new WlPrivateWrapper();
        
        wl_WindowProperties wlProps;
        convertProps(props, wlProps);

        auto win2 = new Window2();
        win2->wlWindow = wl_WindowCreate(width, height, title.c_str(), wrapper, &wlProps);
        win2->delegate_ = del;

        // need to hold on to this as long as the window exists ...
        wrapper->window = std::shared_ptr<Window2>(win2);

        return wrapper->window;
    }
    // interface implementation ================
    void show() override {
        wl_WindowShow(wlWindow);
    }
    void destroy() override {
        wl_WindowDestroy(wlWindow);
    }
    // event handling ==========================
    void onDestroyed() {
        delegate_->destroyed();
    }
    bool canClose() {
        return delegate_->canClose();
    }
    void onRepaint(wl_RepaintEvent& paintEvent) {
        // oooooh this is why we'd want an opaque type! client side has no business determining lifetime!
        // same probably goes for Window as well ...
        DrawContextImpl context(paintEvent.platformContext.d2d.target);
        delegate_->repaint(std::shared_ptr<DrawContext>(&context), paintEvent.x, paintEvent.y, paintEvent.width, paintEvent.height);
    }
    void onResized(wl_ResizeEvent& resizeEvent) {
    }
};


CDECL int eventHandler(wl_WindowRef wlWindow, struct wl_Event* event, void* userData) {
    if (userData != nullptr) {
        auto wrapper = (WlPrivateWrapper*)userData;
        auto win = wrapper->window;

        event->handled = true;
        switch (event->eventType) {
        case wl_kEventTypeWindowCloseRequest:
            event->closeRequestEvent.cancelClose = !win->canClose();
            break;
        case wl_kEventTypeWindowDestroyed:
            win->onDestroyed();
            // we should be able to delete the wrapper now, after destroy there should be no more uses of it
            printf("Windowing event handler deleting wl private wrapper\n");
            delete wrapper;
            break;
        case wl_kEventTypeWindowRepaint:
            win->onRepaint(event->repaintEvent);
            break;
        case wl_kEventTypeD2DTargetRecreated:
            dl_D2DTargetRecreated(event->d2dTargetRecreatedEvent.newTarget, event->d2dTargetRecreatedEvent.oldTarget);
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

std::shared_ptr<IWindow> createWindow(int32_t width, int32_t height, std::string title, std::shared_ptr<IWindowDelegate> del, WindowProperties props) {
    return Window2::create(width, height, title, del, props);
}
