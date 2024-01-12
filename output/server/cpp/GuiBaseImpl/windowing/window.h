#pragma once

#include "../generated/Windowing.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <d2d1_1.h>

class Window : public ServerIWindow {
private:
	HWND hWnd = NULL;
	std::shared_ptr<IWindowDelegate> delegate_;

	UINT dpi;
	int clientWidth = -1;
	int clientHeight = -1;
	int extraWidth = -1;    // difference between client size and window size
	int extraHeight = -1;

	DWORD dwStyle = 0;
	bool hasMenu = false;

	ID2D1HwndRenderTarget* d2dRenderTarget = nullptr;

	WindowProperties props;

	void direct2DCreateTarget();
public:
// IWindow interface
	void show() override;
	void destroy() override;
// wndProc event handling (keeps it tidy in there)
	bool canClose();
	void onMouseButton(UINT message, WPARAM wParam, LPARAM lParam);
	void onDestroyed();
	void onDPIChanged(UINT newDPI, RECT* suggestedRect);
	void onGetMinMaxInfo(LPARAM lParam);
// static
	static void init();
	static void shutdown();
	static std::shared_ptr<Window> create(int32_t dipWidth, int32_t dipHeight, std::string title, std::shared_ptr<IWindowDelegate> del, WindowProperties &props);
};
