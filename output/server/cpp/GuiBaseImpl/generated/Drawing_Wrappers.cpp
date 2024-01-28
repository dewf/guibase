#include "../support/NativeImplServer.h"
#include "Drawing_wrappers.h"
#include "Drawing.h"


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

void AttributedStringOptions__push(AttributedStringOptions value, bool isReturn) {
    Color strokeColor;
    if (value.hasStrokeColor(&strokeColor)) {
        Color__push(strokeColor);
    }
    double strokeWidth;
    if (value.hasStrokeWidth(&strokeWidth)) {
        ni_pushDouble(strokeWidth);
    }
    Font font;
    if (value.hasFont(&font)) {
        Font__push(font);
    }
    bool foregroundColorFromContext;
    if (value.hasForegroundColorFromContext(&foregroundColorFromContext)) {
        ni_pushBool(foregroundColorFromContext);
    }
    Color foregroundColor;
    if (value.hasForegroundColor(&foregroundColor)) {
        Color__push(foregroundColor);
    }
    ni_pushInt32(value.getUsedFields());
}

AttributedStringOptions AttributedStringOptions__pop() {
    AttributedStringOptions value = {};
    value._usedFields =  ni_popInt32();
    if (value._usedFields & AttributedStringOptions::Fields::ForegroundColorField) {
        auto x = Color__pop();
        value.setForegroundColor(x);
    }
    if (value._usedFields & AttributedStringOptions::Fields::ForegroundColorFromContextField) {
        auto x = ni_popBool();
        value.setForegroundColorFromContext(x);
    }
    if (value._usedFields & AttributedStringOptions::Fields::FontField) {
        auto x = Font__pop();
        value.setFont(x);
    }
    if (value._usedFields & AttributedStringOptions::Fields::StrokeWidthField) {
        auto x = ni_popDouble();
        value.setStrokeWidth(x);
    }
    if (value._usedFields & AttributedStringOptions::Fields::StrokeColorField) {
        auto x = Color__pop();
        value.setStrokeColor(x);
    }
    return value;
}

void AttributedString__push(AttributedString value) {
    ni_pushPtr(value);
}

AttributedString AttributedString__pop() {
    return (AttributedString)ni_popPtr();
}

inline void ColorConstants__push(ColorConstants value) {
    ni_pushInt32((int32_t)value);
}

inline ColorConstants ColorConstants__pop() {
    auto tag = ni_popInt32();
    return (ColorConstants)tag;
}

void Color__push(Color value) {
    ni_pushPtr(value);
}

Color Color__pop() {
    return (Color)ni_popPtr();
}

inline void ColorSpaceName__push(ColorSpaceName value) {
    ni_pushInt32((int32_t)value);
}

inline ColorSpaceName ColorSpaceName__pop() {
    auto tag = ni_popInt32();
    return (ColorSpaceName)tag;
}

void ColorSpace__push(ColorSpace value) {
    ni_pushPtr(value);
}

ColorSpace ColorSpace__pop() {
    return (ColorSpace)ni_popPtr();
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

inline void PathDrawingMode__push(PathDrawingMode value) {
    ni_pushInt32((int32_t)value);
}

inline PathDrawingMode PathDrawingMode__pop() {
    auto tag = ni_popInt32();
    return (PathDrawingMode)tag;
}

// built-in array type: std::vector<double>

inline void GradientDrawingOptions__push(uint32_t value) {
    ni_pushUInt32(value);
}

inline uint32_t GradientDrawingOptions__pop() {
    return ni_popUInt32();
}

void DrawContext__push(DrawContext value) {
    ni_pushPtr(value);
}

DrawContext DrawContext__pop() {
    return (DrawContext)ni_popPtr();
}

void FontTraits__push(FontTraits value, bool isReturn) {
    bool vertical;
    if (value.hasVertical(&vertical)) {
        ni_pushBool(vertical);
    }
    bool monospace;
    if (value.hasMonospace(&monospace)) {
        ni_pushBool(monospace);
    }
    bool condensed;
    if (value.hasCondensed(&condensed)) {
        ni_pushBool(condensed);
    }
    bool expanded;
    if (value.hasExpanded(&expanded)) {
        ni_pushBool(expanded);
    }
    bool bold;
    if (value.hasBold(&bold)) {
        ni_pushBool(bold);
    }
    bool italic;
    if (value.hasItalic(&italic)) {
        ni_pushBool(italic);
    }
    ni_pushInt32(value.getUsedFields());
}

FontTraits FontTraits__pop() {
    FontTraits value = {};
    value._usedFields =  ni_popInt32();
    if (value._usedFields & FontTraits::Fields::ItalicField) {
        auto x = ni_popBool();
        value.setItalic(x);
    }
    if (value._usedFields & FontTraits::Fields::BoldField) {
        auto x = ni_popBool();
        value.setBold(x);
    }
    if (value._usedFields & FontTraits::Fields::ExpandedField) {
        auto x = ni_popBool();
        value.setExpanded(x);
    }
    if (value._usedFields & FontTraits::Fields::CondensedField) {
        auto x = ni_popBool();
        value.setCondensed(x);
    }
    if (value._usedFields & FontTraits::Fields::MonospaceField) {
        auto x = ni_popBool();
        value.setMonospace(x);
    }
    if (value._usedFields & FontTraits::Fields::VerticalField) {
        auto x = ni_popBool();
        value.setVertical(x);
    }
    return value;
}

void OptArgs__push(OptArgs value, bool isReturn) {
    AffineTransform transform;
    if (value.hasTransform(&transform)) {
        AffineTransform__push(transform, isReturn);
    }
    ni_pushInt32(value.getUsedFields());
}

OptArgs OptArgs__pop() {
    OptArgs value = {};
    value._usedFields =  ni_popInt32();
    if (value._usedFields & OptArgs::Fields::TransformField) {
        auto x = AffineTransform__pop();
        value.setTransform(x);
    }
    return value;
}

void Font__push(Font value) {
    ni_pushPtr(value);
}

Font Font__pop() {
    return (Font)ni_popPtr();
}

void __Line_Array__push(std::vector<Line> items, bool isReturn) {
    ni_pushPtrArray((void**)items.data(), items.size());
}

std::vector<Line> __Line_Array__pop() {
    Line *values;
    size_t count;
    ni_popPtrArray((void***)&values, &count);
    return std::vector<Line>(values, values + count);
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

void Range__push(Range value, bool isReturn) {
    ni_pushInt64(value.length);
    ni_pushInt64(value.location);
}

Range Range__pop() {
    auto location = ni_popInt64();
    auto length = ni_popInt64();
    return Range { location, length };
}

void Frame__push(Frame value) {
    ni_pushPtr(value);
}

Frame Frame__pop() {
    return (Frame)ni_popPtr();
}

void FrameSetter__push(FrameSetter value) {
    ni_pushPtr(value);
}

FrameSetter FrameSetter__pop() {
    return (FrameSetter)ni_popPtr();
}

void GradientStop__push(GradientStop value, bool isReturn) {
    ni_pushDouble(value.alpha);
    ni_pushDouble(value.blue);
    ni_pushDouble(value.green);
    ni_pushDouble(value.red);
    ni_pushDouble(value.location);
}

GradientStop GradientStop__pop() {
    auto location = ni_popDouble();
    auto red = ni_popDouble();
    auto green = ni_popDouble();
    auto blue = ni_popDouble();
    auto alpha = ni_popDouble();
    return GradientStop { location, red, green, blue, alpha };
}

void __GradientStop_Array__push(std::vector<GradientStop> values, bool isReturn) {
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

std::vector<GradientStop> __GradientStop_Array__pop() {
    auto location_values = popDoubleArrayInternal();
    auto red_values = popDoubleArrayInternal();
    auto green_values = popDoubleArrayInternal();
    auto blue_values = popDoubleArrayInternal();
    auto alpha_values = popDoubleArrayInternal();
    std::vector<GradientStop> __ret;
    for (auto i = 0; i < location_values.size(); i++) {
        GradientStop __value;
        __value.location = location_values[i];
        __value.red = red_values[i];
        __value.green = green_values[i];
        __value.blue = blue_values[i];
        __value.alpha = alpha_values[i];
        __ret.push_back(__value);
    }
    return __ret;
}

void Gradient__push(Gradient value) {
    ni_pushPtr(value);
}

Gradient Gradient__pop() {
    return (Gradient)ni_popPtr();
}

void TypographicBounds__push(TypographicBounds value, bool isReturn) {
    ni_pushDouble(value.leading);
    ni_pushDouble(value.descent);
    ni_pushDouble(value.ascent);
    ni_pushDouble(value.width);
}

TypographicBounds TypographicBounds__pop() {
    auto width = ni_popDouble();
    auto ascent = ni_popDouble();
    auto descent = ni_popDouble();
    auto leading = ni_popDouble();
    return TypographicBounds { width, ascent, descent, leading };
}

inline void LineBoundsOptions__push(uint32_t value) {
    ni_pushUInt32(value);
}

inline uint32_t LineBoundsOptions__pop() {
    return ni_popUInt32();
}

void __Run_Array__push(std::vector<Run> items, bool isReturn) {
    ni_pushPtrArray((void**)items.data(), items.size());
}

std::vector<Run> __Run_Array__pop() {
    Run *values;
    size_t count;
    ni_popPtrArray((void***)&values, &count);
    return std::vector<Run>(values, values + count);
}

void __DoubleDouble_Tuple__push(std::tuple<double,double> value, bool isReturn) {
    ni_pushDouble(std::get<1>(value));
    ni_pushDouble(std::get<0>(value));
}

std::tuple<double,double> __DoubleDouble_Tuple__pop() {
    auto _0 = ni_popDouble();
    auto _1 = ni_popDouble();
    return std::tuple<double,double>{ _0, _1 };
}

void Line__push(Line value) {
    ni_pushPtr(value);
}

Line Line__pop() {
    return (Line)ni_popPtr();
}

void MutableAttributedString__push(MutableAttributedString value) {
    ni_pushPtr(value);
}

MutableAttributedString MutableAttributedString__pop() {
    return (MutableAttributedString)ni_popPtr();
}

void Path__push(Path value) {
    ni_pushPtr(value);
}

Path Path__pop() {
    return (Path)ni_popPtr();
}

// built-in array type: std::vector<std::string>

// built-in array type: std::vector<int64_t>

void __String_Int64_Map__push(std::map<std::string,int64_t> _map, bool isReturn) {
    std::vector<std::string> keys;
    std::vector<int64_t> values;
    for (auto i = _map.begin(); i != _map.end(); i++) {
        keys.push_back(i->first);
        values.push_back(i->second);
    }
    pushInt64ArrayInternal(values);
    pushStringArrayInternal(keys);
}

std::map<std::string,int64_t> __String_Int64_Map__pop() {
    std::map<std::string,int64_t> __ret;
    auto keys = popStringArrayInternal();
    auto values = popInt64ArrayInternal();
    for (auto i = 0; i < keys.size(); i++) {
        __ret[keys[i]] = values[i];
    }
    return __ret;
}

inline void RunStatus__push(uint32_t value) {
    ni_pushUInt32(value);
}

inline uint32_t RunStatus__pop() {
    return ni_popUInt32();
}

void Run__push(Run value) {
    ni_pushPtr(value);
}

Run Run__pop() {
    return (Run)ni_popPtr();
}

void Color_createGenericRGB__wrapper() {
    auto red = ni_popDouble();
    auto green = ni_popDouble();
    auto blue = ni_popDouble();
    auto alpha = ni_popDouble();
    Color__push(Color_createGenericRGB(red, green, blue, alpha));
}

void Color_getConstantColor__wrapper() {
    auto which = ColorConstants__pop();
    Color__push(Color_getConstantColor(which));
}

void Color_dispose__wrapper() {
    auto _this = Color__pop();
    Color_dispose(_this);
}

void ColorSpace_createWithName__wrapper() {
    auto name = ColorSpaceName__pop();
    ColorSpace__push(ColorSpace_createWithName(name));
}

void ColorSpace_createDeviceGray__wrapper() {
    ColorSpace__push(ColorSpace_createDeviceGray());
}

void ColorSpace_dispose__wrapper() {
    auto _this = ColorSpace__pop();
    ColorSpace_dispose(_this);
}

void Gradient_createWithColorComponents__wrapper() {
    auto space = ColorSpace__pop();
    auto stops = __GradientStop_Array__pop();
    Gradient__push(Gradient_createWithColorComponents(space, stops));
}

void Gradient_dispose__wrapper() {
    auto _this = Gradient__pop();
    Gradient_dispose(_this);
}

void Path_createWithRect__wrapper() {
    auto rect = Rect__pop();
    auto optArgs = OptArgs__pop();
    Path__push(Path_createWithRect(rect, optArgs));
}

void Path_createWithEllipseInRect__wrapper() {
    auto rect = Rect__pop();
    auto optArgs = OptArgs__pop();
    Path__push(Path_createWithEllipseInRect(rect, optArgs));
}

void Path_createWithRoundedRect__wrapper() {
    auto rect = Rect__pop();
    auto cornerWidth = ni_popDouble();
    auto cornerHeight = ni_popDouble();
    auto optArgs = OptArgs__pop();
    Path__push(Path_createWithRoundedRect(rect, cornerWidth, cornerHeight, optArgs));
}

void Path_dispose__wrapper() {
    auto _this = Path__pop();
    Path_dispose(_this);
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
    auto mode = PathDrawingMode__pop();
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
    auto drawOpts = GradientDrawingOptions__pop();
    DrawContext_drawLinearGradient(_this, gradient, startPoint, endPoint, drawOpts);
}

void DrawContext_dispose__wrapper() {
    auto _this = DrawContext__pop();
    DrawContext_dispose(_this);
}

void AttributedString_create__wrapper() {
    auto s = popStringInternal();
    auto opts = AttributedStringOptions__pop();
    AttributedString__push(AttributedString_create(s, opts));
}

void AttributedString_dispose__wrapper() {
    auto _this = AttributedString__pop();
    AttributedString_dispose(_this);
}

void MutableAttributedString_getLength__wrapper() {
    auto _this = MutableAttributedString__pop();
    ni_pushInt64(MutableAttributedString_getLength(_this));
}

void MutableAttributedString_replaceString__wrapper() {
    auto _this = MutableAttributedString__pop();
    auto range = Range__pop();
    auto str = popStringInternal();
    MutableAttributedString_replaceString(_this, range, str);
}

void MutableAttributedString_beginEditing__wrapper() {
    auto _this = MutableAttributedString__pop();
    MutableAttributedString_beginEditing(_this);
}

void MutableAttributedString_endEditing__wrapper() {
    auto _this = MutableAttributedString__pop();
    MutableAttributedString_endEditing(_this);
}

void MutableAttributedString_setAttribute__wrapper() {
    auto _this = MutableAttributedString__pop();
    auto range = Range__pop();
    auto attr = AttributedStringOptions__pop();
    MutableAttributedString_setAttribute(_this, range, attr);
}

void MutableAttributedString_setCustomAttribute__wrapper() {
    auto _this = MutableAttributedString__pop();
    auto range = Range__pop();
    auto key = popStringInternal();
    auto value = ni_popInt64();
    MutableAttributedString_setCustomAttribute(_this, range, key, value);
}

void MutableAttributedString_getNormalAttributedString_REMOVEME__wrapper() {
    auto _this = MutableAttributedString__pop();
    AttributedString__push(MutableAttributedString_getNormalAttributedString_REMOVEME(_this));
}

void MutableAttributedString_create__wrapper() {
    auto maxLength = ni_popInt64();
    MutableAttributedString__push(MutableAttributedString_create(maxLength));
}

void MutableAttributedString_dispose__wrapper() {
    auto _this = MutableAttributedString__pop();
    MutableAttributedString_dispose(_this);
}

void Font_createCopyWithSymbolicTraits__wrapper() {
    auto _this = Font__pop();
    auto size = ni_popDouble();
    auto newTraits = FontTraits__pop();
    auto optArgs = OptArgs__pop();
    Font__push(Font_createCopyWithSymbolicTraits(_this, size, newTraits, optArgs));
}

void Font_getAscent__wrapper() {
    auto _this = Font__pop();
    ni_pushDouble(Font_getAscent(_this));
}

void Font_getDescent__wrapper() {
    auto _this = Font__pop();
    ni_pushDouble(Font_getDescent(_this));
}

void Font_getUnderlineThickness__wrapper() {
    auto _this = Font__pop();
    ni_pushDouble(Font_getUnderlineThickness(_this));
}

void Font_getUnderlinePosition__wrapper() {
    auto _this = Font__pop();
    ni_pushDouble(Font_getUnderlinePosition(_this));
}

void Font_createFromFile__wrapper() {
    auto path = popStringInternal();
    auto size = ni_popDouble();
    auto optArgs = OptArgs__pop();
    Font__push(Font_createFromFile(path, size, optArgs));
}

void Font_createWithName__wrapper() {
    auto name = popStringInternal();
    auto size = ni_popDouble();
    auto optArgs = OptArgs__pop();
    Font__push(Font_createWithName(name, size, optArgs));
}

void Font_dispose__wrapper() {
    auto _this = Font__pop();
    Font_dispose(_this);
}

void Run_getAttributes__wrapper() {
    auto _this = Run__pop();
    AttributedStringOptions__push(Run_getAttributes(_this), true);
}

void Run_getCustomAttributes__wrapper() {
    auto _this = Run__pop();
    auto keys = popStringArrayInternal();
    __String_Int64_Map__push(Run_getCustomAttributes(_this, keys), true);
}

void Run_getTypographicBounds__wrapper() {
    auto _this = Run__pop();
    auto range = Range__pop();
    TypographicBounds__push(Run_getTypographicBounds(_this, range), true);
}

void Run_getStringRange__wrapper() {
    auto _this = Run__pop();
    Range__push(Run_getStringRange(_this), true);
}

void Run_getStatus__wrapper() {
    auto _this = Run__pop();
    RunStatus__push(Run_getStatus(_this));
}

void Run_dispose__wrapper() {
    auto _this = Run__pop();
    Run_dispose(_this);
}

void Line_getTypographicBounds__wrapper() {
    auto _this = Line__pop();
    TypographicBounds__push(Line_getTypographicBounds(_this), true);
}

void Line_getBoundsWithOptions__wrapper() {
    auto _this = Line__pop();
    auto opts = LineBoundsOptions__pop();
    Rect__push(Line_getBoundsWithOptions(_this, opts), true);
}

void Line_draw__wrapper() {
    auto _this = Line__pop();
    auto context = DrawContext__pop();
    Line_draw(_this, context);
}

void Line_getGlyphRuns__wrapper() {
    auto _this = Line__pop();
    __Run_Array__push(Line_getGlyphRuns(_this), true);
}

void Line_getLineOffsetForStringIndex__wrapper() {
    auto _this = Line__pop();
    auto charIndex = ni_popInt64();
    __DoubleDouble_Tuple__push(Line_getLineOffsetForStringIndex(_this, charIndex), true);
}

void Line_createWithAttributedString__wrapper() {
    auto str = AttributedString__pop();
    Line__push(Line_createWithAttributedString(str));
}

void Line_dispose__wrapper() {
    auto _this = Line__pop();
    Line_dispose(_this);
}

void Frame_draw__wrapper() {
    auto _this = Frame__pop();
    auto context = DrawContext__pop();
    Frame_draw(_this, context);
}

void Frame_getLines__wrapper() {
    auto _this = Frame__pop();
    __Line_Array__push(Frame_getLines(_this), true);
}

void Frame_getLineOrigins__wrapper() {
    auto _this = Frame__pop();
    auto range = Range__pop();
    __Point_Array__push(Frame_getLineOrigins(_this, range), true);
}

void Frame_dispose__wrapper() {
    auto _this = Frame__pop();
    Frame_dispose(_this);
}

void FrameSetter_createWithAttributedString__wrapper() {
    auto str = AttributedString__pop();
    FrameSetter__push(FrameSetter_createWithAttributedString(str));
}

void FrameSetter_createFrame__wrapper() {
    auto _this = FrameSetter__pop();
    auto range = Range__pop();
    auto path = Path__pop();
    Frame__push(FrameSetter_createFrame(_this, range, path));
}

void FrameSetter_dispose__wrapper() {
    auto _this = FrameSetter__pop();
    FrameSetter_dispose(_this);
}

void __constantsFunc() {
    AffineTransform__push(AffineTransformIdentity, false);
}

int Drawing__register() {
    auto m = ni_registerModule("Drawing");
    ni_registerModuleConstants(m, &__constantsFunc);
    ni_registerModuleMethod(m, "Color_createGenericRGB", &Color_createGenericRGB__wrapper);
    ni_registerModuleMethod(m, "Color_getConstantColor", &Color_getConstantColor__wrapper);
    ni_registerModuleMethod(m, "Color_dispose", &Color_dispose__wrapper);
    ni_registerModuleMethod(m, "ColorSpace_createWithName", &ColorSpace_createWithName__wrapper);
    ni_registerModuleMethod(m, "ColorSpace_createDeviceGray", &ColorSpace_createDeviceGray__wrapper);
    ni_registerModuleMethod(m, "ColorSpace_dispose", &ColorSpace_dispose__wrapper);
    ni_registerModuleMethod(m, "Gradient_createWithColorComponents", &Gradient_createWithColorComponents__wrapper);
    ni_registerModuleMethod(m, "Gradient_dispose", &Gradient_dispose__wrapper);
    ni_registerModuleMethod(m, "Path_createWithRect", &Path_createWithRect__wrapper);
    ni_registerModuleMethod(m, "Path_createWithEllipseInRect", &Path_createWithEllipseInRect__wrapper);
    ni_registerModuleMethod(m, "Path_createWithRoundedRect", &Path_createWithRoundedRect__wrapper);
    ni_registerModuleMethod(m, "Path_dispose", &Path_dispose__wrapper);
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
    ni_registerModuleMethod(m, "DrawContext_dispose", &DrawContext_dispose__wrapper);
    ni_registerModuleMethod(m, "AttributedString_create", &AttributedString_create__wrapper);
    ni_registerModuleMethod(m, "AttributedString_dispose", &AttributedString_dispose__wrapper);
    ni_registerModuleMethod(m, "MutableAttributedString_getLength", &MutableAttributedString_getLength__wrapper);
    ni_registerModuleMethod(m, "MutableAttributedString_replaceString", &MutableAttributedString_replaceString__wrapper);
    ni_registerModuleMethod(m, "MutableAttributedString_beginEditing", &MutableAttributedString_beginEditing__wrapper);
    ni_registerModuleMethod(m, "MutableAttributedString_endEditing", &MutableAttributedString_endEditing__wrapper);
    ni_registerModuleMethod(m, "MutableAttributedString_setAttribute", &MutableAttributedString_setAttribute__wrapper);
    ni_registerModuleMethod(m, "MutableAttributedString_setCustomAttribute", &MutableAttributedString_setCustomAttribute__wrapper);
    ni_registerModuleMethod(m, "MutableAttributedString_getNormalAttributedString_REMOVEME", &MutableAttributedString_getNormalAttributedString_REMOVEME__wrapper);
    ni_registerModuleMethod(m, "MutableAttributedString_create", &MutableAttributedString_create__wrapper);
    ni_registerModuleMethod(m, "MutableAttributedString_dispose", &MutableAttributedString_dispose__wrapper);
    ni_registerModuleMethod(m, "Font_createCopyWithSymbolicTraits", &Font_createCopyWithSymbolicTraits__wrapper);
    ni_registerModuleMethod(m, "Font_getAscent", &Font_getAscent__wrapper);
    ni_registerModuleMethod(m, "Font_getDescent", &Font_getDescent__wrapper);
    ni_registerModuleMethod(m, "Font_getUnderlineThickness", &Font_getUnderlineThickness__wrapper);
    ni_registerModuleMethod(m, "Font_getUnderlinePosition", &Font_getUnderlinePosition__wrapper);
    ni_registerModuleMethod(m, "Font_createFromFile", &Font_createFromFile__wrapper);
    ni_registerModuleMethod(m, "Font_createWithName", &Font_createWithName__wrapper);
    ni_registerModuleMethod(m, "Font_dispose", &Font_dispose__wrapper);
    ni_registerModuleMethod(m, "Run_getAttributes", &Run_getAttributes__wrapper);
    ni_registerModuleMethod(m, "Run_getCustomAttributes", &Run_getCustomAttributes__wrapper);
    ni_registerModuleMethod(m, "Run_getTypographicBounds", &Run_getTypographicBounds__wrapper);
    ni_registerModuleMethod(m, "Run_getStringRange", &Run_getStringRange__wrapper);
    ni_registerModuleMethod(m, "Run_getStatus", &Run_getStatus__wrapper);
    ni_registerModuleMethod(m, "Run_dispose", &Run_dispose__wrapper);
    ni_registerModuleMethod(m, "Line_getTypographicBounds", &Line_getTypographicBounds__wrapper);
    ni_registerModuleMethod(m, "Line_getBoundsWithOptions", &Line_getBoundsWithOptions__wrapper);
    ni_registerModuleMethod(m, "Line_draw", &Line_draw__wrapper);
    ni_registerModuleMethod(m, "Line_getGlyphRuns", &Line_getGlyphRuns__wrapper);
    ni_registerModuleMethod(m, "Line_getLineOffsetForStringIndex", &Line_getLineOffsetForStringIndex__wrapper);
    ni_registerModuleMethod(m, "Line_createWithAttributedString", &Line_createWithAttributedString__wrapper);
    ni_registerModuleMethod(m, "Line_dispose", &Line_dispose__wrapper);
    ni_registerModuleMethod(m, "Frame_draw", &Frame_draw__wrapper);
    ni_registerModuleMethod(m, "Frame_getLines", &Frame_getLines__wrapper);
    ni_registerModuleMethod(m, "Frame_getLineOrigins", &Frame_getLineOrigins__wrapper);
    ni_registerModuleMethod(m, "Frame_dispose", &Frame_dispose__wrapper);
    ni_registerModuleMethod(m, "FrameSetter_createWithAttributedString", &FrameSetter_createWithAttributedString__wrapper);
    ni_registerModuleMethod(m, "FrameSetter_createFrame", &FrameSetter_createFrame__wrapper);
    ni_registerModuleMethod(m, "FrameSetter_dispose", &FrameSetter_dispose__wrapper);
    return 0; // = OK
}
