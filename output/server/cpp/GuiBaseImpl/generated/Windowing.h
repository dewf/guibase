#include "../support/NativeImplServer.h"
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <set>

enum class MouseButton {
    None,
    Left,
    Middle,
    Right,
    Other
};

class Window {
public:
    virtual void show() = 0;
    virtual void destroy() = 0;
};

// inherit from this to create server instances of Window
class ServerWindow : public Window, public ServerObject {
public:
    virtual ~ServerWindow() {}
    static std::shared_ptr<ServerWindow> getByID(int id) {
        auto obj = ServerObject::getByID(id);
        return std::static_pointer_cast<ServerWindow>(obj);
    }
};

class WindowDelegate {
public:
    virtual void buttonClicked(int32_t x, int32_t y, MouseButton button) = 0;
    virtual void closed() = 0;
};

// inherit from this to create server instances of WindowDelegate
class ServerWindowDelegate : public WindowDelegate, public ServerObject {
public:
    virtual ~ServerWindowDelegate() {}
    static std::shared_ptr<ServerWindowDelegate> getByID(int id) {
        auto obj = ServerObject::getByID(id);
        return std::static_pointer_cast<ServerWindowDelegate>(obj);
    }
};

void moduleInit();
void moduleShutdown();
void runloop();
void exitRunloop();
std::shared_ptr<Window> createWindow(int32_t width, int32_t height, std::string title, std::shared_ptr<WindowDelegate> del);
