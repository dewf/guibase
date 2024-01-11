#include "generated/Windowing.h"

#include "windowing/win32util.h"

// this will be removed eventually:
#include "windowing/window.h"

#include <stdio.h>

void moduleInit() {
    // any sub-psuedo-modules
    win32util_init();

    Window::registerWndClass();
}

void moduleShutdown() {
	// nothing yet
}

void runloop() {
	//// hmm, doesn't this mean that any actions/accelerators created after the runloop start, won't work?
	//// will we ever need that?
	//HACCEL hAccelTable = wl_Action::createAccelTable();
	HACCEL hAccelTable = nullptr;

	// Main message loop:
	MSG msg;
	BOOL bRet;
	while ((bRet = GetMessage(&msg, nullptr, 0, 0)) != 0)
	{
		if (bRet == -1)
		{
			// handle the error and possibly exit
			printf("win32 message loop error, exiting\n");
			break;
		}
		else
		{
			//// note that thread-only (windowless) messages such as WM_WLTimerMessage / WM_WLMainThreadExecMsg
			////   are now being processed by an invisible / message-only window
			////   (because otherwise they won't be processed during modal events, like dragging the window, or DnD)
			//if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			//{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			//}
		}
	}
	//return (int)msg.wParam;
}

void exitRunloop() {
	PostQuitMessage(0);
}

std::shared_ptr<IWindow> createWindow(int32_t width, int32_t height, std::string title, std::shared_ptr<IWindowDelegate> delegate_) {
    return Window::create(width, height, title, delegate_);
}
