#include "../support/NativeImplServer.h"
#include "Drawing.h"

ni_InterfaceMethodRef cGContext_setRGBFillColor;
ni_InterfaceMethodRef cGContext_fillRect;

void Point__push(Point value, bool isReturn) {
    ni_pushDouble(value.y);
    ni_pushDouble(value.x);
}

Point Point__pop() {
    auto x = ni_popDouble();
    auto y = ni_popDouble();
    return Point { x, y };
}

void Size__push(Size value, bool isReturn) {
    ni_pushDouble(value.height);
    ni_pushDouble(value.width);
}

Size Size__pop() {
    auto width = ni_popDouble();
    auto height = ni_popDouble();
    return Size { width, height };
}

void Rect__push(Rect value, bool isReturn) {
    Size__push(value.size, isReturn);
    Point__push(value.origin, isReturn);
}

Rect Rect__pop() {
    auto origin = Point__pop();
    auto size = Size__pop();
    return Rect { origin, size };
}

class ClientCGContext : public ClientObject, public CGContext {
public:
    ClientCGContext(int id) : ClientObject(id) {}
    void setRGBFillColor(double red, double green, double blue, double alpha) override {
        ni_pushDouble(alpha);
        ni_pushDouble(blue);
        ni_pushDouble(green);
        ni_pushDouble(red);
        invokeMethod(cGContext_setRGBFillColor);
    }
    void fillRect(Rect rect) override {
        Rect__push(rect, false);
        invokeMethod(cGContext_fillRect);
    }
};

void CGContext__push(std::shared_ptr<CGContext> inst, bool isReturn) {
    if (inst != nullptr) {
        auto pushable = std::dynamic_pointer_cast<Pushable>(inst);
        pushable->push(pushable, isReturn);
    }
    else {
        ni_pushNull();
    }
}

std::shared_ptr<CGContext> CGContext__pop()
{
    bool isClientID;
    auto id = ni_popInstance(&isClientID);
    if (id != 0) {
        if (isClientID) {
            return std::shared_ptr<CGContext>(new ClientCGContext(id));
        }
        else {
            return ServerCGContext::getByID(id);
        }
    }
    else {
        return std::shared_ptr<CGContext>();
    }
}

void CGContext_setRGBFillColor__wrapper(int serverID) {
    auto inst = ServerCGContext::getByID(serverID);
    auto red = ni_popDouble();
    auto green = ni_popDouble();
    auto blue = ni_popDouble();
    auto alpha = ni_popDouble();
    inst->setRGBFillColor(red, green, blue, alpha);
}

void CGContext_fillRect__wrapper(int serverID) {
    auto inst = ServerCGContext::getByID(serverID);
    auto rect = Rect__pop();
    inst->fillRect(rect);
}

int Drawing__init() {
    auto m = ni_registerModule("Drawing");
    auto cGContext = ni_registerInterface(m, "CGContext");
    cGContext_setRGBFillColor = ni_registerInterfaceMethod(cGContext, "setRGBFillColor", &CGContext_setRGBFillColor__wrapper);
    cGContext_fillRect = ni_registerInterfaceMethod(cGContext, "fillRect", &CGContext_fillRect__wrapper);
    return 0; // = OK
}

void Drawing__shutdown() {
}
