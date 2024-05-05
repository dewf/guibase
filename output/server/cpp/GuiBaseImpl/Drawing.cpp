#include "generated/Drawing.h"

#include "deps/opendl/source/opendl.h"
#include "deps/opendl/deps/CFMinimal/source/CF/CFMisc.h" // for exceptions

#include "util.h"

namespace Drawing
{
    const AffineTransform AffineTransform::identity = STRUCT_CAST(AffineTransform, dl_CGAffineTransformIdentity);

    AffineTransform AffineTransform::translate(AffineTransform input, double tx, double ty) {
        auto ret = dl_CGAffineTransformTranslate(STRUCT_CAST(dl_CGAffineTransform, input), tx, ty);
        return STRUCT_CAST(AffineTransform, ret);
    }

    AffineTransform AffineTransform::rotate(AffineTransform input, double angle) {
        auto ret = dl_CGAffineTransformRotate(STRUCT_CAST(dl_CGAffineTransform, input), angle);
        return STRUCT_CAST(AffineTransform, ret);
    }

    AffineTransform AffineTransform::scale(AffineTransform input, double sx, double sy) {
        auto ret = dl_CGAffineTransformScale(STRUCT_CAST(dl_CGAffineTransform, input), sx, sy);
        return STRUCT_CAST(AffineTransform, ret);
    }

    AffineTransform AffineTransform::concat(AffineTransform t1, AffineTransform t2) {
        auto ret = dl_CGAffineTransformConcat(STRUCT_CAST(dl_CGAffineTransform, t1), STRUCT_CAST(dl_CGAffineTransform, t2));
        return STRUCT_CAST(AffineTransform, ret);
    }

    namespace AffineBatchOps {
        namespace Value {
            class ProcessVisitor : public Visitor {
                dl_CGAffineTransform& result;
            public:
                ProcessVisitor(dl_CGAffineTransform& result) : result(result) {}
                void onTranslate(const Translate* translate) {
                    result = dl_CGAffineTransformTranslate(STRUCT_CAST(dl_CGAffineTransform, result), translate->tx, translate->ty);
                }
                void onRotate(const Rotate* rotate) {
                    result = dl_CGAffineTransformRotate(STRUCT_CAST(dl_CGAffineTransform, result), rotate->angle);
                }
                void onScale(const Scale* scale) {
                    result = dl_CGAffineTransformScale(STRUCT_CAST(dl_CGAffineTransform, result), scale->sx, scale->sy);
                }
                void onConcat(const Concat* concat) {
                    result = dl_CGAffineTransformConcat(STRUCT_CAST(dl_CGAffineTransform, result), STRUCT_CAST(dl_CGAffineTransform, concat->t2));
                }
            };
        }
        AffineTransform process(AffineTransform input, std::vector<std::shared_ptr<Value::Base>> ops) {
            dl_CGAffineTransform result = STRUCT_CAST(dl_CGAffineTransform, input);
            Value::ProcessVisitor v(result);
            for (auto i = ops.begin(); i != ops.end(); i++) {
                (*i)->accept(&v);
            }
            return STRUCT_CAST(AffineTransform, result);
        }
    }

    namespace Color {
        ColorRef createGenericRGB(double red, double green, double blue, double alpha) {
            return (ColorRef)dl_CGColorCreateGenericRGB(red, green, blue, alpha);
        }

        ColorRef getConstantColor(Constant which) {
            dl_CFStringRef key;
            switch (which) {
            case Color::Constant::Black:
                key = dl_kCGColorBlack;
                break;
            case Color::Constant::White:
                key = dl_kCGColorWhite;
                break;
            case Color::Constant::Clear:
                key = dl_kCGColorClear;
                break;
            default:
                printf("Color_getConstantColor: unrecognized color %d, returning null\n", which);
                return nullptr;
            }
            return (ColorRef)dl_CGColorGetConstantColor(key);
        }
    }

    void Color_dispose(ColorRef _this) {
        dl_CGColorRelease((dl_CGColorRef)_this);
    }

    namespace ColorSpace {
        ColorSpaceRef createWithName(Name name) {
            dl_CFStringRef cfName = nullptr;
            switch (name) {
            case ColorSpace::Name::GenericGray:
                cfName = dl_kCGColorSpaceGenericGray;
                break;
            case ColorSpace::Name::GenericRGB:
                cfName = dl_kCGColorSpaceGenericRGB;
                break;
            case ColorSpace::Name::GenericCMYK:
                cfName = dl_kCGColorSpaceGenericCMYK;
                break;
            case ColorSpace::Name::GenericRGBLinear:
                cfName = dl_kCGColorSpaceGenericRGBLinear;
                break;
            case ColorSpace::Name::AdobeRGB1998:
                cfName = dl_kCGColorSpaceAdobeRGB1998;
                break;
            case ColorSpace::Name::SRGB:
                cfName = dl_kCGColorSpaceSRGB;
                break;
            case ColorSpace::Name::GenericGrayGamma2_2:
                cfName = dl_kCGColorSpaceGenericGrayGamma2_2;
                break;
            default:
                printf("ColorSpace_createWithName: unknown ColorSpaceName (%d), returning null!\n", name);
                return nullptr;
            }
            return (ColorSpaceRef)dl_CGColorSpaceCreateWithName(cfName);
        }

        ColorSpaceRef createDeviceGray() {
            return (ColorSpaceRef)dl_CGColorSpaceCreateDeviceGray();
        }
    }

    void ColorSpace_dispose(ColorSpaceRef _this) {
        dl_CGColorSpaceRelease((dl_CGColorSpaceRef)_this);
    }

    namespace Gradient {
        GradientRef createWithColorComponents(ColorSpaceRef space, std::vector<Stop> stops) {
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

            return (GradientRef)gradient;
        }
    }

    void Gradient_dispose(GradientRef _this) {
        dl_CGGradientRelease((dl_CGGradientRef)_this);
    }

    namespace Path {
        PathRef createWithRect(Rect rect, std::optional<AffineTransform> transform) {
            return (PathRef)dl_CGPathCreateWithRect(STRUCT_CAST(dl_CGRect, rect), dlOptionalTransform(transform));
        }
        PathRef createWithEllipseInRect(Rect rect, std::optional<AffineTransform> transform) {
            return (PathRef)dl_CGPathCreateWithEllipseInRect(STRUCT_CAST(dl_CGRect, rect), dlOptionalTransform(transform));
        }
        PathRef createWithRoundedRect(Rect rect, double cornerWidth, double cornerHeight, std::optional<AffineTransform> transform) {
            return (PathRef)dl_CGPathCreateWithRoundedRect(STRUCT_CAST(dl_CGRect, rect), cornerWidth, cornerHeight, dlOptionalTransform(transform));
        }
    }

    Point Path_getCurrentPoint(PathRef _this) {
        auto ret = dl_CGPathGetCurrentPoint((dl_CGPathRef)_this);
        return STRUCT_CAST(Point, ret);
    }

    PathRef Path_createCopy(PathRef _this) {
        return (PathRef)dl_CGPathCreateCopy((dl_CGPathRef)_this);
    }

    MutablePathRef Path_createMutableCopy(PathRef _this) {
        return (MutablePathRef)dl_CGPathCreateMutableCopy((dl_CGPathRef)_this);
    }

    void Path_dispose(PathRef _this) {
        dl_CGPathRelease((dl_CGPathRef)_this);
    }

    namespace MutablePath {
        MutablePathRef create() {
            return (MutablePathRef)dl_CGPathCreateMutable();
        }
    }

    void MutablePath_addPath(MutablePathRef _this, PathRef path2, std::optional<AffineTransform> transform) {
        dl_CGPathAddPath((dl_CGMutablePathRef)_this, dlOptionalTransform(transform), (dl_CGPathRef)path2);
    }

    void MutablePath_addRect(MutablePathRef _this, Rect rect, std::optional<AffineTransform> transform) {
        dl_CGPathAddRect((dl_CGMutablePathRef)_this, dlOptionalTransform(transform), STRUCT_CAST(dl_CGRect, rect));
    }

    void MutablePath_addRects(MutablePathRef _this, std::vector<Rect> rects, std::optional<AffineTransform> transform) {
        dl_CGPathAddRects((dl_CGMutablePathRef)_this, dlOptionalTransform(transform), (dl_CGRect*)rects.data(), rects.size());
    }

    void MutablePath_addRoundedRect(MutablePathRef _this, Rect rect, double cornerWidth, double cornerHeight, std::optional<AffineTransform> transform) {
        dl_CGPathAddRoundedRect((dl_CGMutablePathRef)_this, dlOptionalTransform(transform), STRUCT_CAST(dl_CGRect, rect), cornerWidth, cornerHeight);
    }

    void MutablePath_addEllipseInRect(MutablePathRef _this, Rect rect, std::optional<AffineTransform> transform) {
        dl_CGPathAddEllipseInRect((dl_CGMutablePathRef)_this, dlOptionalTransform(transform), STRUCT_CAST(dl_CGRect, rect));
    }

    void MutablePath_moveToPoint(MutablePathRef _this, double x, double y, std::optional<AffineTransform> transform) { // throws MutablePath::TransformException
        try {
            dl_CGPathMoveToPoint((dl_CGMutablePathRef)_this, dlOptionalTransform(transform), x, y);
        }
        catch (cf::Exception e) {
            throw MutablePath::TransformException(e.reason());
        }
    }

    void MutablePath_addArc(MutablePathRef _this, double x, double y, double radius, double startAngle, double endAngle, bool clockwise, std::optional<AffineTransform> transform) { // throws MutablePath::TransformException
        try {
            dl_CGPathAddArc((dl_CGMutablePathRef)_this, dlOptionalTransform(transform), x, y, radius, startAngle, endAngle, clockwise);
        }
        catch (cf::Exception e) {
            throw MutablePath::TransformException(e.reason());
        }
    }

    void MutablePath_addRelativeArc(MutablePathRef _this, double x, double y, double radius, double startAngle, double delta, std::optional<AffineTransform> transform) { // throws MutablePath::TransformException
        try {
            dl_CGPathAddRelativeArc((dl_CGMutablePathRef)_this, dlOptionalTransform(transform), x, y, radius, startAngle, delta);
        }
        catch (cf::Exception e) {
            throw MutablePath::TransformException(e.reason());
        }
    }

    void MutablePath_addArcToPoint(MutablePathRef _this, double x1, double y1, double x2, double y2, double radius, std::optional<AffineTransform> transform) { // throws MutablePath::TransformException
        try {
            dl_CGPathAddArcToPoint((dl_CGMutablePathRef)_this, dlOptionalTransform(transform), x1, y1, x2, y2, radius);
        }
        catch (cf::Exception e) {
            throw MutablePath::TransformException(e.reason());
        }
    }

    void MutablePath_addCurveToPoint(MutablePathRef _this, double cp1x, double cp1y, double cp2x, double cp2y, double x, double y, std::optional<AffineTransform> transform) { // throws MutablePath::TransformException
        try {
            dl_CGPathAddCurveToPoint((dl_CGMutablePathRef)_this, dlOptionalTransform(transform), cp1x, cp1y, cp2x, cp2y, x, y);
        }
        catch (cf::Exception e) {
            throw MutablePath::TransformException(e.reason());
        }
    }

    void MutablePath_addLines(MutablePathRef _this, std::vector<Point> points, std::optional<AffineTransform> transform) { // throws MutablePath::TransformException
        try {
            dl_CGPathAddLines((dl_CGMutablePathRef)_this, dlOptionalTransform(transform), (dl_CGPoint*)points.data(), points.size());
        }
        catch (cf::Exception e) {
            throw MutablePath::TransformException(e.reason());
        }
    }

    void MutablePath_addLineToPoint(MutablePathRef _this, double x, double y, std::optional<AffineTransform> transform) { // throws MutablePath::TransformException
        try {
            dl_CGPathAddLineToPoint((dl_CGMutablePathRef)_this, dlOptionalTransform(transform), x, y);
        }
        catch (cf::Exception e) {
            throw MutablePath::TransformException(e.reason());
        }
    }

    void MutablePath_addQuadCurveToPoint(MutablePathRef _this, double cpx, double cpy, double x, double y, std::optional<AffineTransform> transform) { // throws MutablePath::TransformException
        try {
            dl_CGPathAddQuadCurveToPoint((dl_CGMutablePathRef)_this, dlOptionalTransform(transform), cpx, cpy, x, y);
        }
        catch (cf::Exception e) {
            throw MutablePath::TransformException(e.reason());
        }
    }

    void MutablePath_closeSubpath(MutablePathRef _this) {
        dl_CGPathCloseSubpath((dl_CGMutablePathRef)_this);
    }

    void MutablePath_dispose(MutablePathRef _this) {
        dl_CGPathRelease((dl_CGPathRef)_this);
    }

    void DrawContext_saveGState(DrawContextRef _this) {
        dl_CGContextSaveGState((dl_CGContextRef)_this);
    }

    void DrawContext_restoreGState(DrawContextRef _this) {
        dl_CGContextRestoreGState((dl_CGContextRef)_this);
    }

    void DrawContext_setRGBFillColor(DrawContextRef _this, double red, double green, double blue, double alpha) {
        dl_CGContextSetRGBFillColor((dl_CGContextRef)_this, red, green, blue, alpha);
    }

    void DrawContext_setRGBStrokeColor(DrawContextRef _this, double red, double green, double blue, double alpha) {
        dl_CGContextSetRGBStrokeColor((dl_CGContextRef)_this, red, green, blue, alpha);
    }

    void DrawContext_setFillColorWithColor(DrawContextRef _this, ColorRef color) {
        dl_CGContextSetFillColorWithColor((dl_CGContextRef)_this, (dl_CGColorRef)color);
    }

    void DrawContext_fillRect(DrawContextRef _this, Rect rect) {
        dl_CGContextFillRect((dl_CGContextRef)_this, *((dl_CGRect*)&rect));
    }

    void DrawContext_setTextMatrix(DrawContextRef _this, AffineTransform t) {
        dl_CGContextSetTextMatrix((dl_CGContextRef)_this, STRUCT_CAST(dl_CGAffineTransform,t));
    }

    void DrawContext_setTextPosition(DrawContextRef _this, double x, double y) {
        dl_CGContextSetTextPosition((dl_CGContextRef)_this, x, y);
    }

    void DrawContext_beginPath(DrawContextRef _this) {
        dl_CGContextBeginPath((dl_CGContextRef)_this);
    }

    void DrawContext_addArc(DrawContextRef _this, double x, double y, double radius, double startAngle, double endAngle, bool clockwise) {
        dl_CGContextAddArc((dl_CGContextRef)_this, x, y, radius, startAngle, endAngle, clockwise ? 1 : 0);
    }

    void DrawContext_addArcToPoint(DrawContextRef _this, double x1, double y1, double x2, double y2, double radius) {
        dl_CGContextAddArcToPoint((dl_CGContextRef)_this, x1, y1, x2, y2, radius);
    }

    void DrawContext_drawPath(DrawContextRef _this, Path::DrawingMode mode) {
        dl_CGContextDrawPath((dl_CGContextRef)_this, (dl_CGPathDrawingMode)mode);
    }

    void DrawContext_setStrokeColorWithColor(DrawContextRef _this, ColorRef color) {
        dl_CGContextSetStrokeColorWithColor((dl_CGContextRef)_this, (dl_CGColorRef)color);
    }

    void DrawContext_strokeRectWithWidth(DrawContextRef _this, Rect rect, double width) {
        dl_CGContextStrokeRectWithWidth((dl_CGContextRef)_this, STRUCT_CAST(dl_CGRect, rect), width);
    }

    void DrawContext_moveToPoint(DrawContextRef _this, double x, double y) {
        dl_CGContextMoveToPoint((dl_CGContextRef)_this, x, y);
    }

    void DrawContext_addLineToPoint(DrawContextRef _this, double x, double y) {
        dl_CGContextAddLineToPoint((dl_CGContextRef)_this, x, y);
    }

    void DrawContext_strokePath(DrawContextRef _this) {
        dl_CGContextStrokePath((dl_CGContextRef)_this);
    }

    void DrawContext_setLineDash(DrawContextRef _this, double phase, std::vector<double> lengths) {
        if (lengths.size() > 0) {
            dl_CGContextSetLineDash((dl_CGContextRef)_this, phase, lengths.data(), lengths.size());
        }
        else {
            dl_CGContextSetLineDash((dl_CGContextRef)_this, 0, nullptr, 0);
        }
    }

    void DrawContext_clearLineDash(DrawContextRef _this) {
        dl_CGContextSetLineDash((dl_CGContextRef)_this, 0, nullptr, 0);
    }

    void DrawContext_setLineWidth(DrawContextRef _this, double width) {
        dl_CGContextSetLineWidth((dl_CGContextRef)_this, width);
    }

    void DrawContext_clip(DrawContextRef _this) {
        dl_CGContextClip((dl_CGContextRef)_this);
    }

    void DrawContext_clipToRect(DrawContextRef _this, Rect clipRect) {
        dl_CGContextClipToRect((dl_CGContextRef)_this, STRUCT_CAST(dl_CGRect, clipRect));
    }

    void DrawContext_translateCTM(DrawContextRef _this, double tx, double ty) {
        dl_CGContextTranslateCTM((dl_CGContextRef)_this, tx, ty);
    }

    void DrawContext_scaleCTM(DrawContextRef _this, double scaleX, double scaleY) {
        dl_CGContextScaleCTM((dl_CGContextRef)_this, scaleX, scaleY);
    }

    void DrawContext_rotateCTM(DrawContextRef _this, double angle) {
        dl_CGContextRotateCTM((dl_CGContextRef)_this, angle);
    }

    void DrawContext_concatCTM(DrawContextRef _this, AffineTransform transform) {
        dl_CGContextConcatCTM((dl_CGContextRef)_this, STRUCT_CAST(dl_CGAffineTransform, transform));
    }

    void DrawContext_addPath(DrawContextRef _this, PathRef path) {
        dl_CGContextAddPath((dl_CGContextRef)_this, (dl_CGPathRef)path);
    }

    void DrawContext_fillPath(DrawContextRef _this) {
        dl_CGContextFillPath((dl_CGContextRef)_this);
    }

    void DrawContext_strokeRect(DrawContextRef _this, Rect rect) {
        dl_CGContextStrokeRect((dl_CGContextRef)_this, STRUCT_CAST(dl_CGRect, rect));
    }

    void DrawContext_addRect(DrawContextRef _this, Rect rect) {
        dl_CGContextAddRect((dl_CGContextRef)_this, STRUCT_CAST(dl_CGRect, rect));
    }

    void DrawContext_closePath(DrawContextRef _this) {
        dl_CGContextClosePath((dl_CGContextRef)_this);
    }

    void DrawContext_drawLinearGradient(DrawContextRef _this, GradientRef gradient, Point startPoint, Point endPoint, uint32_t drawOpts) {
        dl_CGContextDrawLinearGradient(
            (dl_CGContextRef)_this,
            (dl_CGGradientRef)gradient,
            STRUCT_CAST(dl_CGPoint, startPoint),
            STRUCT_CAST(dl_CGPoint, endPoint),
            drawOpts);
    }

    void DrawContext_setTextDrawingMode(DrawContextRef _this, TextDrawingMode mode) {
        dl_CGContextSetTextDrawingMode((dl_CGContextRef)_this, (dl_CGTextDrawingMode)mode);
    }

    void DrawContext_clipToMask(DrawContextRef _this, Rect rect, ImageRef mask) {
        dl_CGContextClipToMask((dl_CGContextRef)_this, STRUCT_CAST(dl_CGRect, rect), (dl_CGImageRef)mask);
    }

    void DrawContext_drawImage(DrawContextRef _this, Rect rect, ImageRef image) {
        dl_CGContextDrawImage((dl_CGContextRef)_this, STRUCT_CAST(dl_CGRect, rect), (dl_CGImageRef)image);
    }

    void DrawContext_dispose(DrawContextRef _this) {
        // hmm this might have end-user value when for example drawing into bitmaps?
        // but for window repainting we must never call .dispose() ...
        // would be nice to annotate the API to indicate ownership or something
        // (some .get() accessors for example returning non-owned copies of things, whereas .create() stuff is owned by convention)
        dl_CGContextRelease((dl_CGContextRef)_this);
    }

    struct __BitmapLock {
        BitmapDrawContextRef source;
        void* data;
    };

    void BitmapLock_dispose(BitmapLockRef _this) {
        dl_CGBitmapContextReleaseData((dl_CGContextRef)_this->source);
        delete _this;
    }

    void Image_dispose(ImageRef _this) {
        dl_CGImageRelease((dl_CGImageRef)_this);
    }

    namespace BitmapDrawContext {
        BitmapDrawContextRef create(int32_t width, int32_t height, int32_t bitsPerComponent, int32_t bytesPerRow, ColorSpaceRef space, uint32_t bitmapInfo) {
            return (BitmapDrawContextRef)dl_CGBitmapContextCreate(nullptr, width, height, bitsPerComponent, bytesPerRow, (dl_CGColorSpaceRef)space, bitmapInfo);
        }
    }

    ImageRef BitmapDrawContext_createImage(BitmapDrawContextRef _this) {
        return (ImageRef)dl_CGBitmapContextCreateImage((dl_CGContextRef)_this);
    }

    BitmapLockRef BitmapDrawContext_getData(BitmapDrawContextRef _this) {
        auto ret = new __BitmapLock;
        ret->source = _this;
        ret->data = dl_CGBitmapContextGetData((dl_CGContextRef)_this);
        return ret;
    }

    void BitmapDrawContext_dispose(BitmapDrawContextRef _this) {
        dl_CGContextRelease((dl_CGContextRef)_this);
    }
}
