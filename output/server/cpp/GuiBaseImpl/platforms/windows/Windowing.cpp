#include "../../generated/Windowing.h"

#include <stdio.h>

void moduleInit() {
    printf("Hello from reorganized project!\n");
}

void moduleShutdown() {
    printf("goodbye from shutdown! we are less alive\n");
}

void runloop() {
}

void exitRunloop() {
}

std::shared_ptr<Window> createWindow(int32_t width, int32_t height, std::string title, std::shared_ptr<WindowDelegate> del) {
    return std::shared_ptr<Window>();
}
