#pragma once

#include "../generated/Windowing.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class Window : public ServerIWindow {
private:
	UINT dpi;
	HWND _hWnd;
	std::shared_ptr<IWindowDelegate> _delegate;
public:
// IWindow interface
	void show() override;
	void destroy() override;
// public events (wndProc handling, keeps it tidy in there)
	bool canClose();
	void onMouseButton(UINT message, WPARAM wParam, LPARAM lParam);
	void onDestroyed();
// static
	static std::shared_ptr<Window> create(int32_t dipWidth, int32_t dipHeight, std::string title, std::shared_ptr<IWindowDelegate> del);
	static void registerWndClass();
};

// we associate this with the hWND since it can't hold shared_ptrs
struct HWndUserData {
	std::shared_ptr<Window> window;
};
