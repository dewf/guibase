#include "../support/NativeImplServer.h"
#include "Drawing_wrappers.h"
#include "Drawing.h"
#include "Foundation_wrappers.h"

NIHANDLE(drawContext);
NIHANDLE(fontDescriptor);
NIHANDLE(fontDescriptorArray);
NIHANDLE(font);

void AffineTransform__push(AffineTransform value, bool isReturn) {
    ni_pushDouble(value.ty);
    ni_pushDouble(value.tx);
    ni_pushDouble(value.d);
    ni_pushDouble(value.c);
    ni_pushDouble(value.b);
    ni_pushDouble(value.a);
}

AffineTransform AffineTransform__pop() {
    auto a = ni_popDouble();
    auto b = ni_popDouble();
    auto c = ni_popDouble();
    auto d = ni_popDouble();
    auto tx = ni_popDouble();
    auto ty = ni_popDouble();
    return AffineTransform { a, b, c, d, tx, ty };
}

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

void Font__push(Font value) {
    ni_pushPtr(value);
}

Font Font__pop() {
    return (Font)ni_popPtr();
}

void FontDescriptor__push(FontDescriptor value) {
    ni_pushPtr(value);
}

FontDescriptor FontDescriptor__pop() {
    return (FontDescriptor)ni_popPtr();
}

void __FontDescriptor_Array__push(std::vector<FontDescriptor> items, bool isReturn) {
    ni_pushPtrArray((void**)items.data(), items.size());
}

std::vector<FontDescriptor> __FontDescriptor_Array__pop() {
    FontDescriptor *values;
    size_t count;
    ni_popPtrArray((void***)&values, &count);
    return std::vector<FontDescriptor>(values, values + count);
}

void FontDescriptorArray__push(FontDescriptorArray value) {
    ni_pushPtr(value);
}

FontDescriptorArray FontDescriptorArray__pop() {
    return (FontDescriptorArray)ni_popPtr();
}

void fontManagerCreateFontDescriptorsFromURL__wrapper() {
    auto fileUrl = URL__pop();
    FontDescriptorArray__push(fontManagerCreateFontDescriptorsFromURL(fileUrl));
}

void fontCreateWithFontDescriptor__wrapper() {
    auto descriptor = FontDescriptor__pop();
    auto size = ni_popDouble();
    auto matrix = AffineTransform__pop();
    Font__push(fontCreateWithFontDescriptor(descriptor, size, matrix));
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

void FontDescriptorArray_items__wrapper() {
    auto _this = FontDescriptorArray__pop();
    __FontDescriptor_Array__push(FontDescriptorArray_items(_this), true);
}

void __constantsFunc() {
    AffineTransform__push(AffineTransformIdentity, false);
}

int Drawing__register() {
    auto m = ni_registerModule("Drawing");
    ni_registerModuleConstants(m, &__constantsFunc);
    ni_registerModuleMethod(m, "fontManagerCreateFontDescriptorsFromURL", &fontManagerCreateFontDescriptorsFromURL__wrapper);
    ni_registerModuleMethod(m, "fontCreateWithFontDescriptor", &fontCreateWithFontDescriptor__wrapper);
    ni_registerModuleMethod(m, "DrawContext_saveGState", &DrawContext_saveGState__wrapper);
    ni_registerModuleMethod(m, "DrawContext_restoreGState", &DrawContext_restoreGState__wrapper);
    ni_registerModuleMethod(m, "DrawContext_setRGBFillColor", &DrawContext_setRGBFillColor__wrapper);
    ni_registerModuleMethod(m, "DrawContext_fillRect", &DrawContext_fillRect__wrapper);
    ni_registerModuleMethod(m, "FontDescriptorArray_items", &FontDescriptorArray_items__wrapper);
    return 0; // = OK
}
