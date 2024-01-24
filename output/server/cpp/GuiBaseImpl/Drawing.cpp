#include "generated/Drawing.h"
#include "deps/opendl/source/opendl.h"

#define STRUCT_CAST(t, v) *((t*)&v)

const AffineTransform AffineTransformIdentity = *((AffineTransform*)&dl_CGAffineTransformIdentity);

Rect makeRect(double x, double y, double width, double height)
{
    auto r = dl_CGRectMake(x, y, width, height);
    return STRUCT_CAST(Rect, r);
}

Color createColor(double red, double green, double blue, double alpha)
{
    return (Color)dl_CGColorCreateGenericRGB(red, green, blue, alpha);
}

AttributedString createAttributedString(std::string s, AttributedStringOptions opts)
{
    Font f;
    Color fg;

    auto text = dl_CFStringCreateWithCString(s.c_str());
    auto dict = dl_CFDictionaryCreateMutable(0);
    if (opts.hasFont(&f)) {
        dl_CFDictionarySetValue(dict, dl_kCTFontAttributeName, (dl_CTFontRef)f);
    }
    if (opts.hasForegroundColor(&fg)) {
        dl_CFDictionarySetValue(dict, dl_kCTForegroundColorAttributeName, (dl_CGColorRef)fg);
    }
    auto str = dl_CFAttributedStringCreate(text, dict);

    dl_CFRelease(dict);
    dl_CFRelease(text);

    return (AttributedString)str;
}

FontDescriptorArray fontManagerCreateFontDescriptorsFromURL(URL fileUrl)
{
    return (FontDescriptorArray)dl_CTFontManagerCreateFontDescriptorsFromURL((dl_CFURLRef)fileUrl);
}

Font fontCreateWithFontDescriptor(FontDescriptor descriptor, double size, AffineTransform matrix)
{
    auto res = (Font)dl_CTFontCreateWithFontDescriptor((dl_CTFontDescriptorRef)descriptor, size, (dl_CGAffineTransform*)&matrix);
    printf("fontCreateWithFontDescriptor: [%p]\n", res);
    return res;
}

Line createLineWithAttributedString(AttributedString str)
{
    return (Line)dl_CTLineCreateWithAttributedString((dl_CFAttributedStringRef)str);
}

void DrawContext_dispose(DrawContext _this)
{
    dl_CGContextRelease((dl_CGContextRef)_this);
}

void DrawContext_saveGState(DrawContext _this) {
    dl_CGContextSaveGState((dl_CGContextRef)_this);
}

void DrawContext_restoreGState(DrawContext _this) {
    dl_CGContextRestoreGState((dl_CGContextRef)_this);
}

void DrawContext_setRGBFillColor(DrawContext _this, double red, double green, double blue, double alpha) {
    dl_CGContextSetRGBFillColor((dl_CGContextRef)_this, red, green, blue, alpha);
}

void DrawContext_fillRect(DrawContext _this, Rect rect) {
    dl_CGContextFillRect((dl_CGContextRef)_this, *((dl_CGRect*)&rect));
}

void DrawContext_setTextMatrix(DrawContext _this, AffineTransform t)
{
    dl_CGContextSetTextMatrix((dl_CGContextRef)_this, *((dl_CGAffineTransform*)&t));
}

void DrawContext_setTextPosition(DrawContext _this, double x, double y)
{
    dl_CGContextSetTextPosition((dl_CGContextRef)_this, x, y);
}

void Color_dispose(Color _this)
{
    dl_CGColorRelease((dl_CGColorRef)_this);
}

void AttributedString_dispose(AttributedString _this)
{
    dl_CFRelease(_this);
}

void FontDescriptor_dispose(FontDescriptor _this)
{
    dl_CFRelease(_this);
}

void FontDescriptorArray_dispose(FontDescriptorArray _this)
{
    dl_CFRelease(_this);
}

std::vector<FontDescriptor> FontDescriptorArray_items(FontDescriptorArray _this)
{
    auto arr = (dl_CFArrayRef)_this;
    std::vector<FontDescriptor> ret;
    for (int i = 0; i < dl_CFArrayGetCount(arr); i++) {
        auto fd = (dl_CTFontDescriptorRef)dl_CFArrayGetValueAtIndex(arr, i);
        ret.push_back((FontDescriptor)fd);
    }
    // the returned items are NOT owned and so shouldn't be released
    // ideally we need a way of encoding that into the opaque type (annotated in the interface description?)
    // so that we can catch and warn about it
    return ret;
}

void Font_dispose(Font _this)
{
    dl_CFRelease(_this);
}

void Line_dispose(Line _this)
{
    dl_CFRelease(_this);
}

TypographicBounds Line_getTypographicBounds(Line _this)
{
    dl_CGFloat tb_width, ascent, descent, leading;
    tb_width = dl_CTLineGetTypographicBounds((dl_CTLineRef)_this, &ascent, &descent, &leading);
    return TypographicBounds{ tb_width, ascent, descent, leading };
}

Rect Line_getBoundsWithOptions(Line _this, uint32_t opts)
{
    auto r = dl_CTLineGetBoundsWithOptions((dl_CTLineRef)_this, (dl_CTLineBoundsOptions)opts);
    return STRUCT_CAST(Rect, r);
}

void Line_draw(Line _this, DrawContext context)
{
    dl_CTLineDraw((dl_CTLineRef)_this, (dl_CGContextRef)context);
}
