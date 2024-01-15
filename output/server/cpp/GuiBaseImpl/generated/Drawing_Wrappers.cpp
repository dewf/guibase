#include "../support/NativeImplServer.h"
#include "Drawing.h"

ni_InterfaceMethodRef drawContext_saveGState;
ni_InterfaceMethodRef drawContext_restoreGState;
ni_InterfaceMethodRef drawContext_setRGBFillColor;
ni_InterfaceMethodRef drawContext_fillRect;

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

class ClientDrawContext : public ClientObject, public DrawContext {
public:
    ClientDrawContext(int id) : ClientObject(id) {}
    void saveGState() override {
        invokeMethod(drawContext_saveGState);
    }
    void restoreGState() override {
        invokeMethod(drawContext_restoreGState);
    }
    void setRGBFillColor(double red, double green, double blue, double alpha) override {
        ni_pushDouble(alpha);
        ni_pushDouble(blue);
        ni_pushDouble(green);
        ni_pushDouble(red);
        invokeMethod(drawContext_setRGBFillColor);
    }
    void fillRect(Rect rect) override {
        Rect__push(rect, false);
        invokeMethod(drawContext_fillRect);
    }
};

void DrawContext__push(std::shared_ptr<DrawContext> inst, bool isReturn) {
    if (inst != nullptr) {
        auto pushable = std::dynamic_pointer_cast<Pushable>(inst);
        pushable->push(pushable, isReturn);
    }
    else {
        ni_pushNull();
    }
}

std::shared_ptr<DrawContext> DrawContext__pop()
{
    bool isClientID;
    auto id = ni_popInstance(&isClientID);
    if (id != 0) {
        if (isClientID) {
            return std::shared_ptr<DrawContext>(new ClientDrawContext(id));
        }
        else {
            return ServerDrawContext::getByID(id);
        }
    }
    else {
        return std::shared_ptr<DrawContext>();
    }
}

void DrawContext_saveGState__wrapper(int serverID) {
    auto inst = ServerDrawContext::getByID(serverID);
    inst->saveGState();
}

void DrawContext_restoreGState__wrapper(int serverID) {
    auto inst = ServerDrawContext::getByID(serverID);
    inst->restoreGState();
}

void DrawContext_setRGBFillColor__wrapper(int serverID) {
    auto inst = ServerDrawContext::getByID(serverID);
    auto red = ni_popDouble();
    auto green = ni_popDouble();
    auto blue = ni_popDouble();
    auto alpha = ni_popDouble();
    inst->setRGBFillColor(red, green, blue, alpha);
}

void DrawContext_fillRect__wrapper(int serverID) {
    auto inst = ServerDrawContext::getByID(serverID);
    auto rect = Rect__pop();
    inst->fillRect(rect);
}

int Drawing__register() {
    auto m = ni_registerModule("Drawing");
    auto drawContext = ni_registerInterface(m, "DrawContext");
    drawContext_saveGState = ni_registerInterfaceMethod(drawContext, "saveGState", &DrawContext_saveGState__wrapper);
    drawContext_restoreGState = ni_registerInterfaceMethod(drawContext, "restoreGState", &DrawContext_restoreGState__wrapper);
    drawContext_setRGBFillColor = ni_registerInterfaceMethod(drawContext, "setRGBFillColor", &DrawContext_setRGBFillColor__wrapper);
    drawContext_fillRect = ni_registerInterfaceMethod(drawContext, "fillRect", &DrawContext_fillRect__wrapper);
    return 0; // = OK
}
