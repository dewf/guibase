#include "../support/NativeImplServer.h"
#include "Drawing_wrappers.h"
#include "Drawing.h"

namespace Drawing
{
    // built-in array type: std::vector<double>

    void __AffineTransform_Option__push(std::optional<AffineTransform> value, bool isReturn) {
        if (value.has_value()) {
            AffineTransform__push(value.value(), isReturn);
            ni_pushBool(true);
        }
        else {
            ni_pushBool(false);
        }
    }

    std::optional<AffineTransform> __AffineTransform_Option__pop() {
        std::optional<AffineTransform> maybeValue;
        auto hasValue = ni_popBool();
        if (hasValue) {
            maybeValue =  AffineTransform__pop();
        }
        return maybeValue;
    }
    void __Point_Array__push(std::vector<Point> values, bool isReturn) {
        std::vector<double> y_values;
        std::vector<double> x_values;
        for (auto v = values.begin(); v != values.end(); v++) {
            y_values.push_back(v->y);
            x_values.push_back(v->x);
        }
        pushDoubleArrayInternal(y_values);
        pushDoubleArrayInternal(x_values);
    }

    std::vector<Point> __Point_Array__pop() {
        auto x_values = popDoubleArrayInternal();
        auto y_values = popDoubleArrayInternal();
        std::vector<Point> __ret;
        for (auto i = 0; i < x_values.size(); i++) {
            Point __value;
            __value.x = x_values[i];
            __value.y = y_values[i];
            __ret.push_back(__value);
        }
        return __ret;
    }
    void __Size_Array__push(std::vector<Size> values, bool isReturn) {
        std::vector<double> height_values;
        std::vector<double> width_values;
        for (auto v = values.begin(); v != values.end(); v++) {
            height_values.push_back(v->height);
            width_values.push_back(v->width);
        }
        pushDoubleArrayInternal(height_values);
        pushDoubleArrayInternal(width_values);
    }

    std::vector<Size> __Size_Array__pop() {
        auto width_values = popDoubleArrayInternal();
        auto height_values = popDoubleArrayInternal();
        std::vector<Size> __ret;
        for (auto i = 0; i < width_values.size(); i++) {
            Size __value;
            __value.width = width_values[i];
            __value.height = height_values[i];
            __ret.push_back(__value);
        }
        return __ret;
    }
    void __Rect_Array__push(std::vector<Rect> values, bool isReturn) {
        std::vector<Size> size_values;
        std::vector<Point> origin_values;
        for (auto v = values.begin(); v != values.end(); v++) {
            size_values.push_back(v->size);
            origin_values.push_back(v->origin);
        }
        __Size_Array__push(size_values, isReturn);
        __Point_Array__push(origin_values, isReturn);
    }

    std::vector<Rect> __Rect_Array__pop() {
        auto origin_values = __Point_Array__pop();
        auto size_values = __Size_Array__pop();
        std::vector<Rect> __ret;
        for (auto i = 0; i < origin_values.size(); i++) {
            Rect __value;
            __value.origin = origin_values[i];
            __value.size = size_values[i];
            __ret.push_back(__value);
        }
        return __ret;
    }
    void __Gradient_Stop_Array__push(std::vector<Gradient::Stop> values, bool isReturn) {
        std::vector<double> alpha_values;
        std::vector<double> blue_values;
        std::vector<double> green_values;
        std::vector<double> red_values;
        std::vector<double> location_values;
        for (auto v = values.begin(); v != values.end(); v++) {
            alpha_values.push_back(v->alpha);
            blue_values.push_back(v->blue);
            green_values.push_back(v->green);
            red_values.push_back(v->red);
            location_values.push_back(v->location);
        }
        pushDoubleArrayInternal(alpha_values);
        pushDoubleArrayInternal(blue_values);
        pushDoubleArrayInternal(green_values);
        pushDoubleArrayInternal(red_values);
        pushDoubleArrayInternal(location_values);
    }

    std::vector<Gradient::Stop> __Gradient_Stop_Array__pop() {
        auto location_values = popDoubleArrayInternal();
        auto red_values = popDoubleArrayInternal();
        auto green_values = popDoubleArrayInternal();
        auto blue_values = popDoubleArrayInternal();
        auto alpha_values = popDoubleArrayInternal();
        std::vector<Gradient::Stop> __ret;
        for (auto i = 0; i < location_values.size(); i++) {
            Gradient::Stop __value;
            __value.location = location_values[i];
            __value.red = red_values[i];
            __value.green = green_values[i];
            __value.blue = blue_values[i];
            __value.alpha = alpha_values[i];
            __ret.push_back(__value);
        }
        return __ret;
    }
    void __AffineBatchOps_Value_Array__push(std::vector<std::shared_ptr<AffineBatchOps::Value::Base>> values, bool isReturn) {
        for (auto v = values.rbegin(); v != values.rend(); v++) {
            AffineBatchOps::Value__push(*v, isReturn);
        }
        ni_pushSizeT(values.size());
    }

    std::vector<std::shared_ptr<AffineBatchOps::Value::Base>> __AffineBatchOps_Value_Array__pop() {
        std::vector<std::shared_ptr<AffineBatchOps::Value::Base>> __ret;
        auto count = ni_popSizeT();
        for (auto i = 0; i < count; i++) {
            auto value = AffineBatchOps::Value__pop();
            __ret.push_back(value);
        }
        return __ret;
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
    namespace AffineTransform__ {

        void translate__wrapper() {
            auto input = AffineTransform__pop();
            auto tx = ni_popDouble();
            auto ty = ni_popDouble();
            AffineTransform__push(AffineTransform::translate(input, tx, ty), true);
        }

        void rotate__wrapper() {
            auto input = AffineTransform__pop();
            auto angle = ni_popDouble();
            AffineTransform__push(AffineTransform::rotate(input, angle), true);
        }

        void scale__wrapper() {
            auto input = AffineTransform__pop();
            auto sx = ni_popDouble();
            auto sy = ni_popDouble();
            AffineTransform__push(AffineTransform::scale(input, sx, sy), true);
        }

        void concat__wrapper() {
            auto t1 = AffineTransform__pop();
            auto t2 = AffineTransform__pop();
            AffineTransform__push(AffineTransform::concat(t1, t2), true);
        }
    }
    namespace AffineBatchOps {

        class Value_PushVisitor : public Value::Visitor {
        private:
            bool isReturn;
        public:
            Value_PushVisitor(bool isReturn) : isReturn(isReturn) {}
            void onTranslate(const Value::Translate* translate) override {
                ni_pushDouble(translate->ty);
                ni_pushDouble(translate->tx);
                // kind:
                ni_pushInt32(0);
            }
            void onRotate(const Value::Rotate* rotate) override {
                ni_pushDouble(rotate->angle);
                // kind:
                ni_pushInt32(1);
            }
            void onScale(const Value::Scale* scale) override {
                ni_pushDouble(scale->sy);
                ni_pushDouble(scale->sx);
                // kind:
                ni_pushInt32(2);
            }
            void onConcat(const Value::Concat* concat) override {
                AffineTransform__push(concat->t2, isReturn);
                // kind:
                ni_pushInt32(3);
            }
        };

        void Value__push(std::shared_ptr<Value::Base> value, bool isReturn) {
            Value_PushVisitor v(isReturn);
            value->accept((Value::Visitor*)&v);
        }

        std::shared_ptr<Value::Base> Value__pop() {
            Value::Base* __ret = nullptr;
            switch (ni_popInt32()) {
            case 0: {
                auto tx = ni_popDouble();
                auto ty = ni_popDouble();
                __ret = new Value::Translate(tx, ty);
                break;
            }
            case 1: {
                auto angle = ni_popDouble();
                __ret = new Value::Rotate(angle);
                break;
            }
            case 2: {
                auto sx = ni_popDouble();
                auto sy = ni_popDouble();
                __ret = new Value::Scale(sx, sy);
                break;
            }
            case 3: {
                auto t2 = AffineTransform__pop();
                __ret = new Value::Concat(t2);
                break;
            }
            default:
                printf("C++ Value__pop() - unknown kind! returning null\n");
            }
            return std::shared_ptr<Value::Base>(__ret);
        }

        void process__wrapper() {
            auto init = AffineTransform__pop();
            auto ops = __AffineBatchOps_Value_Array__pop();
            AffineTransform__push(process(init, ops), true);
        }
    }
    void Color__push(ColorRef value) {
        ni_pushPtr(value);
    }

    ColorRef Color__pop() {
        return (ColorRef)ni_popPtr();
    }
    namespace Color {
        void Constant__push(Constant value) {
            ni_pushInt32((int32_t)value);
        }

        Constant Constant__pop() {
            auto tag = ni_popInt32();
            return (Constant)tag;
        }

        void createGenericRGB__wrapper() {
            auto red = ni_popDouble();
            auto green = ni_popDouble();
            auto blue = ni_popDouble();
            auto alpha = ni_popDouble();
            Color__push(createGenericRGB(red, green, blue, alpha));
        }

        void getConstantColor__wrapper() {
            auto which = Constant__pop();
            Color__push(getConstantColor(which));
        }
    }

    void Color_dispose__wrapper() {
        auto _this = Color__pop();
        Color_dispose(_this);
    }
    void ColorSpace__push(ColorSpaceRef value) {
        ni_pushPtr(value);
    }

    ColorSpaceRef ColorSpace__pop() {
        return (ColorSpaceRef)ni_popPtr();
    }
    namespace ColorSpace {
        void Name__push(Name value) {
            ni_pushInt32((int32_t)value);
        }

        Name Name__pop() {
            auto tag = ni_popInt32();
            return (Name)tag;
        }

        void createWithName__wrapper() {
            auto name = Name__pop();
            ColorSpace__push(createWithName(name));
        }

        void createDeviceGray__wrapper() {
            ColorSpace__push(createDeviceGray());
        }
    }

    void ColorSpace_dispose__wrapper() {
        auto _this = ColorSpace__pop();
        ColorSpace_dispose(_this);
    }
    void Gradient__push(GradientRef value) {
        ni_pushPtr(value);
    }

    GradientRef Gradient__pop() {
        return (GradientRef)ni_popPtr();
    }
    namespace Gradient {
        void DrawingOptions__push(uint32_t value) {
            ni_pushUInt32(value);
        }

        uint32_t DrawingOptions__pop() {
            return ni_popUInt32();
        }
        void Stop__push(Stop value, bool isReturn) {
            ni_pushDouble(value.alpha);
            ni_pushDouble(value.blue);
            ni_pushDouble(value.green);
            ni_pushDouble(value.red);
            ni_pushDouble(value.location);
        }

        Stop Stop__pop() {
            auto location = ni_popDouble();
            auto red = ni_popDouble();
            auto green = ni_popDouble();
            auto blue = ni_popDouble();
            auto alpha = ni_popDouble();
            return Stop { location, red, green, blue, alpha };
        }

        void createWithColorComponents__wrapper() {
            auto space = ColorSpace__pop();
            auto stops = __Gradient_Stop_Array__pop();
            Gradient__push(createWithColorComponents(space, stops));
        }
    }

    void Gradient_dispose__wrapper() {
        auto _this = Gradient__pop();
        Gradient_dispose(_this);
    }
    void Path__push(PathRef value) {
        ni_pushPtr(value);
    }

    PathRef Path__pop() {
        return (PathRef)ni_popPtr();
    }
    namespace Path {
        void DrawingMode__push(DrawingMode value) {
            ni_pushInt32((int32_t)value);
        }

        DrawingMode DrawingMode__pop() {
            auto tag = ni_popInt32();
            return (DrawingMode)tag;
        }

        void createWithRect__wrapper() {
            auto rect = Rect__pop();
            auto transform = __AffineTransform_Option__pop();
            Path__push(createWithRect(rect, transform));
        }

        void createWithEllipseInRect__wrapper() {
            auto rect = Rect__pop();
            auto transform = __AffineTransform_Option__pop();
            Path__push(createWithEllipseInRect(rect, transform));
        }

        void createWithRoundedRect__wrapper() {
            auto rect = Rect__pop();
            auto cornerWidth = ni_popDouble();
            auto cornerHeight = ni_popDouble();
            auto transform = __AffineTransform_Option__pop();
            Path__push(createWithRoundedRect(rect, cornerWidth, cornerHeight, transform));
        }
    }

    void Path_getCurrentPoint__wrapper() {
        auto _this = Path__pop();
        Point__push(Path_getCurrentPoint(_this), true);
    }

    void Path_createCopy__wrapper() {
        auto _this = Path__pop();
        Path__push(Path_createCopy(_this));
    }

    void Path_createMutableCopy__wrapper() {
        auto _this = Path__pop();
        MutablePath__push(Path_createMutableCopy(_this));
    }

    void Path_dispose__wrapper() {
        auto _this = Path__pop();
        Path_dispose(_this);
    }
    void MutablePath__push(MutablePathRef value) {
        ni_pushPtr(value);
    }

    MutablePathRef MutablePath__pop() {
        return (MutablePathRef)ni_popPtr();
    }
    namespace MutablePath {
        ni_ExceptionRef transformException;

        void TransformException__push(TransformException e) {
            pushStringInternal(e.error);
        }

        void TransformException__buildAndThrow() {
            auto error = popStringInternal();
            throw TransformException(error);
        }

        void create__wrapper() {
            MutablePath__push(create());
        }
    }

    void MutablePath_addPath__wrapper() {
        auto _this = MutablePath__pop();
        auto path2 = Path__pop();
        auto transform = __AffineTransform_Option__pop();
        MutablePath_addPath(_this, path2, transform);
    }

    void MutablePath_addRect__wrapper() {
        auto _this = MutablePath__pop();
        auto rect = Rect__pop();
        auto transform = __AffineTransform_Option__pop();
        MutablePath_addRect(_this, rect, transform);
    }

    void MutablePath_addRects__wrapper() {
        auto _this = MutablePath__pop();
        auto rects = __Rect_Array__pop();
        auto transform = __AffineTransform_Option__pop();
        MutablePath_addRects(_this, rects, transform);
    }

    void MutablePath_addRoundedRect__wrapper() {
        auto _this = MutablePath__pop();
        auto rect = Rect__pop();
        auto cornerWidth = ni_popDouble();
        auto cornerHeight = ni_popDouble();
        auto transform = __AffineTransform_Option__pop();
        MutablePath_addRoundedRect(_this, rect, cornerWidth, cornerHeight, transform);
    }

    void MutablePath_addEllipseInRect__wrapper() {
        auto _this = MutablePath__pop();
        auto rect = Rect__pop();
        auto transform = __AffineTransform_Option__pop();
        MutablePath_addEllipseInRect(_this, rect, transform);
    }

    void MutablePath_moveToPoint__wrapper() {
        auto _this = MutablePath__pop();
        auto x = ni_popDouble();
        auto y = ni_popDouble();
        auto transform = __AffineTransform_Option__pop();
        try {
            MutablePath_moveToPoint(_this, x, y, transform);
        }
        catch (const MutablePath::TransformException& e) {
            ni_setException(MutablePath::transformException);
            MutablePath::TransformException__push(e);
        }
    }

    void MutablePath_addArc__wrapper() {
        auto _this = MutablePath__pop();
        auto x = ni_popDouble();
        auto y = ni_popDouble();
        auto radius = ni_popDouble();
        auto startAngle = ni_popDouble();
        auto endAngle = ni_popDouble();
        auto clockwise = ni_popBool();
        auto transform = __AffineTransform_Option__pop();
        try {
            MutablePath_addArc(_this, x, y, radius, startAngle, endAngle, clockwise, transform);
        }
        catch (const MutablePath::TransformException& e) {
            ni_setException(MutablePath::transformException);
            MutablePath::TransformException__push(e);
        }
    }

    void MutablePath_addRelativeArc__wrapper() {
        auto _this = MutablePath__pop();
        auto x = ni_popDouble();
        auto y = ni_popDouble();
        auto radius = ni_popDouble();
        auto startAngle = ni_popDouble();
        auto delta = ni_popDouble();
        auto transform = __AffineTransform_Option__pop();
        try {
            MutablePath_addRelativeArc(_this, x, y, radius, startAngle, delta, transform);
        }
        catch (const MutablePath::TransformException& e) {
            ni_setException(MutablePath::transformException);
            MutablePath::TransformException__push(e);
        }
    }

    void MutablePath_addArcToPoint__wrapper() {
        auto _this = MutablePath__pop();
        auto x1 = ni_popDouble();
        auto y1 = ni_popDouble();
        auto x2 = ni_popDouble();
        auto y2 = ni_popDouble();
        auto radius = ni_popDouble();
        auto transform = __AffineTransform_Option__pop();
        try {
            MutablePath_addArcToPoint(_this, x1, y1, x2, y2, radius, transform);
        }
        catch (const MutablePath::TransformException& e) {
            ni_setException(MutablePath::transformException);
            MutablePath::TransformException__push(e);
        }
    }

    void MutablePath_addCurveToPoint__wrapper() {
        auto _this = MutablePath__pop();
        auto cp1x = ni_popDouble();
        auto cp1y = ni_popDouble();
        auto cp2x = ni_popDouble();
        auto cp2y = ni_popDouble();
        auto x = ni_popDouble();
        auto y = ni_popDouble();
        auto transform = __AffineTransform_Option__pop();
        try {
            MutablePath_addCurveToPoint(_this, cp1x, cp1y, cp2x, cp2y, x, y, transform);
        }
        catch (const MutablePath::TransformException& e) {
            ni_setException(MutablePath::transformException);
            MutablePath::TransformException__push(e);
        }
    }

    void MutablePath_addLines__wrapper() {
        auto _this = MutablePath__pop();
        auto points = __Point_Array__pop();
        auto transform = __AffineTransform_Option__pop();
        try {
            MutablePath_addLines(_this, points, transform);
        }
        catch (const MutablePath::TransformException& e) {
            ni_setException(MutablePath::transformException);
            MutablePath::TransformException__push(e);
        }
    }

    void MutablePath_addLineToPoint__wrapper() {
        auto _this = MutablePath__pop();
        auto x = ni_popDouble();
        auto y = ni_popDouble();
        auto transform = __AffineTransform_Option__pop();
        try {
            MutablePath_addLineToPoint(_this, x, y, transform);
        }
        catch (const MutablePath::TransformException& e) {
            ni_setException(MutablePath::transformException);
            MutablePath::TransformException__push(e);
        }
    }

    void MutablePath_addQuadCurveToPoint__wrapper() {
        auto _this = MutablePath__pop();
        auto cpx = ni_popDouble();
        auto cpy = ni_popDouble();
        auto x = ni_popDouble();
        auto y = ni_popDouble();
        auto transform = __AffineTransform_Option__pop();
        try {
            MutablePath_addQuadCurveToPoint(_this, cpx, cpy, x, y, transform);
        }
        catch (const MutablePath::TransformException& e) {
            ni_setException(MutablePath::transformException);
            MutablePath::TransformException__push(e);
        }
    }

    void MutablePath_closeSubpath__wrapper() {
        auto _this = MutablePath__pop();
        MutablePath_closeSubpath(_this);
    }

    void MutablePath_dispose__wrapper() {
        auto _this = MutablePath__pop();
        MutablePath_dispose(_this);
    }
    void TextDrawingMode__push(TextDrawingMode value) {
        ni_pushInt32((int32_t)value);
    }

    TextDrawingMode TextDrawingMode__pop() {
        auto tag = ni_popInt32();
        return (TextDrawingMode)tag;
    }
    void DrawContext__push(DrawContextRef value) {
        ni_pushPtr(value);
    }

    DrawContextRef DrawContext__pop() {
        return (DrawContextRef)ni_popPtr();
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

    void DrawContext_setRGBStrokeColor__wrapper() {
        auto _this = DrawContext__pop();
        auto red = ni_popDouble();
        auto green = ni_popDouble();
        auto blue = ni_popDouble();
        auto alpha = ni_popDouble();
        DrawContext_setRGBStrokeColor(_this, red, green, blue, alpha);
    }

    void DrawContext_setFillColorWithColor__wrapper() {
        auto _this = DrawContext__pop();
        auto color = Color__pop();
        DrawContext_setFillColorWithColor(_this, color);
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

    void DrawContext_beginPath__wrapper() {
        auto _this = DrawContext__pop();
        DrawContext_beginPath(_this);
    }

    void DrawContext_addArc__wrapper() {
        auto _this = DrawContext__pop();
        auto x = ni_popDouble();
        auto y = ni_popDouble();
        auto radius = ni_popDouble();
        auto startAngle = ni_popDouble();
        auto endAngle = ni_popDouble();
        auto clockwise = ni_popBool();
        DrawContext_addArc(_this, x, y, radius, startAngle, endAngle, clockwise);
    }

    void DrawContext_addArcToPoint__wrapper() {
        auto _this = DrawContext__pop();
        auto x1 = ni_popDouble();
        auto y1 = ni_popDouble();
        auto x2 = ni_popDouble();
        auto y2 = ni_popDouble();
        auto radius = ni_popDouble();
        DrawContext_addArcToPoint(_this, x1, y1, x2, y2, radius);
    }

    void DrawContext_drawPath__wrapper() {
        auto _this = DrawContext__pop();
        auto mode = Path::DrawingMode__pop();
        DrawContext_drawPath(_this, mode);
    }

    void DrawContext_setStrokeColorWithColor__wrapper() {
        auto _this = DrawContext__pop();
        auto color = Color__pop();
        DrawContext_setStrokeColorWithColor(_this, color);
    }

    void DrawContext_strokeRectWithWidth__wrapper() {
        auto _this = DrawContext__pop();
        auto rect = Rect__pop();
        auto width = ni_popDouble();
        DrawContext_strokeRectWithWidth(_this, rect, width);
    }

    void DrawContext_moveToPoint__wrapper() {
        auto _this = DrawContext__pop();
        auto x = ni_popDouble();
        auto y = ni_popDouble();
        DrawContext_moveToPoint(_this, x, y);
    }

    void DrawContext_addLineToPoint__wrapper() {
        auto _this = DrawContext__pop();
        auto x = ni_popDouble();
        auto y = ni_popDouble();
        DrawContext_addLineToPoint(_this, x, y);
    }

    void DrawContext_strokePath__wrapper() {
        auto _this = DrawContext__pop();
        DrawContext_strokePath(_this);
    }

    void DrawContext_setLineDash__wrapper() {
        auto _this = DrawContext__pop();
        auto phase = ni_popDouble();
        auto lengths = popDoubleArrayInternal();
        DrawContext_setLineDash(_this, phase, lengths);
    }

    void DrawContext_clearLineDash__wrapper() {
        auto _this = DrawContext__pop();
        DrawContext_clearLineDash(_this);
    }

    void DrawContext_setLineWidth__wrapper() {
        auto _this = DrawContext__pop();
        auto width = ni_popDouble();
        DrawContext_setLineWidth(_this, width);
    }

    void DrawContext_clip__wrapper() {
        auto _this = DrawContext__pop();
        DrawContext_clip(_this);
    }

    void DrawContext_clipToRect__wrapper() {
        auto _this = DrawContext__pop();
        auto clipRect = Rect__pop();
        DrawContext_clipToRect(_this, clipRect);
    }

    void DrawContext_translateCTM__wrapper() {
        auto _this = DrawContext__pop();
        auto tx = ni_popDouble();
        auto ty = ni_popDouble();
        DrawContext_translateCTM(_this, tx, ty);
    }

    void DrawContext_scaleCTM__wrapper() {
        auto _this = DrawContext__pop();
        auto scaleX = ni_popDouble();
        auto scaleY = ni_popDouble();
        DrawContext_scaleCTM(_this, scaleX, scaleY);
    }

    void DrawContext_rotateCTM__wrapper() {
        auto _this = DrawContext__pop();
        auto angle = ni_popDouble();
        DrawContext_rotateCTM(_this, angle);
    }

    void DrawContext_concatCTM__wrapper() {
        auto _this = DrawContext__pop();
        auto transform = AffineTransform__pop();
        DrawContext_concatCTM(_this, transform);
    }

    void DrawContext_addPath__wrapper() {
        auto _this = DrawContext__pop();
        auto path = Path__pop();
        DrawContext_addPath(_this, path);
    }

    void DrawContext_fillPath__wrapper() {
        auto _this = DrawContext__pop();
        DrawContext_fillPath(_this);
    }

    void DrawContext_strokeRect__wrapper() {
        auto _this = DrawContext__pop();
        auto rect = Rect__pop();
        DrawContext_strokeRect(_this, rect);
    }

    void DrawContext_addRect__wrapper() {
        auto _this = DrawContext__pop();
        auto rect = Rect__pop();
        DrawContext_addRect(_this, rect);
    }

    void DrawContext_closePath__wrapper() {
        auto _this = DrawContext__pop();
        DrawContext_closePath(_this);
    }

    void DrawContext_drawLinearGradient__wrapper() {
        auto _this = DrawContext__pop();
        auto gradient = Gradient__pop();
        auto startPoint = Point__pop();
        auto endPoint = Point__pop();
        auto drawOpts = Gradient::DrawingOptions__pop();
        DrawContext_drawLinearGradient(_this, gradient, startPoint, endPoint, drawOpts);
    }

    void DrawContext_setTextDrawingMode__wrapper() {
        auto _this = DrawContext__pop();
        auto mode = TextDrawingMode__pop();
        DrawContext_setTextDrawingMode(_this, mode);
    }

    void DrawContext_clipToMask__wrapper() {
        auto _this = DrawContext__pop();
        auto rect = Rect__pop();
        auto mask = Image__pop();
        DrawContext_clipToMask(_this, rect, mask);
    }

    void DrawContext_drawImage__wrapper() {
        auto _this = DrawContext__pop();
        auto rect = Rect__pop();
        auto image = Image__pop();
        DrawContext_drawImage(_this, rect, image);
    }

    void DrawContext_dispose__wrapper() {
        auto _this = DrawContext__pop();
        DrawContext_dispose(_this);
    }
    void ImageAlphaInfo__push(ImageAlphaInfo value) {
        ni_pushInt32((int32_t)value);
    }

    ImageAlphaInfo ImageAlphaInfo__pop() {
        auto tag = ni_popInt32();
        return (ImageAlphaInfo)tag;
    }
    void BitmapInfo__push(uint32_t value) {
        ni_pushUInt32(value);
    }

    uint32_t BitmapInfo__pop() {
        return ni_popUInt32();
    }
    void BitmapLock__push(BitmapLockRef value) {
        ni_pushPtr(value);
    }

    BitmapLockRef BitmapLock__pop() {
        return (BitmapLockRef)ni_popPtr();
    }

    void BitmapLock_dispose__wrapper() {
        auto _this = BitmapLock__pop();
        BitmapLock_dispose(_this);
    }
    void Image__push(ImageRef value) {
        ni_pushPtr(value);
    }

    ImageRef Image__pop() {
        return (ImageRef)ni_popPtr();
    }

    void Image_dispose__wrapper() {
        auto _this = Image__pop();
        Image_dispose(_this);
    }
    void BitmapDrawContext__push(BitmapDrawContextRef value) {
        ni_pushPtr(value);
    }

    BitmapDrawContextRef BitmapDrawContext__pop() {
        return (BitmapDrawContextRef)ni_popPtr();
    }
    namespace BitmapDrawContext {

        void create__wrapper() {
            auto width = ni_popInt32();
            auto height = ni_popInt32();
            auto bitsPerComponent = ni_popInt32();
            auto bytesPerRow = ni_popInt32();
            auto space = ColorSpace__pop();
            auto bitmapInfo = BitmapInfo__pop();
            BitmapDrawContext__push(create(width, height, bitsPerComponent, bytesPerRow, space, bitmapInfo));
        }
    }

    void BitmapDrawContext_createImage__wrapper() {
        auto _this = BitmapDrawContext__pop();
        Image__push(BitmapDrawContext_createImage(_this));
    }

    void BitmapDrawContext_getData__wrapper() {
        auto _this = BitmapDrawContext__pop();
        BitmapLock__push(BitmapDrawContext_getData(_this));
    }

    void BitmapDrawContext_dispose__wrapper() {
        auto _this = BitmapDrawContext__pop();
        BitmapDrawContext_dispose(_this);
    }

    void __constantsFunc() {
        AffineTransform__push(AffineTransform::identity, false);
    }

    int __register() {
        auto m = ni_registerModule("Drawing");
        ni_registerModuleConstants(m, &__constantsFunc);
        ni_registerModuleMethod(m, "Color_dispose", &Color_dispose__wrapper);
        ni_registerModuleMethod(m, "ColorSpace_dispose", &ColorSpace_dispose__wrapper);
        ni_registerModuleMethod(m, "Gradient_dispose", &Gradient_dispose__wrapper);
        ni_registerModuleMethod(m, "Path_getCurrentPoint", &Path_getCurrentPoint__wrapper);
        ni_registerModuleMethod(m, "Path_createCopy", &Path_createCopy__wrapper);
        ni_registerModuleMethod(m, "Path_createMutableCopy", &Path_createMutableCopy__wrapper);
        ni_registerModuleMethod(m, "Path_dispose", &Path_dispose__wrapper);
        ni_registerModuleMethod(m, "MutablePath_addPath", &MutablePath_addPath__wrapper);
        ni_registerModuleMethod(m, "MutablePath_addRect", &MutablePath_addRect__wrapper);
        ni_registerModuleMethod(m, "MutablePath_addRects", &MutablePath_addRects__wrapper);
        ni_registerModuleMethod(m, "MutablePath_addRoundedRect", &MutablePath_addRoundedRect__wrapper);
        ni_registerModuleMethod(m, "MutablePath_addEllipseInRect", &MutablePath_addEllipseInRect__wrapper);
        ni_registerModuleMethod(m, "MutablePath_moveToPoint", &MutablePath_moveToPoint__wrapper);
        ni_registerModuleMethod(m, "MutablePath_addArc", &MutablePath_addArc__wrapper);
        ni_registerModuleMethod(m, "MutablePath_addRelativeArc", &MutablePath_addRelativeArc__wrapper);
        ni_registerModuleMethod(m, "MutablePath_addArcToPoint", &MutablePath_addArcToPoint__wrapper);
        ni_registerModuleMethod(m, "MutablePath_addCurveToPoint", &MutablePath_addCurveToPoint__wrapper);
        ni_registerModuleMethod(m, "MutablePath_addLines", &MutablePath_addLines__wrapper);
        ni_registerModuleMethod(m, "MutablePath_addLineToPoint", &MutablePath_addLineToPoint__wrapper);
        ni_registerModuleMethod(m, "MutablePath_addQuadCurveToPoint", &MutablePath_addQuadCurveToPoint__wrapper);
        ni_registerModuleMethod(m, "MutablePath_closeSubpath", &MutablePath_closeSubpath__wrapper);
        ni_registerModuleMethod(m, "MutablePath_dispose", &MutablePath_dispose__wrapper);
        ni_registerModuleMethod(m, "DrawContext_saveGState", &DrawContext_saveGState__wrapper);
        ni_registerModuleMethod(m, "DrawContext_restoreGState", &DrawContext_restoreGState__wrapper);
        ni_registerModuleMethod(m, "DrawContext_setRGBFillColor", &DrawContext_setRGBFillColor__wrapper);
        ni_registerModuleMethod(m, "DrawContext_setRGBStrokeColor", &DrawContext_setRGBStrokeColor__wrapper);
        ni_registerModuleMethod(m, "DrawContext_setFillColorWithColor", &DrawContext_setFillColorWithColor__wrapper);
        ni_registerModuleMethod(m, "DrawContext_fillRect", &DrawContext_fillRect__wrapper);
        ni_registerModuleMethod(m, "DrawContext_setTextMatrix", &DrawContext_setTextMatrix__wrapper);
        ni_registerModuleMethod(m, "DrawContext_setTextPosition", &DrawContext_setTextPosition__wrapper);
        ni_registerModuleMethod(m, "DrawContext_beginPath", &DrawContext_beginPath__wrapper);
        ni_registerModuleMethod(m, "DrawContext_addArc", &DrawContext_addArc__wrapper);
        ni_registerModuleMethod(m, "DrawContext_addArcToPoint", &DrawContext_addArcToPoint__wrapper);
        ni_registerModuleMethod(m, "DrawContext_drawPath", &DrawContext_drawPath__wrapper);
        ni_registerModuleMethod(m, "DrawContext_setStrokeColorWithColor", &DrawContext_setStrokeColorWithColor__wrapper);
        ni_registerModuleMethod(m, "DrawContext_strokeRectWithWidth", &DrawContext_strokeRectWithWidth__wrapper);
        ni_registerModuleMethod(m, "DrawContext_moveToPoint", &DrawContext_moveToPoint__wrapper);
        ni_registerModuleMethod(m, "DrawContext_addLineToPoint", &DrawContext_addLineToPoint__wrapper);
        ni_registerModuleMethod(m, "DrawContext_strokePath", &DrawContext_strokePath__wrapper);
        ni_registerModuleMethod(m, "DrawContext_setLineDash", &DrawContext_setLineDash__wrapper);
        ni_registerModuleMethod(m, "DrawContext_clearLineDash", &DrawContext_clearLineDash__wrapper);
        ni_registerModuleMethod(m, "DrawContext_setLineWidth", &DrawContext_setLineWidth__wrapper);
        ni_registerModuleMethod(m, "DrawContext_clip", &DrawContext_clip__wrapper);
        ni_registerModuleMethod(m, "DrawContext_clipToRect", &DrawContext_clipToRect__wrapper);
        ni_registerModuleMethod(m, "DrawContext_translateCTM", &DrawContext_translateCTM__wrapper);
        ni_registerModuleMethod(m, "DrawContext_scaleCTM", &DrawContext_scaleCTM__wrapper);
        ni_registerModuleMethod(m, "DrawContext_rotateCTM", &DrawContext_rotateCTM__wrapper);
        ni_registerModuleMethod(m, "DrawContext_concatCTM", &DrawContext_concatCTM__wrapper);
        ni_registerModuleMethod(m, "DrawContext_addPath", &DrawContext_addPath__wrapper);
        ni_registerModuleMethod(m, "DrawContext_fillPath", &DrawContext_fillPath__wrapper);
        ni_registerModuleMethod(m, "DrawContext_strokeRect", &DrawContext_strokeRect__wrapper);
        ni_registerModuleMethod(m, "DrawContext_addRect", &DrawContext_addRect__wrapper);
        ni_registerModuleMethod(m, "DrawContext_closePath", &DrawContext_closePath__wrapper);
        ni_registerModuleMethod(m, "DrawContext_drawLinearGradient", &DrawContext_drawLinearGradient__wrapper);
        ni_registerModuleMethod(m, "DrawContext_setTextDrawingMode", &DrawContext_setTextDrawingMode__wrapper);
        ni_registerModuleMethod(m, "DrawContext_clipToMask", &DrawContext_clipToMask__wrapper);
        ni_registerModuleMethod(m, "DrawContext_drawImage", &DrawContext_drawImage__wrapper);
        ni_registerModuleMethod(m, "DrawContext_dispose", &DrawContext_dispose__wrapper);
        ni_registerModuleMethod(m, "BitmapLock_dispose", &BitmapLock_dispose__wrapper);
        ni_registerModuleMethod(m, "Image_dispose", &Image_dispose__wrapper);
        ni_registerModuleMethod(m, "BitmapDrawContext_createImage", &BitmapDrawContext_createImage__wrapper);
        ni_registerModuleMethod(m, "BitmapDrawContext_getData", &BitmapDrawContext_getData__wrapper);
        ni_registerModuleMethod(m, "BitmapDrawContext_dispose", &BitmapDrawContext_dispose__wrapper);
        ni_registerModuleMethod(m, "AffineTransform.translate", &AffineTransform__::translate__wrapper);
        ni_registerModuleMethod(m, "AffineTransform.rotate", &AffineTransform__::rotate__wrapper);
        ni_registerModuleMethod(m, "AffineTransform.scale", &AffineTransform__::scale__wrapper);
        ni_registerModuleMethod(m, "AffineTransform.concat", &AffineTransform__::concat__wrapper);
        ni_registerModuleMethod(m, "AffineBatchOps.process", &AffineBatchOps::process__wrapper);
        ni_registerModuleMethod(m, "Color.createGenericRGB", &Color::createGenericRGB__wrapper);
        ni_registerModuleMethod(m, "Color.getConstantColor", &Color::getConstantColor__wrapper);
        ni_registerModuleMethod(m, "ColorSpace.createWithName", &ColorSpace::createWithName__wrapper);
        ni_registerModuleMethod(m, "ColorSpace.createDeviceGray", &ColorSpace::createDeviceGray__wrapper);
        ni_registerModuleMethod(m, "Gradient.createWithColorComponents", &Gradient::createWithColorComponents__wrapper);
        ni_registerModuleMethod(m, "Path.createWithRect", &Path::createWithRect__wrapper);
        ni_registerModuleMethod(m, "Path.createWithEllipseInRect", &Path::createWithEllipseInRect__wrapper);
        ni_registerModuleMethod(m, "Path.createWithRoundedRect", &Path::createWithRoundedRect__wrapper);
        ni_registerModuleMethod(m, "MutablePath.create", &MutablePath::create__wrapper);
        MutablePath::transformException = ni_registerException(m, "MutablePath.TransformException", &MutablePath::TransformException__buildAndThrow);
        ni_registerModuleMethod(m, "BitmapDrawContext.create", &BitmapDrawContext::create__wrapper);
        return 0; // = OK
    }
}
