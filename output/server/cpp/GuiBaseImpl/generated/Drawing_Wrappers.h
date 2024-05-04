#pragma once
#include "Drawing.h"

namespace Drawing
{

    void __AffineTransform_Option__push(std::optional<AffineTransform> value, bool isReturn);
    std::optional<AffineTransform> __AffineTransform_Option__pop();

    void Point__push(Point value, bool isReturn);
    Point Point__pop();

    void Size__push(Size value, bool isReturn);
    Size Size__pop();

    void Rect__push(Rect value, bool isReturn);
    Rect Rect__pop();

    void AffineTransform__push(AffineTransform value, bool isReturn);
    AffineTransform AffineTransform__pop();
    namespace AffineTransform__ {

        void translate__wrapper();

        void rotate__wrapper();

        void scale__wrapper();

        void concat__wrapper();
    }
    namespace AffineBatchOps {
        void Value__push(std::shared_ptr<Value::Base> value, bool isReturn);
        std::shared_ptr<Value::Base> Value__pop();

        void process__wrapper();
    }

    void Color__push(ColorRef value);
    ColorRef Color__pop();
    namespace Color {

        void Constant__push(Constant value);
        Constant Constant__pop();

        void createGenericRGB__wrapper();

        void getConstantColor__wrapper();
    }

    void Color_dispose__wrapper();

    void ColorSpace__push(ColorSpaceRef value);
    ColorSpaceRef ColorSpace__pop();
    namespace ColorSpace {

        void Name__push(Name value);
        Name Name__pop();

        void createWithName__wrapper();

        void createDeviceGray__wrapper();
    }

    void ColorSpace_dispose__wrapper();

    void Gradient__push(GradientRef value);
    GradientRef Gradient__pop();
    namespace Gradient {

        void DrawingOptions__push(uint32_t value);
        uint32_t DrawingOptions__pop();

        void Stop__push(Stop value, bool isReturn);
        Stop Stop__pop();

        void createWithColorComponents__wrapper();
    }

    void Gradient_dispose__wrapper();

    void Path__push(PathRef value);
    PathRef Path__pop();
    namespace Path {

        void DrawingMode__push(DrawingMode value);
        DrawingMode DrawingMode__pop();

        void createWithRect__wrapper();

        void createWithEllipseInRect__wrapper();

        void createWithRoundedRect__wrapper();
    }

    void Path_getCurrentPoint__wrapper();

    void Path_createCopy__wrapper();

    void Path_createMutableCopy__wrapper();

    void Path_dispose__wrapper();

    void MutablePath__push(MutablePathRef value);
    MutablePathRef MutablePath__pop();
    namespace MutablePath {

        void TransformException__push(TransformException e);
        void TransformException__buildAndThrow();

        void create__wrapper();
    }

    void MutablePath_addPath__wrapper();

    void MutablePath_addRect__wrapper();

    void MutablePath_addRects__wrapper();

    void MutablePath_addRoundedRect__wrapper();

    void MutablePath_addEllipseInRect__wrapper();

    void MutablePath_moveToPoint__wrapper();

    void MutablePath_addArc__wrapper();

    void MutablePath_addRelativeArc__wrapper();

    void MutablePath_addArcToPoint__wrapper();

    void MutablePath_addCurveToPoint__wrapper();

    void MutablePath_addLines__wrapper();

    void MutablePath_addLineToPoint__wrapper();

    void MutablePath_addQuadCurveToPoint__wrapper();

    void MutablePath_closeSubpath__wrapper();

    void MutablePath_dispose__wrapper();

    void TextDrawingMode__push(TextDrawingMode value);
    TextDrawingMode TextDrawingMode__pop();

    void DrawContext__push(DrawContextRef value);
    DrawContextRef DrawContext__pop();

    void DrawContext_saveGState__wrapper();

    void DrawContext_restoreGState__wrapper();

    void DrawContext_setRGBFillColor__wrapper();

    void DrawContext_setRGBStrokeColor__wrapper();

    void DrawContext_setFillColorWithColor__wrapper();

    void DrawContext_fillRect__wrapper();

    void DrawContext_setTextMatrix__wrapper();

    void DrawContext_setTextPosition__wrapper();

    void DrawContext_beginPath__wrapper();

    void DrawContext_addArc__wrapper();

    void DrawContext_addArcToPoint__wrapper();

    void DrawContext_drawPath__wrapper();

    void DrawContext_setStrokeColorWithColor__wrapper();

    void DrawContext_strokeRectWithWidth__wrapper();

    void DrawContext_moveToPoint__wrapper();

    void DrawContext_addLineToPoint__wrapper();

    void DrawContext_strokePath__wrapper();

    void DrawContext_setLineDash__wrapper();

    void DrawContext_clearLineDash__wrapper();

    void DrawContext_setLineWidth__wrapper();

    void DrawContext_clip__wrapper();

    void DrawContext_clipToRect__wrapper();

    void DrawContext_translateCTM__wrapper();

    void DrawContext_scaleCTM__wrapper();

    void DrawContext_rotateCTM__wrapper();

    void DrawContext_concatCTM__wrapper();

    void DrawContext_addPath__wrapper();

    void DrawContext_fillPath__wrapper();

    void DrawContext_strokeRect__wrapper();

    void DrawContext_addRect__wrapper();

    void DrawContext_closePath__wrapper();

    void DrawContext_drawLinearGradient__wrapper();

    void DrawContext_setTextDrawingMode__wrapper();

    void DrawContext_clipToMask__wrapper();

    void DrawContext_drawImage__wrapper();

    void DrawContext_dispose__wrapper();

    void ImageAlphaInfo__push(ImageAlphaInfo value);
    ImageAlphaInfo ImageAlphaInfo__pop();

    void BitmapInfo__push(uint32_t value);
    uint32_t BitmapInfo__pop();

    void BitmapLock__push(BitmapLockRef value);
    BitmapLockRef BitmapLock__pop();

    void BitmapLock_dispose__wrapper();

    void Image__push(ImageRef value);
    ImageRef Image__pop();

    void Image_dispose__wrapper();

    void BitmapDrawContext__push(BitmapDrawContextRef value);
    BitmapDrawContextRef BitmapDrawContext__pop();
    namespace BitmapDrawContext {

        void create__wrapper();
    }

    void BitmapDrawContext_createImage__wrapper();

    void BitmapDrawContext_getData__wrapper();

    void BitmapDrawContext_dispose__wrapper();

    int __register();
}
