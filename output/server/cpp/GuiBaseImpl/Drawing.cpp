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

void DrawContext_setFillColorWithColor(DrawContext _this, Color color)
{
    dl_CGContextSetFillColorWithColor((dl_CGContextRef)_this, (dl_CGColorRef)color);
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
    dl_CFStringRef cfName = nullptr;
    switch (name) {
    case ColorSpaceName::GenericGray:
        cfName = dl_kCGColorSpaceGenericGray;
        break;
    case ColorSpaceName::GenericRGB:
        cfName = dl_kCGColorSpaceGenericRGB;
        break;
    case ColorSpaceName::GenericCMYK:
        cfName = dl_kCGColorSpaceGenericCMYK;
        break;
    case ColorSpaceName::GenericRGBLinear:
        cfName = dl_kCGColorSpaceGenericRGBLinear;
        break;
    case ColorSpaceName::AdobeRGB1998:
        cfName = dl_kCGColorSpaceAdobeRGB1998;
        break;
    case ColorSpaceName::SRGB:
        cfName = dl_kCGColorSpaceSRGB;
        break;
    case ColorSpaceName::GenericGrayGamma2_2:
        cfName = dl_kCGColorSpaceGenericGrayGamma2_2;
        break;
    default:
        printf("ColorSpace_createWithName: unknown ColorSpaceName (%d), returning null!\n", name);
        return nullptr;
    }
    return (ColorSpace)dl_CGColorSpaceCreateWithName(cfName);
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
    auto text = dl_CFStringCreateWithCString(s.c_str());
    auto dict = dl_CFDictionaryCreateMutable(0);

    Color foregroundColor;
    if (opts.hasForegroundColor(&foregroundColor)) {
        dl_CFDictionarySetValue(dict, dl_kCTForegroundColorAttributeName, (dl_CGColorRef)foregroundColor);
    }

    bool foregroundColorFromContext;
    if (opts.hasForegroundColorFromContext(&foregroundColorFromContext)) {
        auto cfBool = foregroundColorFromContext ? dl_kCFBooleanTrue : dl_kCFBooleanFalse;
        dl_CFDictionarySetValue(dict, dl_kCTForegroundColorFromContextAttributeName, cfBool);
    }

    Font f;
    if (opts.hasFont(&f)) {
        dl_CFDictionarySetValue(dict, dl_kCTFontAttributeName, (dl_CTFontRef)f); // cast not actually necessary, but makes clear we're using CTFont
    }

    double strokeWidth;
    if (opts.hasStrokeWidth(&strokeWidth)) {
        auto cfNumber = dl_CFNumberWithFloat((float)strokeWidth);
        dl_CFDictionarySetValue(dict, dl_kCTStrokeWidthAttributeName, cfNumber);
        dl_CFRelease(cfNumber);
    }
    
    Color strokeColor;
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

int64_t MutableAttributedString_getLength(MutableAttributedString _this)
{
    return (int64_t)dl_CFAttributedStringGetLength((dl_CFAttributedStringRef)_this);
}

void MutableAttributedString_replaceString(MutableAttributedString _this, Range range, std::string str)
{
    auto replacement = dl_CFStringCreateWithCString(str.c_str());
    dl_CFAttributedStringReplaceString((dl_CFMutableAttributedStringRef)_this, STRUCT_CAST(dl_CFRange, range), replacement); // note the struct cast only works in 64-bit mode!
    dl_CFRelease(replacement);
}

void MutableAttributedString_beginEditing(MutableAttributedString _this)
{
    dl_CFAttributedStringBeginEditing((dl_CFMutableAttributedStringRef)_this);
}

void MutableAttributedString_endEditing(MutableAttributedString _this)
{
    dl_CFAttributedStringEndEditing((dl_CFMutableAttributedStringRef)_this);
}

void MutableAttributedString_setAttribute(MutableAttributedString _this, Range range, AttributedStringOptions attr)
{
    Color foreground;
    if (attr.hasForegroundColor(&foreground)) {
        dl_CFAttributedStringSetAttribute((dl_CFMutableAttributedStringRef)_this, STRUCT_CAST(dl_CFRange, range), dl_kCTForegroundColorAttributeName, foreground);
    }

    bool foregroundFromContext;
    if (attr.hasForegroundColorFromContext(&foregroundFromContext)) {
        auto cfBool = foregroundFromContext ? dl_kCFBooleanTrue : dl_kCFBooleanFalse;
        dl_CFAttributedStringSetAttribute((dl_CFMutableAttributedStringRef)_this, STRUCT_CAST(dl_CFRange, range), dl_kCTForegroundColorFromContextAttributeName, cfBool);
    }

    Font font;
    if (attr.hasFont(&font)) {
        dl_CFAttributedStringSetAttribute((dl_CFMutableAttributedStringRef)_this, STRUCT_CAST(dl_CFRange, range), dl_kCTFontAttributeName, font);
    }

    double strokeWidth;
    if (attr.hasStrokeWidth(&strokeWidth)) {
        auto cfWidth = dl_CFNumberWithFloat((float)strokeWidth); // because double isn't working (nothing supports casting yet)
        dl_CFAttributedStringSetAttribute((dl_CFMutableAttributedStringRef)_this, STRUCT_CAST(dl_CFRange, range), dl_kCTStrokeWidthAttributeName, cfWidth);
        dl_CFRelease(cfWidth);
    }

    Color strokeColor;
    if (attr.hasStrokeColor(&strokeColor)) {
        dl_CFAttributedStringSetAttribute((dl_CFMutableAttributedStringRef)_this, STRUCT_CAST(dl_CFRange, range), dl_kCTStrokeColorAttributeName, strokeColor);
    }
}

void MutableAttributedString_setCustomAttribute(MutableAttributedString _this, Range range, std::string key, int64_t value)
{
    auto cfKey = dl_CFStringCreateWithCString(key.c_str());
    auto cfValue = dl_CFNumberCreate(dl_CFNumberType::dl_kCFNumberLongType, &value);

    dl_CFAttributedStringSetAttribute((dl_CFMutableAttributedStringRef)_this, STRUCT_CAST(dl_CFRange, range), cfKey, cfValue);

    dl_CFRelease(cfValue);
    dl_CFRelease(cfKey);
}

AttributedString MutableAttributedString_getNormalAttributedString_REMOVEME(MutableAttributedString _this)
{
    return (AttributedString)_this;
}

MutableAttributedString MutableAttributedString_create(int64_t maxLength)
{
    return (MutableAttributedString)dl_CFAttributedStringCreateMutable(maxLength);
}

void MutableAttributedString_dispose(MutableAttributedString _this)
{
    dl_CFRelease(_this);
}

double Font_getAscent(Font _this)
{
    return dl_CTFontGetAscent((dl_CTFontRef)_this);
}

double Font_getDescent(Font _this)
{
    return dl_CTFontGetDescent((dl_CTFontRef)_this);
}

double Font_getUnderlineThickness(Font _this)
{
    return dl_CTFontGetUnderlineThickness((dl_CTFontRef)_this);
}

double Font_getUnderlinePosition(Font _this)
{
    return dl_CTFontGetUnderlinePosition((dl_CTFontRef)_this);
}

Font Font_createCopyWithSymbolicTraits(Font _this, double size, FontTraits newTraits, OptArgs optArgs)
{
    dl_CTFontSymbolicTraits value = 0, mask = 0;
    bool b;
    if (newTraits.hasItalic(&b)) {
        value |= b ? dl_kCTFontTraitItalic : 0;
        mask |= dl_kCTFontTraitItalic;
    }
    if (newTraits.hasBold(&b)) {
        value |= b ? dl_kCTFontTraitBold : 0;
        mask |= dl_kCTFontTraitBold;
    }
    if (newTraits.hasExpanded(&b)) {
        value |= b ? dl_kCTFontTraitExpanded : 0;
        mask |= dl_kCTFontTraitExpanded;
    }
    if (newTraits.hasCondensed(&b)) {
        value |= b ? dl_kCTFontTraitCondensed : 0;
        mask |= dl_kCTFontTraitCondensed;
    }
    if (newTraits.hasMonospace(&b)) {
        value |= b ? dl_kCTFontTraitMonoSpace : 0;
        mask |= dl_kCTFontTraitMonoSpace;
    }
    if (newTraits.hasVertical(&b)) {
        value |= b ? dl_kCTFontTraitVertical : 0;
        mask |= dl_kCTFontTraitVertical;
    }

    AffineTransform matrix;
    AffineTransform* maybeMatrix = nullptr;
    if (optArgs.hasTransform(&matrix)) {
        maybeMatrix = &matrix;
    }

    return (Font)dl_CTFontCreateCopyWithSymbolicTraits((dl_CTFontRef)_this, size, (dl_CGAffineTransform*)maybeMatrix, value, mask);
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

AttributedStringOptions Run_getAttributes(Run _this, std::vector<std::string> customKeys)
{
    AttributedStringOptions ret;
    auto attrs = dl_CTRunGetAttributes((dl_CTRunRef)_this);

    auto foregroundColor = (Color)dl_CFDictionaryGetValue(attrs, dl_kCTForegroundColorAttributeName);
    if (foregroundColor != nullptr) {
        ret.setForegroundColor(foregroundColor);
    }

    auto foregroundFromContext = (dl_CFBooleanRef)dl_CFDictionaryGetValue(attrs, dl_kCTForegroundColorFromContextAttributeName);
    if (foregroundFromContext != nullptr) {
        ret.setForegroundColorFromContext(foregroundFromContext == dl_kCFBooleanTrue);
    }

    auto font = (Font)dl_CFDictionaryGetValue(attrs, dl_kCTFontAttributeName);
    if (font != nullptr) {
        ret.setFont(font);
    }

    auto strokeWidth = (dl_CFNumberRef)dl_CFDictionaryGetValue(attrs, dl_kCTStrokeWidthAttributeName);
    if (strokeWidth != nullptr) {
        float value;
        if (dl_CFNumberGetValue(strokeWidth, dl_kCFNumberFloatType, &value)) {
            ret.setStrokeWidth(value);
        }
        else {
            printf("Run_getAttributes: failed to get float value!\n");
        }
    }

    auto strokeColor = (Color)dl_CFDictionaryGetValue(attrs, dl_kCTStrokeColorAttributeName);
    if (strokeColor != nullptr) {
        ret.setStrokeColor(strokeColor);
    }

    // custom keys if requested
    if (customKeys.size() > 0) {
        std::map<std::string, int64_t> customMap;
        for (auto i = customKeys.begin(); i != customKeys.end(); i++) {
            auto cfKey = dl_CFStringCreateWithCString(i->c_str());
            auto cfNumber = (dl_CFNumberRef)dl_CFDictionaryGetValue(attrs, cfKey);
            if (cfNumber != nullptr) {
                long id;
                if (dl_CFNumberGetValue(cfNumber, dl_kCFNumberLongType, &id)) {
                    customMap[*i] = id;
                }
                else {
                    printf("Run_getAttributes: failed to get long value! (custom attr keys)\n");
                }
            }
            dl_CFRelease(cfKey);
        }
        ret.setCustom(customMap);
    }

    return ret;
}

TypographicBounds Run_getTypographicBounds(Run _this, Range range)
{
    TypographicBounds ret;
    ret.width = dl_CTRunGetTypographicBounds((dl_CTRunRef)_this, STRUCT_CAST(dl_CFRange, range), &ret.ascent, &ret.descent, &ret.leading);
    return ret;
}

Range Run_getStringRange(Run _this)
{
    auto ret = dl_CTRunGetStringRange((dl_CTRunRef)_this);
    return STRUCT_CAST(Range, ret);
}

uint32_t Run_getStatus(Run _this)
{
    return dl_CTRunGetStatus((dl_CTRunRef)_this);
}

void Run_dispose(Run _this)
{
    // but I don't think these are ever owned by the existing API ...
    // dl_CFRelease(_this);
    printf("called Run_dispose ... why?\n");
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

std::vector<Run> Line_getGlyphRuns(Line _this)
{
    std::vector<Run> ret;
    auto arr = dl_CTLineGetGlyphRuns((dl_CTLineRef)_this);
    auto count = dl_CFArrayGetCount(arr);
    for (auto i = 0; i < count; i++) {
        auto run = (Run)dl_CFArrayGetValueAtIndex(arr, i);
        ret.push_back(run);
    }
    return ret;
}

std::tuple<double, double> Line_getLineOffsetForStringIndex(Line _this, int64_t charIndex)
{
    double secondary;
    auto primary = dl_CTLineGetOffsetForStringIndex((dl_CTLineRef)_this, charIndex, &secondary);
    return std::tuple<double, double>(primary, secondary);
}

Line Line_createWithAttributedString(AttributedString str)
{
    return (Line)dl_CTLineCreateWithAttributedString((dl_CFAttributedStringRef)str);
}

void Line_dispose(Line _this)
{
    dl_CFRelease(_this);
}

void Frame_draw(Frame _this, DrawContext context)
{
    dl_CTFrameDraw((dl_CTFrameRef)_this, (dl_CGContextRef)context);
}

std::vector<Line> Frame_getLines(Frame _this)
{
    auto arr = dl_CTFrameGetLines((dl_CTFrameRef)_this);
    auto count = dl_CFArrayGetCount(arr);

    std::vector<Line> ret;
    for (auto i = 0; i < count; i++) {
        auto line = (dl_CTLineRef)dl_CFArrayGetValueAtIndex(arr, i);
        ret.push_back((Line)line);
    }
    return ret;
}

std::vector<Point> Frame_getLineOrigins(Frame _this, Range range)
{
    auto arr = dl_CTFrameGetLines((dl_CTFrameRef)_this);
    auto count = dl_CFArrayGetCount(arr);
    auto points = new Point[count];
    dl_CTFrameGetLineOrigins((dl_CTFrameRef)_this, STRUCT_CAST(dl_CFRange, range), (dl_CGPoint*)points);
    auto ret = std::vector<Point>(points, points + count);
    delete[] points;
    return ret;
}

void Frame_dispose(Frame _this)
{
    dl_CFRelease((dl_CTFrameRef)_this);
}

FrameSetter FrameSetter_createWithAttributedString(AttributedString str)
{
    return (FrameSetter)dl_CTFramesetterCreateWithAttributedString((dl_CFAttributedStringRef)str);
}

Frame FrameSetter_createFrame(FrameSetter _this, Range range, Path path)
{
    auto dict = dl_CFDictionaryCreate(nullptr, nullptr, 0);
    auto ret = (Frame)dl_CTFramesetterCreateFrame((dl_CTFramesetterRef)_this, STRUCT_CAST(dl_CFRange, range), (dl_CGPathRef)path, dict);
    dl_CFRelease(dict);
    return ret;
}

void FrameSetter_dispose(FrameSetter _this)
{
    dl_CFRelease(_this);
}
