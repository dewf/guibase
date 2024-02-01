#include "generated/Drawing.h"
#include "deps/opendl/source/opendl.h"
#include "deps/opendl/deps/CFMinimal/source/CF/CFMisc.h" // for exceptions

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

int64_t AttributedString_getLength(AttributedString _this)
{
    return dl_CFAttributedStringGetLength((dl_CFAttributedStringRef)_this); // could be mutable for all we know!
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
    auto cfRange = STRUCT_CAST(dl_CFRange, range);

    Color foreground;
    if (attr.hasForegroundColor(&foreground)) {
        dl_CFAttributedStringSetAttribute((dl_CFMutableAttributedStringRef)_this, cfRange, dl_kCTForegroundColorAttributeName, foreground);
    }

    bool foregroundFromContext;
    if (attr.hasForegroundColorFromContext(&foregroundFromContext)) {
        auto cfBool = foregroundFromContext ? dl_kCFBooleanTrue : dl_kCFBooleanFalse;
        dl_CFAttributedStringSetAttribute((dl_CFMutableAttributedStringRef)_this, cfRange, dl_kCTForegroundColorFromContextAttributeName, cfBool);
    }

    Font font;
    if (attr.hasFont(&font)) {
        dl_CFAttributedStringSetAttribute((dl_CFMutableAttributedStringRef)_this, cfRange, dl_kCTFontAttributeName, font);
    }

    double strokeWidth;
    if (attr.hasStrokeWidth(&strokeWidth)) {
        auto cfWidth = dl_CFNumberWithFloat((float)strokeWidth); // because double isn't working (nothing supports casting yet)
        dl_CFAttributedStringSetAttribute((dl_CFMutableAttributedStringRef)_this, cfRange, dl_kCTStrokeWidthAttributeName, cfWidth);
        dl_CFRelease(cfWidth);
    }

    Color strokeColor;
    if (attr.hasStrokeColor(&strokeColor)) {
        dl_CFAttributedStringSetAttribute((dl_CFMutableAttributedStringRef)_this, cfRange, dl_kCTStrokeColorAttributeName, strokeColor);
    }

    ParagraphStyle paraStyle;
    if (attr.hasParagraphStyle(&paraStyle)) {
        dl_CFAttributedStringSetAttribute((dl_CFMutableAttributedStringRef)_this, cfRange, dl_kCTParagraphStyleAttributeName, paraStyle);
    }
}

void MutableAttributedString_setCustomAttribute(MutableAttributedString _this, Range range, std::string key, int64_t value)
{
    auto cfKey = __dl_CFStringMakeConstantString(key.c_str()); // needs to be a constant (deduplicated) for anything key-related
    auto cfValue = dl_CFNumberCreate(dl_CFNumberType::dl_kCFNumberLongType, &value);

    dl_CFAttributedStringSetAttribute((dl_CFMutableAttributedStringRef)_this, STRUCT_CAST(dl_CFRange, range), cfKey, cfValue);

    dl_CFRelease(cfValue);
    // dl_CFRelease(cfKey); // constant strings don't need to be released
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
            auto cfKey = __dl_CFStringMakeConstantString(i->c_str()); // needs to be constant (ie, deduplicated) for anything key-related
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
            // dl_CFRelease(cfKey); // constant strings shouldn't be released
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

std::tuple<double, double> Line_getOffsetForStringIndex(Line _this, int64_t charIndex)
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

std::vector<Point> Frame_getLineOrigins(Frame _this, Range range)
{
    auto ctLinesArr = dl_CTFrameGetLines((dl_CTFrameRef)_this);
    auto lineCount = dl_CFArrayGetCount(ctLinesArr);

    std::vector<Point> origins(lineCount);
    dl_CTFrameGetLineOrigins((dl_CTFrameRef)_this, STRUCT_CAST(dl_CFRange,range), (dl_CGPoint*)origins.data());
    return origins;
}

std::vector<LineInfo> Frame_getLinesExtended(Frame _this, std::vector<std::string> customKeys)
{
    std::vector<LineInfo> ret;
    auto ctLinesArr = dl_CTFrameGetLines((dl_CTFrameRef)_this);
    auto lineCount = dl_CFArrayGetCount(ctLinesArr);

    std::vector<Point> origins(lineCount);
    dl_CTFrameGetLineOrigins((dl_CTFrameRef)_this, dl_CFRangeZero, (dl_CGPoint*)origins.data());
    
    for (auto lineIndex = 0; lineIndex < lineCount; lineIndex++) {
        LineInfo line;
        line.origin = origins[lineIndex];

        auto ctLine = (dl_CTLineRef)dl_CFArrayGetValueAtIndex(ctLinesArr, lineIndex);
        line.lineTypoBounds = Line_getTypographicBounds((Line)ctLine);

        auto ctRunsArr = dl_CTLineGetGlyphRuns(ctLine);
        auto runCount = dl_CFArrayGetCount(ctRunsArr);
        for (auto runIndex = 0; runIndex < runCount; runIndex++) {
            RunInfo run;

            auto ctRun = (dl_CTRunRef)dl_CFArrayGetValueAtIndex(ctRunsArr, runIndex);
            run.attrs = Run_getAttributes((Run)ctRun, customKeys);

            run.typoBounds = Run_getTypographicBounds((Run)ctRun, STRUCT_CAST(Range,dl_CFRangeZero));
            run.bounds = STRUCT_CAST(Rect, dl_CGRectZero);

            // might want to pad these with user-definable pads?
            run.bounds.size.width = run.typoBounds.width;
            run.bounds.size.height = run.typoBounds.ascent + run.typoBounds.descent;

            auto xOffset = 0.0;
            auto runRange = dl_CTRunGetStringRange(ctRun);
            run.sourceRange = STRUCT_CAST(Range, runRange);
            run.status = (RunStatus)dl_CTRunGetStatus(ctRun);
            if (run.status & RunStatus::RightToLeft) {
                //    var(offs1, _) = line.GetLineOffsetForStringIndex(glyphRange.Location + glyphRange.Length);
                //    xOffset = offs1;
                xOffset = dl_CTLineGetOffsetForStringIndex(ctLine, run.sourceRange.location + run.sourceRange.length, nullptr);
            }
            else {
                //    var(offs1, _) = line.GetLineOffsetForStringIndex(glyphRange.Location);
                //    xOffset = offs1;
                xOffset = dl_CTLineGetOffsetForStringIndex(ctLine, run.sourceRange.location, nullptr);
            }

            run.bounds.origin.x = line.origin.x + xOffset;
            run.bounds.origin.y = line.origin.y;
            run.bounds.origin.y -= run.typoBounds.ascent;

            if (run.bounds.size.width > line.lineTypoBounds.width) {
                run.bounds.size.width = line.lineTypoBounds.width;
            }

            line.runs.push_back(run);
        }
        ret.push_back(line);
    }

    return ret;
}

ParagraphStyle ParagraphStyle_create(std::vector<ParagraphStyleSetting> settings)
{
    std::vector<dl_CTParagraphStyleSetting> ctSettings;

    for (auto i = settings.begin(); i != settings.end(); i++) {
        dl_CTParagraphStyleSetting pss;

        switch (i->tag) {
        case ParagraphStyleSetting::Tag::alignment: {
            pss.spec = dl_kCTParagraphStyleSpecifierAlignment;
            auto value = i->alignment->value;
            pss.value = &value;
            pss.valueSize = sizeof(value);
            break;
        }
        default:
            printf("ParagraphStyle_create(): unrecognized setting tag: %d\n", i->tag);
            continue;
        }

        ctSettings.push_back(pss);
    }

    return (ParagraphStyle)dl_CTParagraphStyleCreate(ctSettings.data(), ctSettings.size());
}

void ParagraphStyle_dispose(ParagraphStyle _this)
{
    dl_CFRelease(_this);
}

void DrawContext_setTextDrawingMode(DrawContext _this, TextDrawingMode mode)
{
    dl_CGContextSetTextDrawingMode((dl_CGContextRef)_this, (dl_CGTextDrawingMode)mode);
}

void DrawContext_clipToMask(DrawContext _this, Rect rect, Image mask)
{
    dl_CGContextClipToMask((dl_CGContextRef)_this, STRUCT_CAST(dl_CGRect, rect), (dl_CGImageRef)mask);
}

void DrawContext_drawImage(DrawContext _this, Rect rect, Image image)
{
    dl_CGContextDrawImage((dl_CGContextRef)_this, STRUCT_CAST(dl_CGRect, rect), (dl_CGImageRef)image);
}

MutableAttributedString AttributedString_createMutableCopy(AttributedString _this, int64_t maxLength)
{
    return (MutableAttributedString)dl_CFAttributedStringCreateMutableCopy(maxLength, (dl_CFAttributedStringRef)_this);
}

struct __BitmapLock {
    BitmapDrawContext source;
    void* data;
};

BitmapLock BitmapDrawContext_getData(BitmapDrawContext _this)
{
    auto ret = new __BitmapLock;
    ret->source = _this;
    ret->data = dl_CGBitmapContextGetData((dl_CGContextRef)_this);
    return ret;
}

Range Line_getStringRange(Line _this)
{
    auto ret = dl_CTLineGetStringRange((dl_CTLineRef)_this);
    return STRUCT_CAST(Range, ret);
}

int64_t Line_getStringIndexForPosition(Line _this, Point p)
{
    return dl_CTLineGetStringIndexForPosition((dl_CTLineRef)_this, STRUCT_CAST(dl_CGPoint, p));
}

void BitmapLock_dispose(BitmapLock _this)
{
    dl_CGBitmapContextReleaseData((dl_CGContextRef)_this->source);
    delete _this;
}

BitmapDrawContext BitmapDrawContext_create(int32_t width, int32_t height, int32_t bitsPerComponent, int32_t bytesPerRow, ColorSpace space, uint32_t bitmapInfo)
{
    return (BitmapDrawContext)dl_CGBitmapContextCreate(nullptr, width, height, bitsPerComponent, bytesPerRow, (dl_CGColorSpaceRef)space, bitmapInfo);
}

Image BitmapDrawContext_createImage(BitmapDrawContext _this)
{
    return (Image)dl_CGBitmapContextCreateImage((dl_CGContextRef)_this);
}

void BitmapDrawContext_dispose(BitmapDrawContext _this)
{
    dl_CGContextRelease((dl_CGContextRef)_this);
}

void Image_dispose(Image _this)
{
    dl_CGImageRelease((dl_CGImageRef)_this);
}

AffineTransform AffineTransformTranslate(AffineTransform input, double tx, double ty)
{
    auto ret = dl_CGAffineTransformTranslate(STRUCT_CAST(dl_CGAffineTransform, input), tx, ty);
    return STRUCT_CAST(AffineTransform, ret);
}

AffineTransform AffineTransformRotate(AffineTransform input, double angle)
{
    auto ret = dl_CGAffineTransformRotate(STRUCT_CAST(dl_CGAffineTransform, input), angle);
    return STRUCT_CAST(AffineTransform, ret);
}

AffineTransform AffineTransformScale(AffineTransform input, double sx, double sy)
{
    auto ret = dl_CGAffineTransformScale(STRUCT_CAST(dl_CGAffineTransform, input), sx, sy);
    return STRUCT_CAST(AffineTransform, ret);
}

AffineTransform AffineTransformConcat(AffineTransform t1, AffineTransform t2)
{
    auto ret = dl_CGAffineTransformConcat(STRUCT_CAST(dl_CGAffineTransform, t1), STRUCT_CAST(dl_CGAffineTransform, t2));
    return STRUCT_CAST(AffineTransform, ret);
}

Point Path_getCurrentPoint(Path _this)
{
    auto ret = dl_CGPathGetCurrentPoint((dl_CGPathRef)_this);
    return STRUCT_CAST(Point, ret);
}

Path Path_createCopy(Path _this)
{
    return (Path)dl_CGPathCreateCopy((dl_CGPathRef)_this);
}

MutablePath Path_createMutableCopy(Path _this)
{
    return (MutablePath)dl_CGPathCreateMutableCopy((dl_CGPathRef)_this);
}

void MutablePath_moveToPoint(MutablePath _this, double x, double y, OptArgs optArgs)
{
    AffineTransform transform;
    dl_CGAffineTransform *m = nullptr;
    if (optArgs.hasTransform(&transform)) {
        m = (dl_CGAffineTransform*)&transform;
    }
    try {
        dl_CGPathMoveToPoint((dl_CGMutablePathRef)_this, m, x, y);
    }
    catch (cf::Exception e) {
        throw MutablePathTransformException(e.reason());
    }
}

void MutablePath_addArc(MutablePath _this, double x, double y, double radius, double startAngle, double endAngle, bool clockwise, OptArgs optArgs)
{
    AffineTransform transform;
    dl_CGAffineTransform* m = nullptr;
    if (optArgs.hasTransform(&transform)) {
        m = (dl_CGAffineTransform*)&transform;
    }
    try {
        dl_CGPathAddArc((dl_CGMutablePathRef)_this, m, x, y, radius, startAngle, endAngle, clockwise);
    }
    catch (cf::Exception e) {
        throw MutablePathTransformException(e.reason());
    }
}

void MutablePath_addRelativeArc(MutablePath _this, double x, double y, double radius, double startAngle, double delta, OptArgs optArgs)
{
    AffineTransform transform;
    dl_CGAffineTransform* m = nullptr;
    if (optArgs.hasTransform(&transform)) {
        m = (dl_CGAffineTransform*)&transform;
    }
    try {
        dl_CGPathAddRelativeArc((dl_CGMutablePathRef)_this, m, x, y, radius, startAngle, delta);
    }
    catch (cf::Exception e) {
        throw MutablePathTransformException(e.reason());
    }
}

void MutablePath_addArcToPoint(MutablePath _this, double x1, double y1, double x2, double y2, double radius, OptArgs optArgs)
{
    AffineTransform transform;
    dl_CGAffineTransform* m = nullptr;
    if (optArgs.hasTransform(&transform)) {
        m = (dl_CGAffineTransform*)&transform;
    }
    try {
        dl_CGPathAddArcToPoint((dl_CGMutablePathRef)_this, m, x1, y1, x2, y2, radius);
    }
    catch (cf::Exception e) {
        throw MutablePathTransformException(e.reason());
    }
}

void MutablePath_addCurveToPoint(MutablePath _this, double cp1x, double cp1y, double cp2x, double cp2y, double x, double y, OptArgs optArgs)
{
    AffineTransform transform;
    dl_CGAffineTransform* m = nullptr;
    if (optArgs.hasTransform(&transform)) {
        m = (dl_CGAffineTransform*)&transform;
    }
    try {
        dl_CGPathAddCurveToPoint((dl_CGMutablePathRef)_this, m, cp1x, cp1y, cp2x, cp2y, x, y);
    }
    catch (cf::Exception e) {
        throw MutablePathTransformException(e.reason());
    }
}

void MutablePath_addLines(MutablePath _this, std::vector<Point> points, OptArgs optArgs)
{
    AffineTransform transform;
    dl_CGAffineTransform* m = nullptr;
    if (optArgs.hasTransform(&transform)) {
        m = (dl_CGAffineTransform*)&transform;
    }
    try {
        dl_CGPathAddLines((dl_CGMutablePathRef)_this, m, (dl_CGPoint*)points.data(), points.size());
    }
    catch (cf::Exception e) {
        throw MutablePathTransformException(e.reason());
    }
}

void MutablePath_addLineToPoint(MutablePath _this, double x, double y, OptArgs optArgs)
{
    AffineTransform transform;
    dl_CGAffineTransform* m = nullptr;
    if (optArgs.hasTransform(&transform)) {
        m = (dl_CGAffineTransform*)&transform;
    }
    try {
        dl_CGPathAddLineToPoint((dl_CGMutablePathRef)_this, m, x, y);
    }
    catch (cf::Exception e) {
        throw MutablePathTransformException(e.reason());
    }
}

void MutablePath_addPath(MutablePath _this, Path path2, OptArgs optArgs)
{
    AffineTransform transform;
    dl_CGAffineTransform* m = nullptr;
    if (optArgs.hasTransform(&transform)) {
        m = (dl_CGAffineTransform*)&transform;
    }
    dl_CGPathAddPath((dl_CGMutablePathRef)_this, m, (dl_CGPathRef)path2);
}

void MutablePath_addQuadCurveToPoint(MutablePath _this, double cpx, double cpy, double x, double y, OptArgs optArgs)
{
    AffineTransform transform;
    dl_CGAffineTransform* m = nullptr;
    if (optArgs.hasTransform(&transform)) {
        m = (dl_CGAffineTransform*)&transform;
    }
    try {
        dl_CGPathAddQuadCurveToPoint((dl_CGMutablePathRef)_this, m, cpx, cpy, x, y);
    }
    catch (cf::Exception e) {
        throw MutablePathTransformException(e.reason());
    }
}

void MutablePath_addRect(MutablePath _this, Rect rect, OptArgs optArgs)
{
    AffineTransform transform;
    dl_CGAffineTransform* m = nullptr;
    if (optArgs.hasTransform(&transform)) {
        m = (dl_CGAffineTransform*)&transform;
    }
    dl_CGPathAddRect((dl_CGMutablePathRef)_this, m, STRUCT_CAST(dl_CGRect, rect));
}

void MutablePath_addRects(MutablePath _this, std::vector<Rect> rects, OptArgs optArgs)
{
    AffineTransform transform;
    dl_CGAffineTransform* m = nullptr;
    if (optArgs.hasTransform(&transform)) {
        m = (dl_CGAffineTransform*)&transform;
    }
    dl_CGPathAddRects((dl_CGMutablePathRef)_this, m, (dl_CGRect*)rects.data(), rects.size());
}

void MutablePath_addRoundedRect(MutablePath _this, Rect rect, double cornerWidth, double cornerHeight, OptArgs optArgs)
{
    AffineTransform transform;
    dl_CGAffineTransform* m = nullptr;
    if (optArgs.hasTransform(&transform)) {
        m = (dl_CGAffineTransform*)&transform;
    }
    dl_CGPathAddRoundedRect((dl_CGMutablePathRef)_this, m, STRUCT_CAST(dl_CGRect, rect), cornerWidth, cornerHeight);
}

void MutablePath_addEllipseInRect(MutablePath _this, Rect rect, OptArgs optArgs)
{
    AffineTransform transform;
    dl_CGAffineTransform* m = nullptr;
    if (optArgs.hasTransform(&transform)) {
        m = (dl_CGAffineTransform*)&transform;
    }
    dl_CGPathAddEllipseInRect((dl_CGMutablePathRef)_this, m, STRUCT_CAST(dl_CGRect, rect));
}

void MutablePath_closeSubpath(MutablePath _this)
{
    dl_CGPathCloseSubpath((dl_CGMutablePathRef)_this);
}

MutablePath MutablePath_create()
{
    return (MutablePath)dl_CGPathCreateMutable();
}

void MutablePath_dispose(MutablePath _this)
{
    dl_CGPathRelease((dl_CGPathRef)_this);
}

//static inline void drawCommand(dl_CGContextRef context, DrawCommand command)
//{
//    switch (command.tag) {
//    case DrawCommand::Tag::restoreGState: {
//        dl_CGContextRestoreGState(context);
//        break;
//    }
//    case DrawCommand::Tag::saveGState: {
//        dl_CGContextSaveGState(context);
//        break;
//    }
//    case DrawCommand::Tag::setRGBFillColor: {
//        auto& cmd = command.setRGBFillColor;
//        dl_CGContextSetRGBFillColor(context, cmd->red, cmd->green, cmd->blue, cmd->alpha);
//        break;
//    }
//    case DrawCommand::Tag::setRGBStrokeColor: {
//        auto& cmd = command.setRGBStrokeColor;
//        dl_CGContextSetRGBStrokeColor(context, cmd->red, cmd->green, cmd->blue, cmd->alpha);
//        break;
//    }
//    case DrawCommand::Tag::setFillColorWithColor: {
//        auto& cmd = command.setFillColorWithColor;
//        dl_CGContextSetFillColorWithColor(context, (dl_CGColorRef)cmd->color);
//        break;
//    }
//    case DrawCommand::Tag::fillRect: {
//        auto& cmd = command.fillRect;
//        dl_CGContextFillRect(context, STRUCT_CAST(dl_CGRect, cmd->rect));
//        break;
//    }
//    case DrawCommand::Tag::setTextMatrix: {
//        auto& cmd = command.setTextMatrix;
//        dl_CGContextSetTextMatrix(context, STRUCT_CAST(dl_CGAffineTransform, cmd->t));
//        break;
//    }
//    case DrawCommand::Tag::setTextPosition: {
//        auto& cmd = command.setTextPosition;
//        dl_CGContextSetTextPosition(context, cmd->x, cmd->y);
//        break;
//    }
//    case DrawCommand::Tag::beginPath: {
//        dl_CGContextBeginPath(context);
//        break;
//    }
//    case DrawCommand::Tag::addArc: {
//        auto& cmd = command.addArc;
//        dl_CGContextAddArc(context, cmd->x, cmd->y, cmd->radius, cmd->startAngle, cmd->endAngle, cmd->clockwise);
//        break;
//    }
//    case DrawCommand::Tag::addArcToPoint: {
//        auto& cmd = command.addArcToPoint;
//        dl_CGContextAddArcToPoint(context, cmd->x1, cmd->y1, cmd->x2, cmd->y2, cmd->radius);
//        break;
//    }
//    case DrawCommand::Tag::drawPath: {
//        auto& cmd = command.drawPath;
//        dl_CGContextDrawPath(context, (dl_CGPathDrawingMode)cmd->mode);
//        break;
//    }
//    case DrawCommand::Tag::setStrokeColorWithColor: {
//        auto& cmd = command.setStrokeColorWithColor;
//        dl_CGContextSetStrokeColorWithColor(context, (dl_CGColorRef)cmd->color);
//        break;
//    }
//    case DrawCommand::Tag::strokeRectWithWidth: {
//        auto& cmd = command.strokeRectWithWidth;
//        dl_CGContextStrokeRectWithWidth(context, STRUCT_CAST(dl_CGRect, cmd->rect), cmd->width);
//        break;
//    }
//    case DrawCommand::Tag::moveToPoint: {
//        auto& cmd = command.moveToPoint;
//        dl_CGContextMoveToPoint(context, cmd->x, cmd->y);
//        break;
//    }
//    case DrawCommand::Tag::addLineToPoint: {
//        auto& cmd = command.addLineToPoint;
//        dl_CGContextAddLineToPoint(context, cmd->x, cmd->y);
//        break;
//    }
//    case DrawCommand::Tag::strokePath: {
//        dl_CGContextStrokePath(context);
//        break;
//    }
//    case DrawCommand::Tag::setLineDash: {
//        auto& cmd = command.setLineDash;
//        dl_CGContextSetLineDash(context, cmd->phase, cmd->lengths.data(), cmd->lengths.size());
//        break;
//    }
//    case DrawCommand::Tag::clearLineDash: {
//        dl_CGContextSetLineDash(context, 0, nullptr, 0);
//        break;
//    }
//    case DrawCommand::Tag::setLineWidth: {
//        auto& cmd = command.setLineWidth;
//        dl_CGContextSetLineWidth(context, cmd->width);
//        break;
//    }
//    case DrawCommand::Tag::clip: {
//        dl_CGContextClip(context);
//        break;
//    }
//    case DrawCommand::Tag::clipToRect: {
//        auto& cmd = command.clipToRect;
//        dl_CGContextClipToRect(context, STRUCT_CAST(dl_CGRect, cmd->clipRect));
//        break;
//    }
//    case DrawCommand::Tag::translateCTM: {
//        auto& cmd = command.translateCTM;
//        dl_CGContextTranslateCTM(context, cmd->tx, cmd->ty);
//        break;
//    }
//    case DrawCommand::Tag::scaleCTM: {
//        auto& cmd = command.scaleCTM;
//        dl_CGContextScaleCTM(context, cmd->scaleX, cmd->scaleY);
//        break;
//    }
//    case DrawCommand::Tag::rotateCTM: {
//        auto& cmd = command.rotateCTM;
//        dl_CGContextRotateCTM(context, cmd->angle);
//        break;
//    }
//    case DrawCommand::Tag::concatCTM: {
//        auto& cmd = command.concatCTM;
//        dl_CGContextConcatCTM(context, STRUCT_CAST(dl_CGAffineTransform, cmd->transform));
//        break;
//    }
//    case DrawCommand::Tag::addPath: {
//        auto& cmd = command.addPath;
//        dl_CGContextAddPath(context, (dl_CGPathRef)cmd->path);
//        break;
//    }
//    case DrawCommand::Tag::fillPath: {
//        dl_CGContextFillPath(context);
//        break;
//    }
//    case DrawCommand::Tag::strokeRect: {
//        auto& cmd = command.strokeRect;
//        dl_CGContextStrokeRect(context, STRUCT_CAST(dl_CGRect, cmd->rect));
//        break;
//    }
//    case DrawCommand::Tag::addRect: {
//        auto& cmd = command.addRect;
//        dl_CGContextAddRect(context, STRUCT_CAST(dl_CGRect, cmd->rect));
//        break;
//    }
//    case DrawCommand::Tag::closePath: {
//        dl_CGContextClosePath(context);
//        break;
//    }
//    case DrawCommand::Tag::drawLinearGradient: {
//        auto& cmd = command.drawLinearGradient;
//        dl_CGContextDrawLinearGradient(
//            context,
//            (dl_CGGradientRef)cmd->gradient,
//            STRUCT_CAST(dl_CGPoint, cmd->startPoint),
//            STRUCT_CAST(dl_CGPoint, cmd->endPoint),
//            (dl_CGGradientDrawingOptions)cmd->drawOpts);
//        break;
//    }
//    case DrawCommand::Tag::drawFrame: {
//        auto& cmd = command.drawFrame;
//        dl_CTFrameDraw((dl_CTFrameRef)cmd->frame, context);
//        break;
//    }
//    default:
//        printf("Drawing.cpp: unhandled drawCommand! %d\n", command.tag);
//    }
//}
//
//void DrawContext_batchDraw(DrawContext _this, std::vector<DrawCommand> commands)
//{
//    for (auto i = commands.begin(); i != commands.end(); i++) {
//        drawCommand((dl_CGContextRef)_this, *i);
//    }
//}

