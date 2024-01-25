#include "generated/Drawing.h"
#include "deps/opendl/source/opendl.h"

#define STRUCT_CAST(t, v) *((t*)&v)

const AffineTransform AffineTransformIdentity = *((AffineTransform*)&dl_CGAffineTransformIdentity);

Rect makeRect(double x, double y, double width, double height)
{
    auto r = dl_CGRectMake(x, y, width, height);
    return STRUCT_CAST(Rect, r);
}

Path Path_createWithRect(Rect rect, AffineTransform transform)
{
    return (Path)dl_CGPathCreateWithRect(STRUCT_CAST(dl_CGRect, rect), (dl_CGAffineTransform*)&transform);
}

Path Path_createWithEllipseInRect(Rect rect, AffineTransform transform)
{
    return (Path)dl_CGPathCreateWithEllipseInRect(STRUCT_CAST(dl_CGRect, rect), (dl_CGAffineTransform*)&transform);
}

Path Path_createWithRoundedRect(Rect rect, double cornerWidth, double cornerHeight, AffineTransform transform)
{
    return (Path)dl_CGPathCreateWithRoundedRect(STRUCT_CAST(dl_CGRect, rect), cornerWidth, cornerHeight, (dl_CGAffineTransform*)&transform);
}

void Path_dispose(Path _this)
{
    dl_CGPathRelease((dl_CGPathRef)_this);
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

void DrawContext_setRGBStrokeColor(DrawContext _this, double red, double green, double blue, double alpha)
{
    dl_CGContextSetRGBStrokeColor((dl_CGContextRef)_this, red, green, blue, alpha);
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

void DrawContext_beginPath(DrawContext _this)
{
    dl_CGContextBeginPath((dl_CGContextRef)_this);
}

void DrawContext_addArc(DrawContext _this, double x, double y, double radius, double startAngle, double endAngle, bool clockwise)
{
    dl_CGContextAddArc((dl_CGContextRef)_this, x, y, radius, startAngle, endAngle, clockwise ? 1 : 0);
}

void DrawContext_addArcToPoint(DrawContext _this, double x1, double y1, double x2, double y2, double radius)
{
    dl_CGContextAddArcToPoint((dl_CGContextRef)_this, x1, y1, x2, y2, radius);
}

void DrawContext_drawPath(DrawContext _this, PathDrawingMode mode)
{
    dl_CGContextDrawPath((dl_CGContextRef)_this, (dl_CGPathDrawingMode)mode);
}

void DrawContext_setStrokeColorWithColor(DrawContext _this, Color color)
{
    dl_CGContextSetStrokeColorWithColor((dl_CGContextRef)_this, (dl_CGColorRef)color);
}

void DrawContext_strokeRectWithWidth(DrawContext _this, Rect rect, double width)
{
    dl_CGContextStrokeRectWithWidth((dl_CGContextRef)_this, STRUCT_CAST(dl_CGRect, rect), width);
}

void DrawContext_moveToPoint(DrawContext _this, double x, double y)
{
    dl_CGContextMoveToPoint((dl_CGContextRef)_this, x, y);
}

void DrawContext_addLineToPoint(DrawContext _this, double x, double y)
{
    dl_CGContextAddLineToPoint((dl_CGContextRef)_this, x, y);
}

void DrawContext_strokePath(DrawContext _this)
{
    dl_CGContextStrokePath((dl_CGContextRef)_this);
}

void DrawContext_setLineDash(DrawContext _this, double phase, std::vector<double> lengths)
{
    dl_CGContextSetLineDash((dl_CGContextRef)_this, phase, lengths.data(), lengths.size());
}

void DrawContext_clearLineDash(DrawContext _this)
{
    dl_CGContextSetLineDash((dl_CGContextRef)_this, 0, nullptr, 0);
}

void DrawContext_setLineWidth(DrawContext _this, double width)
{
    dl_CGContextSetLineWidth((dl_CGContextRef)_this, width);
}

void DrawContext_clip(DrawContext _this)
{
    dl_CGContextClip((dl_CGContextRef)_this);
}

void DrawContext_translateCTM(DrawContext _this, double tx, double ty)
{
    dl_CGContextTranslateCTM((dl_CGContextRef)_this, tx, ty);
}

void DrawContext_scaleCTM(DrawContext _this, double scaleX, double scaleY)
{
    dl_CGContextScaleCTM((dl_CGContextRef)_this, scaleX, scaleY);
}

void DrawContext_rotateCTM(DrawContext _this, double angle)
{
    dl_CGContextRotateCTM((dl_CGContextRef)_this, angle);
}

void DrawContext_concatCTM(DrawContext _this, AffineTransform transform)
{
    dl_CGContextConcatCTM((dl_CGContextRef)_this, STRUCT_CAST(dl_CGAffineTransform, transform));
}

void DrawContext_addPath(DrawContext _this, Path path)
{
    dl_CGContextAddPath((dl_CGContextRef)_this, (dl_CGPathRef)path);
}

void DrawContext_fillPath(DrawContext _this)
{
    dl_CGContextFillPath((dl_CGContextRef)_this);
}

void DrawContext_strokeRect(DrawContext _this, Rect rect)
{
    dl_CGContextStrokeRect((dl_CGContextRef)_this, STRUCT_CAST(dl_CGRect, rect));
}

void DrawContext_addRect(DrawContext _this, Rect rect)
{
    dl_CGContextAddRect((dl_CGContextRef)_this, STRUCT_CAST(dl_CGRect, rect));
}

void DrawContext_closePath(DrawContext _this)
{
    dl_CGContextClosePath((dl_CGContextRef)_this);
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
