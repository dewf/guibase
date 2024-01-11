#include "window.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <windowsx.h> // for some macros (GET_X_LPARAM etc)

#include "unicodestuff.h"
#include "win32util.h"
#include "globals.h"
#include "comstuff.h"

#include <ole2.h> // for MK_ALT, strangely enough ... do these not work with mouse clicks? alt+click not possible, except when dnd dragging?

// DPI macros ===============
#define DECLSF(dpi) double scaleFactor = (dpi) / 96.0;
#define INT(x) ((int)(x))
#define DPIUP(x) INT((x) * scaleFactor)                // from device-independent pixels to physical res
#define DPIDOWN(x) INT((x) / scaleFactor)              // from physical res to DIPs
#define DPIUP_INPLACE(x) x = DPIUP(x);
#define DPIDOWN_INPLACE(x) x = DPIDOWN(x);

// private types ============

// we associate this with the hWND since it can't hold shared_ptrs
struct HWndUserData {
	std::shared_ptr<Window> window;
};

// static definitions =======
static const WCHAR* topLevelWindowClass = L"OpenWLTopLevel";
static ID2D1Factory1* d2dFactory = nullptr;

// forward decls ============
LRESULT CALLBACK topLevelWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void calcChromeExtra(int* extraWidth, int* extraHeight, DWORD dwStyle, bool hasMenu, UINT dpi) {
	const int arbitraryExtent = 500;
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = arbitraryExtent; // just some arbitrary extents -- it's the difference we're interested in
	rect.bottom = arbitraryExtent;

	AdjustWindowRectExForDpi(&rect, dwStyle, hasMenu, 0, dpi);

	*extraWidth = (rect.right - rect.left) - arbitraryExtent;  // left and top will be negative, hence the subtraction (right - left) = outer width
	*extraHeight = (rect.bottom - rect.top) - arbitraryExtent; // bottom - top = outer height
}

long getWindowStyle(void* props, bool isPluginWindow) {
	//long dwStyle = WS_OVERLAPPEDWINDOW;
	//if (isPluginWindow) {
	//	dwStyle = WS_CHILD;
	//}
	//else if (props && (props->usedFields & wl_kWindowPropStyle)) {
	//	switch (props->style) {
	//	case wl_kWindowStyleDefault:
	//		dwStyle = WS_OVERLAPPEDWINDOW;
	//		break;
	//	case wl_kWindowStyleFrameless:
	//		dwStyle = WS_POPUP | WS_BORDER;
	//		break;
	//	default:
	//		printf("wl_WindowCreate: unknown window style\n");
	//		break;
	//	}
	//}
	//return dwStyle;
	return WS_OVERLAPPEDWINDOW;
}

std::set<Modifiers> getMouseModifiers(WPARAM wParam) {
	std::set<Modifiers> modifiers;
	auto fwKeys = GET_KEYSTATE_WPARAM(wParam);
	if (fwKeys & MK_CONTROL) {
		modifiers.insert(Modifiers::Control);
	}
	if (fwKeys & MK_SHIFT) {
		modifiers.insert(Modifiers::Shift);
	}
	if (fwKeys & MK_ALT) {
		modifiers.insert(Modifiers::Alt);
	}
	return modifiers;
}

void Window::direct2DCreateTarget()
{
	ID2D1RenderTarget* oldTarget = d2dRenderTarget;
	if (d2dRenderTarget) {
		d2dRenderTarget->Release();
		d2dRenderTarget = nullptr;
	}
	// Create a Direct2D render target
	auto rtprops = D2D1::RenderTargetProperties();
	rtprops.dpiX = (FLOAT)dpi;
	rtprops.dpiY = (FLOAT)dpi;
	auto hrtprops = D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(clientWidth, clientHeight));
	HR(d2dFactory->CreateHwndRenderTarget(&rtprops, &hrtprops, &d2dRenderTarget));

	// TODO: used to be an OpenWL event here
	// now we need to call
	// dl_D2DTargetRecreated(event->d2dTargetRecreatedEvent.newTarget, event->d2dTargetRecreatedEvent.oldTarget);
}

void Window::show()
{
	ShowWindow(hWnd, SW_SHOWNORMAL); // might need to use a different cmd based on whether first time or not
	UpdateWindow(hWnd);
}

void Window::destroy()
{
	//unregisterDropWindow();
	DestroyWindow(hWnd);
	// I guess we will have to wait until the wndProc destroy to get called, 
	//   before we destroy the HWndUserData, which possibly holds the last shared_ptr reference to our window class
	// otherwise the destroy event would go to a deleted Window instance
}

bool Window::canClose()
{
	return delegate_->canClose();
}

void Window::onDestroyed() {
	delegate_->destroyed();
}

void Window::onDPIChanged(UINT newDPI, RECT* suggestedRect)
{
	dpi = newDPI;

	// recalc extraWidth/extraHeight for resize constraints
	calcChromeExtra(&extraWidth, &extraHeight, dwStyle, hasMenu, dpi);

	auto x = suggestedRect->left;
	auto y = suggestedRect->top;
	auto width = suggestedRect->right - suggestedRect->left;
	auto height = suggestedRect->bottom - suggestedRect->top;
	SetWindowPos(hWnd, HWND_TOP, x, y, width, height, 0);

	// recreate target with new DPI
	direct2DCreateTarget();
}

void Window::onMouseButton(UINT message, WPARAM wParam, LPARAM lParam)
{
	// process mouse events
	DECLSF(dpi);

	// down/up
	auto mouseUp = false;
	switch (message) {
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		mouseUp = true;
		break;
	}

	// button
	auto button = MouseButton::None;
	switch (message) {
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
		button = MouseButton::Left;
		break;
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
		button = MouseButton::Middle;
		break;
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
		button = MouseButton::Right;
		break;
	}

	auto x = DPIDOWN(GET_X_LPARAM(lParam));
	auto y = DPIDOWN(GET_Y_LPARAM(lParam));
	auto modifiers = getMouseModifiers(wParam);

	if (mouseUp) {
		// todo
	}
	else {
		delegate_->mouseDown(x, y, button, modifiers);
	}
}

// static
std::shared_ptr<Window> Window::create(int32_t dipWidth, int32_t dipHeight, std::string title, std::shared_ptr<IWindowDelegate> del)
{
    auto wideTitle = utf8_to_wstring(title);
	int extraWidth = 0;
	int extraHeight = 0;

	auto dwStyle = getWindowStyle(nullptr, false);

	// these need to be set by either branch below
	UINT dpi;
	int width, height;

	// omitted for now: plugin window branch
	// create actual win32 window
	HWND hWnd = nullptr;

	// get DPI and default position on whichever monitor Windows wants us on
	int defaultX, defaultY;
	probeDefaultWindowPos(&defaultX, &defaultY, &dpi);

	DECLSF(dpi);
	width = DPIUP(dipWidth);
	height = DPIUP(dipHeight);
	// note: we don't fix props -- the min/max/width/height all stay in DIPs, 
	//   because window might get dragged between monitors of different DPI
	// so just recalc (DPIUP) from props each time (wl_Window::onGetMinMaxInfo)

	calcChromeExtra(&extraWidth, &extraHeight, dwStyle, FALSE, dpi); // FALSE = no menu for now ... will recalc when the time comes

	auto exStyle = (dwStyle & WS_POPUP) ? WS_EX_TOOLWINDOW : 0; // no taskbar button plz

	hWnd = CreateWindowExW(exStyle, topLevelWindowClass, wideTitle.c_str(), dwStyle,
		defaultX, defaultY,
		width + extraWidth, height + extraHeight, nullptr, nullptr, HINST_THISCOMPONENT, nullptr);

	if (hWnd) {
		// associate data
		auto win = new Window();
		win->hWnd = hWnd;
		win->delegate_ = del;
		win->dpi = dpi;
		win->dwStyle = dwStyle;
		win->clientWidth = width;
		win->clientHeight = height;
		win->extraWidth = extraWidth;
		win->extraHeight = extraHeight;
		//wlw->dropTarget = nullptr;
		//wlw->props.usedFields = 0;
		//if (props != nullptr) {
		//	memcpy(&wlw->props, props, sizeof(wl_WindowProperties));
		//}
		auto userData = new HWndUserData();
		userData->window = std::shared_ptr<Window>(win);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)userData);

		win->direct2DCreateTarget();

		return userData->window;
	}
	// else
	return std::shared_ptr<Window>();
}

// static
void Window::init()
{
	HR(OleInitialize(nullptr));
	HR(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2dFactory));

	registerWindowClass(topLevelWindowClass, topLevelWindowProc);
}

void Window::shutdown()
{
	SafeRelease(&d2dFactory);
	OleUninitialize();
}

LRESULT CALLBACK topLevelWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	auto userData = (HWndUserData*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	if (userData) {
		// here we will invoke Window:: methods
		switch (message)
		{
		case WM_ERASEBKGND:
			//printf("nothx erase background!\n");
			return 1; // nonzero = we're handling background erasure -- keeps windows from doing it
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
			userData->window->onMouseButton(message, wParam, lParam);
			break;
		case WM_DESTROY:
			userData->window->onDestroyed();
			// this shoooooooould be the last possible message to the window ...
			printf("WM_DESTROY - deleting userData from window\n");
			delete userData;
			break;
		case WM_CLOSE:
			if (userData->window->canClose()) {
				// onward to destruction ...
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
			else {
				// cancelled, return 0
			}
			break;
		case WM_DPICHANGED: {
			userData->window->onDPIChanged(LOWORD(wParam), (RECT*)lParam);
			break;
		}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;
	}
	else {
		// do we need to process anything with a null userData? WM_CREATE perhaps?
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
