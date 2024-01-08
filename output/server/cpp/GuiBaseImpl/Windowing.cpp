#include "generated/Windowing.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <stdio.h>

//use this so we don't have to have the DllMain talk to us
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)

void moduleInit() {
    printf("woot nucca\n");
}

void moduleShutdown() {
}

void runloop() {
}

void exitRunloop() {
}

std::shared_ptr<IWindow> createWindow(int32_t width, int32_t height, std::string title, std::shared_ptr<IWindowDelegate> del) {
    return std::shared_ptr<IWindow>();
}
