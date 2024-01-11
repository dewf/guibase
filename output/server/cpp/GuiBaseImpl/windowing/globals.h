#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

//#include <mutex>
//#include <condition_variable>

//use this so we don't have to have the DllMain talk to us
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
//extern HINSTANCE hInstance; // set by DllMain

//extern const WCHAR* topLevelWindowClass;
//extern const WCHAR* appGlobalWindowClass;
//
//extern DWORD mainThreadID;
//
//extern HWND appGlobalWindow; // for receiving messages that don't belong to any window (see comments at point of creation for more)
//
//// custom wndproc messages (currently just for our app-global messages)
//enum Win32MessageEnum : UINT {
//	Nothing = WM_USER,
//	// custom window messages here
//	AppGlobalMsgBegin = Nothing + 0x500,
//	// custom app (main thread) messages here
//	WM_WLTimerMessage,
//	WM_WLMainThreadExecMsg,
//};
//
//// timer stuff
//extern LARGE_INTEGER perfCounterTicksPerSecond;
//
//// direct2D stuff
//extern bool useDirect2D;
//
//// for wl_ExecuteOnMainThread
//extern std::mutex execMutex;
//
//struct MainThreadExecItem {
//	wl_VoidCallback callback;
//	void* data;
//	std::condition_variable& execCond;
//};
//
//void ExecuteMainItem(MainThreadExecItem* item); // defined in wndproc.cpp
//
//// client-supplied callback
//extern wl_EventCallback eventCallback;
