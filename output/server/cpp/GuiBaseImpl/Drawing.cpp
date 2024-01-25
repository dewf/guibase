#include "generated/Drawing.h"
#include "deps/opendl/source/opendl.h"

#define STRUCT_CAST(t, v) *((t*)&v)

const AffineTransform AffineTransformIdentity = *((AffineTransform*)&dl_CGAffineTransformIdentity);

Rect makeRect(double x, double y, double width, double height)
{
    auto r = dl_CGRectMake(x, y, width, height);
    return STRUCT_CAST(Rect, r);
}

void DrawContext_dispose(DrawContext _this)
{
    // hmm this might have end-user value when for example drawing into bitmaps?
    // but for window repainting we must never call .dispose() ...
    // would be nice to annotate the API to indicate ownership or something
    // (some .get() accessors for example returning non-owned copies of things, whereas .create() stuff is owned by convention)
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

Color Color_create(double red, double green, double blue, double alpha)
{
    return (Color)dl_CGColorCreateGenericRGB(red, green, blue, alpha);
}

void Color_dispose(Color _this)
{
    dl_CGColorRelease((dl_CGColorRef)_this);
}

AttributedString AttributedString_create(std::string s, AttributedStringOptions opts)
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

void AttributedString_dispose(AttributedString _this)
{
    dl_CFRelease(_this);
}

Font Font_createFromFile(std::string path, double size, AffineTransform matrix)
{
    auto pathStr = dl_CFStringCreateWithCString(path.c_str());
    auto url = dl_CFURLCreateWithFileSystemPath(pathStr, dl_CFURLPathStyle::dl_kCFURLPOSIXPathStyle, false);
    auto descriptors = dl_CTFontManagerCreateFontDescriptorsFromURL(url);
    Font result = nullptr;
    if (dl_CFArrayGetCount(descriptors) > 0) {
        auto first = (dl_CTFontDescriptorRef)dl_CFArrayGetValueAtIndex(descriptors, 0);
        result = (Font)dl_CTFontCreateWithFontDescriptor(first, size, (dl_CGAffineTransform*)&matrix);
    }
    dl_CFRelease(descriptors);
    dl_CFRelease(url);
    dl_CFRelease(pathStr);
    return result;
}

void Font_dispose(Font _this)
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

Line Line_createWithAttributedString(AttributedString str)
{
    return (Line)dl_CTLineCreateWithAttributedString((dl_CFAttributedStringRef)str);
}

void Line_dispose(Line _this)
{
    dl_CFRelease(_this);
}
