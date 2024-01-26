#include "generated/Drawing.h"
#include "deps/opendl/source/opendl.h"

#define STRUCT_CAST(t, v) *((t*)&v)

const AffineTransform AffineTransformIdentity = *((AffineTransform*)&dl_CGAffineTransformIdentity);

Path Path_createWithRect(Rect rect, OptArgs optArgs)
{
    AffineTransform transform;
    if (optArgs.hasTransform(&transform)) {
        return (Path)dl_CGPathCreateWithRect(STRUCT_CAST(dl_CGRect, rect), (dl_CGAffineTransform*)&transform);
    }
    else {
        return (Path)dl_CGPathCreateWithRect(STRUCT_CAST(dl_CGRect, rect), nullptr);
    }
}

Path Path_createWithEllipseInRect(Rect rect, OptArgs optArgs)
{
    AffineTransform transform;
    if (optArgs.hasTransform(&transform)) {
        return (Path)dl_CGPathCreateWithEllipseInRect(STRUCT_CAST(dl_CGRect, rect), (dl_CGAffineTransform*)&transform);
    }
    else {
        return (Path)dl_CGPathCreateWithEllipseInRect(STRUCT_CAST(dl_CGRect, rect), nullptr);
    }
}

Path Path_createWithRoundedRect(Rect rect, double cornerWidth, double cornerHeight, OptArgs optArgs)
{
    AffineTransform transform;
    if (optArgs.hasTransform(&transform)) {
        return (Path)dl_CGPathCreateWithRoundedRect(STRUCT_CAST(dl_CGRect, rect), cornerWidth, cornerHeight, (dl_CGAffineTransform*)&transform);
    }
    else {
        return (Path)dl_CGPathCreateWithRoundedRect(STRUCT_CAST(dl_CGRect, rect), cornerWidth, cornerHeight, nullptr);
    }
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

void DrawContext_clipToRect(DrawContext _this, Rect clipRect)
{
    dl_CGContextClipToRect((dl_CGContextRef)_this, STRUCT_CAST(dl_CGRect, clipRect));
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

void DrawContext_drawLinearGradient(DrawContext _this, Gradient gradient, Point startPoint, Point endPoint, uint32_t drawOpts)
{
    dl_CGContextDrawLinearGradient(
        (dl_CGContextRef)_this,
        (dl_CGGradientRef)gradient,
        STRUCT_CAST(dl_CGPoint, startPoint),
        STRUCT_CAST(dl_CGPoint, endPoint),
        drawOpts);
}

Color Color_createGenericRGB(double red, double green, double blue, double alpha)
{
    return (Color)dl_CGColorCreateGenericRGB(red, green, blue, alpha);
}

Color Color_getConstantColor(ColorConstants which)
{
    dl_CFStringRef key;
    switch (which) {
    case ColorConstants::Black:
        key = dl_kCGColorBlack;
        break;
    case ColorConstants::White:
        key = dl_kCGColorWhite;
        break;
    case ColorConstants::Clear:
        key = dl_kCGColorClear;
        break;
    default:
        printf("Color_getConstantColor: unrecognized color %d, returning null\n", which);
        return nullptr;
    }
    return (Color)dl_CGColorGetConstantColor(key);
}

void Color_dispose(Color _this)
{
    dl_CGColorRelease((dl_CGColorRef)_this);
}

ColorSpace ColorSpace_createWithName(ColorSpaceName name)
{
    dl_CFStringRef cfStringName = nullptr;
    bool needsRelease = false;
    switch (name.tag) {
    case ColorSpaceName::Tag::GenericGray:
        cfStringName = dl_kCGColorSpaceGenericGray;
        break;
    case ColorSpaceName::Tag::GenericRGB:
        cfStringName = dl_kCGColorSpaceGenericRGB;
        break;
    case ColorSpaceName::Tag::GenericCMYK:
        cfStringName = dl_kCGColorSpaceGenericCMYK;
        break;
    case ColorSpaceName::Tag::GenericRGBLinear:
        cfStringName = dl_kCGColorSpaceGenericRGBLinear;
        break;
    case ColorSpaceName::Tag::AdobeRGB1998:
        cfStringName = dl_kCGColorSpaceAdobeRGB1998;
        break;
    case ColorSpaceName::Tag::SRGB:
        cfStringName = dl_kCGColorSpaceSRGB;
        break;
    case ColorSpaceName::Tag::GenericGrayGamma2_2:
        cfStringName = dl_kCGColorSpaceGenericGrayGamma2_2;
        break;
    case ColorSpaceName::Tag::Other:
        cfStringName = dl_CFStringCreateWithCString(name.other->name.c_str());
        needsRelease = true;
        break;
    default:
        printf("ColorSpace_createWithName: unknown ColorSpaceName, returning null!\n");
        return nullptr;
    }
    auto space = dl_CGColorSpaceCreateWithName(cfStringName);
    if (needsRelease) {
        dl_CFRelease(cfStringName);
    }
    return (ColorSpace)space;
}

ColorSpace ColorSpace_createDeviceGray()
{
    return (ColorSpace)dl_CGColorSpaceCreateDeviceGray();
}

void ColorSpace_dispose(ColorSpace _this)
{
    dl_CGColorSpaceRelease((dl_CGColorSpaceRef)_this);
}

Gradient Gradient_createWithColorComponents(ColorSpace space, std::vector<GradientStop> stops)
{
    auto count = stops.size();

    auto components = new double[count * 4];
    auto locations = new double[count];

    for (int i = 0; i < count; i++) {
        locations[i] = stops[i].location;
        components[i * 4] = stops[i].red;
        components[i * 4 + 1] = stops[i].green;
        components[i * 4 + 2] = stops[i].blue;
        components[i * 4 + 3] = stops[i].alpha;
    }
    auto gradient = dl_CGGradientCreateWithColorComponents((dl_CGColorSpaceRef)space, components, locations, count);

    delete[] locations;
    delete[] components;

    return (Gradient)gradient;
}

void Gradient_dispose(Gradient _this)
{
    dl_CGGradientRelease((dl_CGGradientRef)_this);
}

AttributedString AttributedString_create(std::string s, AttributedStringOptions opts)
{
    Font f;
    Color foregroundColor;
    bool foregroundColorFromContext;
    double strokeWidth;
    Color strokeColor;

    auto text = dl_CFStringCreateWithCString(s.c_str());
    auto dict = dl_CFDictionaryCreateMutable(0);

    if (opts.hasForegroundColor(&foregroundColor)) {
        dl_CFDictionarySetValue(dict, dl_kCTForegroundColorAttributeName, (dl_CGColorRef)foregroundColor);
    }
    if (opts.hasForegroundColorFromContext(&foregroundColorFromContext)) {
        auto cfBool = foregroundColorFromContext ? dl_kCFBooleanTrue : dl_kCFBooleanFalse;
        dl_CFDictionarySetValue(dict, dl_kCTForegroundColorFromContextAttributeName, cfBool);
    }
    if (opts.hasFont(&f)) {
        dl_CFDictionarySetValue(dict, dl_kCTFontAttributeName, (dl_CTFontRef)f); // cast not actually necessary, but makes clear we're using CTFont
    }
    if (opts.hasStrokeWidth(&strokeWidth)) {
        auto cfNumber = dl_CFNumberWithFloat((float)strokeWidth);
        dl_CFDictionarySetValue(dict, dl_kCTStrokeWidthAttributeName, cfNumber);
        dl_CFRelease(cfNumber);
    }
    if (opts.hasStrokeColor(&strokeColor)) {
        dl_CFDictionarySetValue(dict, dl_kCTStrokeColorAttributeName, (dl_CGColorRef)strokeColor);
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

Font Font_createFromFile(std::string path, double size, OptArgs optArgs)
{
    auto pathStr = dl_CFStringCreateWithCString(path.c_str());
    auto url = dl_CFURLCreateWithFileSystemPath(pathStr, dl_CFURLPathStyle::dl_kCFURLPOSIXPathStyle, false);
    auto descriptors = dl_CTFontManagerCreateFontDescriptorsFromURL(url);

    Font result = nullptr;
    if (dl_CFArrayGetCount(descriptors) > 0) {
        AffineTransform matrix;

        auto first = (dl_CTFontDescriptorRef)dl_CFArrayGetValueAtIndex(descriptors, 0);
        if (optArgs.hasTransform(&matrix)) {
            result = (Font)dl_CTFontCreateWithFontDescriptor(first, size, (dl_CGAffineTransform*)&matrix);
        }
        else {
            result = (Font)dl_CTFontCreateWithFontDescriptor(first, size, nullptr);
        }
    }
    dl_CFRelease(descriptors);
    dl_CFRelease(url);
    dl_CFRelease(pathStr);
    return result;
}

Font Font_createWithName(std::string name, double size, OptArgs optArgs)
{
    dl_CTFontRef ret;

    auto nameStr = dl_CFStringCreateWithCString(name.c_str());

    AffineTransform matrix;
    if (optArgs.hasTransform(&matrix)) {
        ret = dl_CTFontCreateWithName(nameStr, size, (dl_CGAffineTransform*)&matrix);
    }
    else {
        ret = dl_CTFontCreateWithName(nameStr, size, nullptr);
    }
    dl_CFRelease(nameStr);

    return (Font)ret;
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
