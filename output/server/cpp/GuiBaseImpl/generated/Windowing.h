#pragma once

#include "../support/NativeImplServer.h"
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <set>

class IWindow {
public:
    virtual void show() = 0;
    virtual void destroy() = 0;
};

// inherit from this to create server instances of IWindow
class ServerIWindow : public IWindow, public ServerObject {
public:
    virtual ~ServerIWindow() {}
    static std::shared_ptr<ServerIWindow> getByID(int id) {
        auto obj = ServerObject::getByID(id);
        return std::static_pointer_cast<ServerIWindow>(obj);
    }
};

enum class MouseButton {
    None,
    Left,
    Middle,
    Right,
    Other
};

enum class Modifiers {
    Shift,
    Control,
    Alt,
    MacControl
};

// std::set<Modifiers>

class IWindowDelegate {
public:
    virtual bool canClose() = 0;
    virtual void closed() = 0;
    virtual void destroyed() = 0;
    virtual void mouseDown(int32_t x, int32_t y, MouseButton button, std::set<Modifiers> modifiers) = 0;
};

// inherit from this to create server instances of IWindowDelegate
class ServerIWindowDelegate : public IWindowDelegate, public ServerObject {
public:
    virtual ~ServerIWindowDelegate() {}
    static std::shared_ptr<ServerIWindowDelegate> getByID(int id) {
        auto obj = ServerObject::getByID(id);
        return std::static_pointer_cast<ServerIWindowDelegate>(obj);
    }
};

void moduleInit();
void moduleShutdown();
void runloop();
void exitRunloop();
std::shared_ptr<IWindow> createWindow(int32_t width, int32_t height, std::string title, std::shared_ptr<IWindowDelegate> del);
