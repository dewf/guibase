#include "../support/NativeImplServer.h"
#include "Drawing_wrappers.h"
#include "Drawing.h"
#include "Foundation_wrappers.h"


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

void AttributedStringOptions__push(AttributedStringOptions value, bool isReturn) {
    Color foregroundColor;
    if (value.hasForegroundColor(&foregroundColor)) {
        Color__push(foregroundColor);
    }
    Font font;
    if (value.hasFont(&font)) {
        Font__push(font);
    }
    ni_pushInt32(value.getUsedFields());
}

AttributedStringOptions AttributedStringOptions__pop() {
    AttributedStringOptions value = {};
    value._usedFields =  ni_popInt32();
    if (value._usedFields & AttributedStringOptions::Fields::FontField) {
        auto x = Font__pop();
        value.setFont(x);
    }
    if (value._usedFields & AttributedStringOptions::Fields::ForegroundColorField) {
        auto x = Color__pop();
        value.setForegroundColor(x);
    }
    return value;
}

void AttributedString__push(AttributedString value) {
    ni_pushPtr(value);
}

AttributedString AttributedString__pop() {
    return (AttributedString)ni_popPtr();
}

void Color__push(Color value) {
    ni_pushPtr(value);
}

Color Color__pop() {
    return (Color)ni_popPtr();
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

void TypographicBounds__push(TypographicBounds value, bool isReturn) {
    ni_pushDouble(value.leading);
    ni_pushDouble(value.descent);
    ni_pushDouble(value.ascent);
    ni_pushDouble(value.width);
}

TypographicBounds TypographicBounds__pop() {
    auto width = ni_popDouble();
    auto ascent = ni_popDouble();
    auto descent = ni_popDouble();
    auto leading = ni_popDouble();
    return TypographicBounds { width, ascent, descent, leading };
}

inline void LineBoundsOptions__push(uint32_t value) {
    ni_pushUInt32(value);
}

inline uint32_t LineBoundsOptions__pop() {
    return ni_popUInt32();
}

void Line__push(Line value) {
    ni_pushPtr(value);
}

Line Line__pop() {
    return (Line)ni_popPtr();
}

void makeRect__wrapper() {
    auto x = ni_popDouble();
    auto y = ni_popDouble();
    auto width = ni_popDouble();
    auto height = ni_popDouble();
    Rect__push(makeRect(x, y, width, height), true);
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

void DrawContext_setTextMatrix__wrapper() {
    auto _this = DrawContext__pop();
    auto t = AffineTransform__pop();
    DrawContext_setTextMatrix(_this, t);
}

void DrawContext_setTextPosition__wrapper() {
    auto _this = DrawContext__pop();
    auto x = ni_popDouble();
    auto y = ni_popDouble();
    DrawContext_setTextPosition(_this, x, y);
}

void DrawContext_dispose__wrapper() {
    auto _this = DrawContext__pop();
    DrawContext_dispose(_this);
}

void Color_create__wrapper() {
    auto red = ni_popDouble();
    auto green = ni_popDouble();
    auto blue = ni_popDouble();
    auto alpha = ni_popDouble();
    Color__push(Color_create(red, green, blue, alpha));
}

void Color_dispose__wrapper() {
    auto _this = Color__pop();
    Color_dispose(_this);
}

void AttributedString_create__wrapper() {
    auto s = popStringInternal();
    auto opts = AttributedStringOptions__pop();
    AttributedString__push(AttributedString_create(s, opts));
}

void AttributedString_dispose__wrapper() {
    auto _this = AttributedString__pop();
    AttributedString_dispose(_this);
}

void FontDescriptor_dispose__wrapper() {
    auto _this = FontDescriptor__pop();
    FontDescriptor_dispose(_this);
}

void FontDescriptorArray_items__wrapper() {
    auto _this = FontDescriptorArray__pop();
    __FontDescriptor_Array__push(FontDescriptorArray_items(_this), true);
}

void FontDescriptorArray_dispose__wrapper() {
    auto _this = FontDescriptorArray__pop();
    FontDescriptorArray_dispose(_this);
}

void Font_dispose__wrapper() {
    auto _this = Font__pop();
    Font_dispose(_this);
}

void Line_getTypographicBounds__wrapper() {
    auto _this = Line__pop();
    TypographicBounds__push(Line_getTypographicBounds(_this), true);
}

void Line_getBoundsWithOptions__wrapper() {
    auto _this = Line__pop();
    auto opts = LineBoundsOptions__pop();
    Rect__push(Line_getBoundsWithOptions(_this, opts), true);
}

void Line_draw__wrapper() {
    auto _this = Line__pop();
    auto context = DrawContext__pop();
    Line_draw(_this, context);
}

void Line_createWithAttributedString__wrapper() {
    auto str = AttributedString__pop();
    Line__push(Line_createWithAttributedString(str));
}

void Line_dispose__wrapper() {
    auto _this = Line__pop();
    Line_dispose(_this);
}

void __constantsFunc() {
    AffineTransform__push(AffineTransformIdentity, false);
}

int Drawing__register() {
    auto m = ni_registerModule("Drawing");
    ni_registerModuleConstants(m, &__constantsFunc);
    ni_registerModuleMethod(m, "makeRect", &makeRect__wrapper);
    ni_registerModuleMethod(m, "fontManagerCreateFontDescriptorsFromURL", &fontManagerCreateFontDescriptorsFromURL__wrapper);
    ni_registerModuleMethod(m, "fontCreateWithFontDescriptor", &fontCreateWithFontDescriptor__wrapper);
    ni_registerModuleMethod(m, "DrawContext_saveGState", &DrawContext_saveGState__wrapper);
    ni_registerModuleMethod(m, "DrawContext_restoreGState", &DrawContext_restoreGState__wrapper);
    ni_registerModuleMethod(m, "DrawContext_setRGBFillColor", &DrawContext_setRGBFillColor__wrapper);
    ni_registerModuleMethod(m, "DrawContext_fillRect", &DrawContext_fillRect__wrapper);
    ni_registerModuleMethod(m, "DrawContext_setTextMatrix", &DrawContext_setTextMatrix__wrapper);
    ni_registerModuleMethod(m, "DrawContext_setTextPosition", &DrawContext_setTextPosition__wrapper);
    ni_registerModuleMethod(m, "DrawContext_dispose", &DrawContext_dispose__wrapper);
    ni_registerModuleMethod(m, "Color_create", &Color_create__wrapper);
    ni_registerModuleMethod(m, "Color_dispose", &Color_dispose__wrapper);
    ni_registerModuleMethod(m, "AttributedString_create", &AttributedString_create__wrapper);
    ni_registerModuleMethod(m, "AttributedString_dispose", &AttributedString_dispose__wrapper);
    ni_registerModuleMethod(m, "FontDescriptor_dispose", &FontDescriptor_dispose__wrapper);
    ni_registerModuleMethod(m, "FontDescriptorArray_items", &FontDescriptorArray_items__wrapper);
    ni_registerModuleMethod(m, "FontDescriptorArray_dispose", &FontDescriptorArray_dispose__wrapper);
    ni_registerModuleMethod(m, "Font_dispose", &Font_dispose__wrapper);
    ni_registerModuleMethod(m, "Line_getTypographicBounds", &Line_getTypographicBounds__wrapper);
    ni_registerModuleMethod(m, "Line_getBoundsWithOptions", &Line_getBoundsWithOptions__wrapper);
    ni_registerModuleMethod(m, "Line_draw", &Line_draw__wrapper);
    ni_registerModuleMethod(m, "Line_createWithAttributedString", &Line_createWithAttributedString__wrapper);
    ni_registerModuleMethod(m, "Line_dispose", &Line_dispose__wrapper);
    return 0; // = OK
}
