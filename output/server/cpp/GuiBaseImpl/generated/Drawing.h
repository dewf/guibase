#pragma once

#include "../support/NativeImplServer.h"
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <set>

struct Point {
    double x;
    double y;
};

struct Size {
    double width;
    double height;
};

struct Rect {
    Point origin;
    Size size;
};

class DrawContext {
public:
    virtual void saveGState() = 0;
    virtual void restoreGState() = 0;
    virtual void setRGBFillColor(double red, double green, double blue, double alpha) = 0;
    virtual void fillRect(Rect rect) = 0;
};

// inherit from this to create server instances of DrawContext
class ServerDrawContext : public DrawContext, public ServerObject {
public:
    virtual ~ServerDrawContext() {}
    static std::shared_ptr<ServerDrawContext> getByID(int id) {
        auto obj = ServerObject::getByID(id);
        return std::static_pointer_cast<ServerDrawContext>(obj);
    }
};

int Drawing__register();
