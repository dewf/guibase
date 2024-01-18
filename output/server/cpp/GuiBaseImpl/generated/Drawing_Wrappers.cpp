#include "../support/NativeImplServer.h"
#include "Drawing_wrappers.h"
#include "Drawing.h"

NIHANDLE(drawContext);

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

void DrawContext__push(DrawContext value) {
    ni_pushPtr(value);
}

DrawContext DrawContext__pop() {
    return (DrawContext)ni_popPtr();
}

void DrawContext_saveGState__wrapper() {
    auto _this = DrawContext__pop();
    DrawContext_saveGState(_this);
}

void DrawContext_restoreGState__wrapper() {
    auto _this = DrawContext__pop();
    DrawContext_restoreGState(_this);
}

void DrawContext_setRGBFillColor__wrapper() {
    auto _this = DrawContext__pop();
    auto red = ni_popDouble();
    auto green = ni_popDouble();
    auto blue = ni_popDouble();
    auto alpha = ni_popDouble();
    DrawContext_setRGBFillColor(_this, red, green, blue, alpha);
}

void DrawContext_fillRect__wrapper() {
    auto _this = DrawContext__pop();
    auto rect = Rect__pop();
    DrawContext_fillRect(_this, rect);
}

int Drawing__register() {
    auto m = ni_registerModule("Drawing");
    ni_registerModuleMethod(m, "DrawContext_saveGState", &DrawContext_saveGState__wrapper);
    ni_registerModuleMethod(m, "DrawContext_restoreGState", &DrawContext_restoreGState__wrapper);
    ni_registerModuleMethod(m, "DrawContext_setRGBFillColor", &DrawContext_setRGBFillColor__wrapper);
    ni_registerModuleMethod(m, "DrawContext_fillRect", &DrawContext_fillRect__wrapper);
    return 0; // = OK
}
