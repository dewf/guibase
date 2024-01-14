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

class CGContext {
public:
    virtual void setRGBFillColor(double red, double green, double blue, double alpha) = 0;
    virtual void fillRect(Rect rect) = 0;
};

// inherit from this to create server instances of CGContext
class ServerCGContext : public CGContext, public ServerObject {
public:
    virtual ~ServerCGContext() {}
    static std::shared_ptr<ServerCGContext> getByID(int id) {
        auto obj = ServerObject::getByID(id);
        return std::static_pointer_cast<ServerCGContext>(obj);
    }
};

int Drawing__register();
