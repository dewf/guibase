#pragma once

#include "../support/NativeImplServer.h"
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <set>
#include <optional>
#include "../support/result.h"

namespace Drawing
{

    struct __Color; typedef struct __Color* ColorRef;
    struct __ColorSpace; typedef struct __ColorSpace* ColorSpaceRef;
    struct __Gradient; typedef struct __Gradient* GradientRef;
    struct __Path; typedef struct __Path* PathRef;
    struct __MutablePath; typedef struct __MutablePath* MutablePathRef; // extends PathRef
    struct __DrawContext; typedef struct __DrawContext* DrawContextRef;
    struct __BitmapLock; typedef struct __BitmapLock* BitmapLockRef;
    struct __Image; typedef struct __Image* ImageRef;
    struct __BitmapDrawContext; typedef struct __BitmapDrawContext* BitmapDrawContextRef; // extends DrawContextRef

    struct Point {
        double x;
        double y;
    };

    struct Size {
        double width;
        double height;
    };

    struct Rect {
        Point origin;
        Size size;
    };

    struct AffineTransform {
        // static definitions:
        static const AffineTransform identity;
        static AffineTransform translate(AffineTransform input, double tx, double ty);
        static AffineTransform rotate(AffineTransform input, double angle);
        static AffineTransform scale(AffineTransform input, double sx, double sy);
        static AffineTransform concat(AffineTransform t1, AffineTransform t2);
        // fields:
        double a;
        double b;
        double c;
        double d;
        double tx;
        double ty;
    };
    namespace AffineBatchOps {

        namespace Value {
            class Base;
        }

        namespace Value {
            class Translate;
            class Rotate;
            class Scale;
            class Concat;

            class Visitor {
            public:
                virtual void onTranslate(const Translate* translate) = 0;
                virtual void onRotate(const Rotate* rotate) = 0;
                virtual void onScale(const Scale* scale) = 0;
                virtual void onConcat(const Concat* concat) = 0;
            };

            class Base {
            public:
                virtual void accept(Visitor* visitor) = 0;
            };

            class Translate : public Base {
            public:
                const double tx;
                const double ty;
                Translate(double tx, double ty) : tx(tx), ty(ty) {}
                void accept(Visitor* visitor) override {
                    visitor->onTranslate(this);
                }
            };

            class Rotate : public Base {
            public:
                const double angle;
                Rotate(double angle) : angle(angle) {}
                void accept(Visitor* visitor) override {
                    visitor->onRotate(this);
                }
            };

            class Scale : public Base {
            public:
                const double sx;
                const double sy;
                Scale(double sx, double sy) : sx(sx), sy(sy) {}
                void accept(Visitor* visitor) override {
                    visitor->onScale(this);
                }
            };

            class Concat : public Base {
            public:
                const AffineTransform t2;
                Concat(AffineTransform t2) : t2(t2) {}
                void accept(Visitor* visitor) override {
                    visitor->onConcat(this);
                }
            };
        }
        AffineTransform process(AffineTransform init, std::vector<std::shared_ptr<Value::Base>> ops);
    }

    namespace Color {

        enum class Constant {
            White,
            Black,
            Clear
        };
        ColorRef createGenericRGB(double red, double green, double blue, double alpha);
        ColorRef getConstantColor(Constant which);
    }
    void Color_dispose(ColorRef _this);

    namespace ColorSpace {

        enum class Name {
            GenericGray,
            GenericRGB,
            GenericCMYK,
            GenericRGBLinear,
            AdobeRGB1998,
            SRGB,
            GenericGrayGamma2_2
        };
        ColorSpaceRef createWithName(Name name);
        ColorSpaceRef createDeviceGray();
    }
    void ColorSpace_dispose(ColorSpaceRef _this);

    namespace Gradient {

        enum DrawingOptions {
            DrawsBeforeStartLocation = 1,
            DrawsAfterEndLocation = 1 << 1
        };

        struct Stop {
            double location;
            double red;
            double green;
            double blue;
            double alpha;
        };
        GradientRef createWithColorComponents(ColorSpaceRef space, std::vector<Stop> stops);
    }
    void Gradient_dispose(GradientRef _this);

    namespace Path {

        enum class DrawingMode {
            Fill,
            EOFill,
            Stroke,
            FillStroke,
            EOFillStroke
        };
        PathRef createWithRect(Rect rect, std::optional<AffineTransform> transform);
        PathRef createWithEllipseInRect(Rect rect, std::optional<AffineTransform> transform);
        PathRef createWithRoundedRect(Rect rect, double cornerWidth, double cornerHeight, std::optional<AffineTransform> transform);
    }
    Point Path_getCurrentPoint(PathRef _this);
    PathRef Path_createCopy(PathRef _this);
    MutablePathRef Path_createMutableCopy(PathRef _this);
    void Path_dispose(PathRef _this);

    namespace MutablePath {

        class TransformException {
        public:
            std::string error;
            TransformException(std::string error)
                : error(error) {}
        };
        MutablePathRef create();
    }
    void MutablePath_addPath(MutablePathRef _this, PathRef path2, std::optional<AffineTransform> transform);
    void MutablePath_addRect(MutablePathRef _this, Rect rect, std::optional<AffineTransform> transform);
    void MutablePath_addRects(MutablePathRef _this, std::vector<Rect> rects, std::optional<AffineTransform> transform);
    void MutablePath_addRoundedRect(MutablePathRef _this, Rect rect, double cornerWidth, double cornerHeight, std::optional<AffineTransform> transform);
    void MutablePath_addEllipseInRect(MutablePathRef _this, Rect rect, std::optional<AffineTransform> transform);
    void MutablePath_moveToPoint(MutablePathRef _this, double x, double y, std::optional<AffineTransform> transform); // throws MutablePath::TransformException
    void MutablePath_addArc(MutablePathRef _this, double x, double y, double radius, double startAngle, double endAngle, bool clockwise, std::optional<AffineTransform> transform); // throws MutablePath::TransformException
    void MutablePath_addRelativeArc(MutablePathRef _this, double x, double y, double radius, double startAngle, double delta, std::optional<AffineTransform> transform); // throws MutablePath::TransformException
    void MutablePath_addArcToPoint(MutablePathRef _this, double x1, double y1, double x2, double y2, double radius, std::optional<AffineTransform> transform); // throws MutablePath::TransformException
    void MutablePath_addCurveToPoint(MutablePathRef _this, double cp1x, double cp1y, double cp2x, double cp2y, double x, double y, std::optional<AffineTransform> transform); // throws MutablePath::TransformException
    void MutablePath_addLines(MutablePathRef _this, std::vector<Point> points, std::optional<AffineTransform> transform); // throws MutablePath::TransformException
    void MutablePath_addLineToPoint(MutablePathRef _this, double x, double y, std::optional<AffineTransform> transform); // throws MutablePath::TransformException
    void MutablePath_addQuadCurveToPoint(MutablePathRef _this, double cpx, double cpy, double x, double y, std::optional<AffineTransform> transform); // throws MutablePath::TransformException
    void MutablePath_closeSubpath(MutablePathRef _this);
    void MutablePath_dispose(MutablePathRef _this);

    enum class TextDrawingMode {
        Fill,
        Stroke,
        FillStroke,
        Invisible,
        FillClip,
        StrokeClip,
        FillStrokeClip,
        Clip
    };

    void DrawContext_saveGState(DrawContextRef _this);
    void DrawContext_restoreGState(DrawContextRef _this);
    void DrawContext_setRGBFillColor(DrawContextRef _this, double red, double green, double blue, double alpha);
    void DrawContext_setRGBStrokeColor(DrawContextRef _this, double red, double green, double blue, double alpha);
    void DrawContext_setFillColorWithColor(DrawContextRef _this, ColorRef color);
    void DrawContext_fillRect(DrawContextRef _this, Rect rect);
    void DrawContext_setTextMatrix(DrawContextRef _this, AffineTransform t);
    void DrawContext_setTextPosition(DrawContextRef _this, double x, double y);
    void DrawContext_beginPath(DrawContextRef _this);
    void DrawContext_addArc(DrawContextRef _this, double x, double y, double radius, double startAngle, double endAngle, bool clockwise);
    void DrawContext_addArcToPoint(DrawContextRef _this, double x1, double y1, double x2, double y2, double radius);
    void DrawContext_drawPath(DrawContextRef _this, Path::DrawingMode mode);
    void DrawContext_setStrokeColorWithColor(DrawContextRef _this, ColorRef color);
    void DrawContext_strokeRectWithWidth(DrawContextRef _this, Rect rect, double width);
    void DrawContext_moveToPoint(DrawContextRef _this, double x, double y);
    void DrawContext_addLineToPoint(DrawContextRef _this, double x, double y);
    void DrawContext_strokePath(DrawContextRef _this);
    void DrawContext_setLineDash(DrawContextRef _this, double phase, std::vector<double> lengths);
    void DrawContext_clearLineDash(DrawContextRef _this);
    void DrawContext_setLineWidth(DrawContextRef _this, double width);
    void DrawContext_clip(DrawContextRef _this);
    void DrawContext_clipToRect(DrawContextRef _this, Rect clipRect);
    void DrawContext_translateCTM(DrawContextRef _this, double tx, double ty);
    void DrawContext_scaleCTM(DrawContextRef _this, double scaleX, double scaleY);
    void DrawContext_rotateCTM(DrawContextRef _this, double angle);
    void DrawContext_concatCTM(DrawContextRef _this, AffineTransform transform);
    void DrawContext_addPath(DrawContextRef _this, PathRef path);
    void DrawContext_fillPath(DrawContextRef _this);
    void DrawContext_strokeRect(DrawContextRef _this, Rect rect);
    void DrawContext_addRect(DrawContextRef _this, Rect rect);
    void DrawContext_closePath(DrawContextRef _this);
    void DrawContext_drawLinearGradient(DrawContextRef _this, GradientRef gradient, Point startPoint, Point endPoint, uint32_t drawOpts);
    void DrawContext_setTextDrawingMode(DrawContextRef _this, TextDrawingMode mode);
    void DrawContext_clipToMask(DrawContextRef _this, Rect rect, ImageRef mask);
    void DrawContext_drawImage(DrawContextRef _this, Rect rect, ImageRef image);
    void DrawContext_dispose(DrawContextRef _this);

    enum class ImageAlphaInfo {
        None,
        PremultipliedLast,
        PremultipliedFirst,
        Last,
        First,
        NoneSkipLast,
        NoneSkipFirst,
        Only
    };

    enum BitmapInfo {
        AlphaInfoMask = 0x1F,
        FloatInfoMask = 0xF00,
        FloatComponents = 1 << 8,
        ByteOrderMask = 0x7000,
        ByteOrderDefault = 0 << 12,
        ByteOrder16Little = 1 << 12,
        ByteOrder32Little = 2 << 12,
        ByteOrder16Big = 3 << 12,
        ByteOrder32Big = 4 << 12
    };

    void BitmapLock_dispose(BitmapLockRef _this);

    void Image_dispose(ImageRef _this);

    namespace BitmapDrawContext {
        BitmapDrawContextRef create(int32_t width, int32_t height, int32_t bitsPerComponent, int32_t bytesPerRow, ColorSpaceRef space, uint32_t bitmapInfo);
    }
    ImageRef BitmapDrawContext_createImage(BitmapDrawContextRef _this);
    BitmapLockRef BitmapDrawContext_getData(BitmapDrawContextRef _this);
    void BitmapDrawContext_dispose(BitmapDrawContextRef _this);
}
