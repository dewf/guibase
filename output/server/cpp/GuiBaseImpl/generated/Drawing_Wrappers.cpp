#include "../support/NativeImplServer.h"
#include "Drawing_wrappers.h"
#include "Drawing.h"

ni_ExceptionRef mutablePathTransformException;

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

void AffineTransformOps__push(AffineTransformOps value, bool isReturn) {
    switch (value.tag) {
    case AffineTransformOps::Tag::Translate:
        ni_pushDouble(value.translate->ty);
        ni_pushDouble(value.translate->tx);
        break;
    case AffineTransformOps::Tag::Rotate:
        ni_pushDouble(value.rotate->angle);
        break;
    case AffineTransformOps::Tag::Scale:
        ni_pushDouble(value.scale->sy);
        ni_pushDouble(value.scale->sx);
        break;
    case AffineTransformOps::Tag::Concat:
        AffineTransform__push(value.concat->t2, isReturn);
        break;
    }
    ni_pushInt32((int32_t)value.tag);
}

AffineTransformOps AffineTransformOps__pop() {
    auto which = ni_popInt32();
    switch ((AffineTransformOps::Tag)which) {
    case AffineTransformOps::Tag::Translate: {
        auto tx = ni_popDouble();
        auto ty = ni_popDouble();
        return AffineTransformOps::Translate::make(tx, ty); }
    case AffineTransformOps::Tag::Rotate: {
        auto angle = ni_popDouble();
        return AffineTransformOps::Rotate::make(angle); }
    case AffineTransformOps::Tag::Scale: {
        auto sx = ni_popDouble();
        auto sy = ni_popDouble();
        return AffineTransformOps::Scale::make(sx, sy); }
    case AffineTransformOps::Tag::Concat: {
        auto t2 = AffineTransform__pop();
        return AffineTransformOps::Concat::make(t2); }
    default:
        throw "AffineTransformOps__pop(): unknown tag!";
    }
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

void AttributedStringOptions__push(AttributedStringOptions value, bool isReturn) {
    std::map<std::string,int64_t> custom;
    if (value.hasCustom(&custom)) {
        __String_Int64_Map__push(custom, isReturn);
    }
    ParagraphStyle paragraphStyle;
    if (value.hasParagraphStyle(&paragraphStyle)) {
        ParagraphStyle__push(paragraphStyle);
    }
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
    if (value._usedFields & AttributedStringOptions::Fields::ParagraphStyleField) {
        auto x = ParagraphStyle__pop();
        value.setParagraphStyle(x);
    }
    if (value._usedFields & AttributedStringOptions::Fields::CustomField) {
        auto x = __String_Int64_Map__pop();
        value.setCustom(x);
    }
    return value;
}

void AttributedString__push(AttributedString value) {
    ni_pushPtr(value);
}

AttributedString AttributedString__pop() {
    return (AttributedString)ni_popPtr();
}

inline void BitmapInfo__push(uint32_t value) {
    ni_pushUInt32(value);
}

inline uint32_t BitmapInfo__pop() {
    return ni_popUInt32();
}

void BitmapDrawContext__push(BitmapDrawContext value) {
    ni_pushPtr(value);
}

BitmapDrawContext BitmapDrawContext__pop() {
    return (BitmapDrawContext)ni_popPtr();
}

void BitmapLock__push(BitmapLock value) {
    ni_pushPtr(value);
}

BitmapLock BitmapLock__pop() {
    return (BitmapLock)ni_popPtr();
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

inline void TextDrawingMode__push(TextDrawingMode value) {
    ni_pushInt32((int32_t)value);
}

inline TextDrawingMode TextDrawingMode__pop() {
    auto tag = ni_popInt32();
    return (TextDrawingMode)tag;
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

void __TypographicBounds_Array__push(std::vector<TypographicBounds> values, bool isReturn) {
    std::vector<double> leading_values;
    std::vector<double> descent_values;
    std::vector<double> ascent_values;
    std::vector<double> width_values;
    for (auto v = values.begin(); v != values.end(); v++) {
        leading_values.push_back(v->leading);
        descent_values.push_back(v->descent);
        ascent_values.push_back(v->ascent);
        width_values.push_back(v->width);
    }
    pushDoubleArrayInternal(leading_values);
    pushDoubleArrayInternal(descent_values);
    pushDoubleArrayInternal(ascent_values);
    pushDoubleArrayInternal(width_values);
}

std::vector<TypographicBounds> __TypographicBounds_Array__pop() {
    auto width_values = popDoubleArrayInternal();
    auto ascent_values = popDoubleArrayInternal();
    auto descent_values = popDoubleArrayInternal();
    auto leading_values = popDoubleArrayInternal();
    std::vector<TypographicBounds> __ret;
    for (auto i = 0; i < width_values.size(); i++) {
        TypographicBounds __value;
        __value.width = width_values[i];
        __value.ascent = ascent_values[i];
        __value.descent = descent_values[i];
        __value.leading = leading_values[i];
        __ret.push_back(__value);
    }
    return __ret;
}

void __AttributedStringOptions_Array__push(std::vector<AttributedStringOptions> values, bool isReturn) {
    for (auto v = values.rbegin(); v != values.rend(); v++) {
        AttributedStringOptions__push(*v, isReturn);
    }
    ni_pushSizeT(values.size());
}

std::vector<AttributedStringOptions> __AttributedStringOptions_Array__pop() {
    std::vector<AttributedStringOptions> __ret;
    auto count = ni_popSizeT();
    for (auto i = 0; i < count; i++) {
        auto value = AttributedStringOptions__pop();
        __ret.push_back(value);
    }
    return __ret;
}

void __Range_Array__push(std::vector<Range> values, bool isReturn) {
    std::vector<int64_t> length_values;
    std::vector<int64_t> location_values;
    for (auto v = values.begin(); v != values.end(); v++) {
        length_values.push_back(v->length);
        location_values.push_back(v->location);
    }
    pushInt64ArrayInternal(length_values);
    pushInt64ArrayInternal(location_values);
}

std::vector<Range> __Range_Array__pop() {
    auto location_values = popInt64ArrayInternal();
    auto length_values = popInt64ArrayInternal();
    std::vector<Range> __ret;
    for (auto i = 0; i < location_values.size(); i++) {
        Range __value;
        __value.location = location_values[i];
        __value.length = length_values[i];
        __ret.push_back(__value);
    }
    return __ret;
}

inline void RunStatus__push(uint32_t value) {
    ni_pushUInt32(value);
}

inline uint32_t RunStatus__pop() {
    return ni_popUInt32();
}

inline void __RunStatus_Array__push(std::vector<uint32_t> values, bool isReturn) {
    pushUInt32ArrayInternal(values);
}
inline std::vector<uint32_t> __RunStatus_Array__pop() {
    return popUInt32ArrayInternal();
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

void RunInfo__push(RunInfo value, bool isReturn) {
    TypographicBounds__push(value.typoBounds, isReturn);
    Rect__push(value.bounds, isReturn);
    RunStatus__push(value.status);
    Range__push(value.sourceRange, isReturn);
    AttributedStringOptions__push(value.attrs, isReturn);
}

RunInfo RunInfo__pop() {
    auto attrs = AttributedStringOptions__pop();
    auto sourceRange = Range__pop();
    auto status = RunStatus__pop();
    auto bounds = Rect__pop();
    auto typoBounds = TypographicBounds__pop();
    return RunInfo { attrs, sourceRange, status, bounds, typoBounds };
}

void __RunInfo_Array__push(std::vector<RunInfo> values, bool isReturn) {
    std::vector<TypographicBounds> typoBounds_values;
    std::vector<Rect> bounds_values;
    std::vector<uint32_t> status_values;
    std::vector<Range> sourceRange_values;
    std::vector<AttributedStringOptions> attrs_values;
    for (auto v = values.begin(); v != values.end(); v++) {
        typoBounds_values.push_back(v->typoBounds);
        bounds_values.push_back(v->bounds);
        status_values.push_back(v->status);
        sourceRange_values.push_back(v->sourceRange);
        attrs_values.push_back(v->attrs);
    }
    __TypographicBounds_Array__push(typoBounds_values, isReturn);
    __Rect_Array__push(bounds_values, isReturn);
    __RunStatus_Array__push(status_values, isReturn);
    __Range_Array__push(sourceRange_values, isReturn);
    __AttributedStringOptions_Array__push(attrs_values, isReturn);
}

std::vector<RunInfo> __RunInfo_Array__pop() {
    auto attrs_values = __AttributedStringOptions_Array__pop();
    auto sourceRange_values = __Range_Array__pop();
    auto status_values = __RunStatus_Array__pop();
    auto bounds_values = __Rect_Array__pop();
    auto typoBounds_values = __TypographicBounds_Array__pop();
    std::vector<RunInfo> __ret;
    for (auto i = 0; i < attrs_values.size(); i++) {
        RunInfo __value;
        __value.attrs = attrs_values[i];
        __value.sourceRange = sourceRange_values[i];
        __value.status = status_values[i];
        __value.bounds = bounds_values[i];
        __value.typoBounds = typoBounds_values[i];
        __ret.push_back(__value);
    }
    return __ret;
}

void __RunInfo_Array_Array__push(std::vector<std::vector<RunInfo>> values, bool isReturn) {
    for (auto v = values.rbegin(); v != values.rend(); v++) {
        __RunInfo_Array__push(*v, isReturn);
    }
    ni_pushSizeT(values.size());
}

std::vector<std::vector<RunInfo>> __RunInfo_Array_Array__pop() {
    std::vector<std::vector<RunInfo>> __ret;
    auto count = ni_popSizeT();
    for (auto i = 0; i < count; i++) {
        auto value = __RunInfo_Array__pop();
        __ret.push_back(value);
    }
    return __ret;
}

void LineInfo__push(LineInfo value, bool isReturn) {
    __RunInfo_Array__push(value.runs, isReturn);
    TypographicBounds__push(value.lineTypoBounds, isReturn);
    Point__push(value.origin, isReturn);
}

LineInfo LineInfo__pop() {
    auto origin = Point__pop();
    auto lineTypoBounds = TypographicBounds__pop();
    auto runs = __RunInfo_Array__pop();
    return LineInfo { origin, lineTypoBounds, runs };
}

void __LineInfo_Array__push(std::vector<LineInfo> values, bool isReturn) {
    std::vector<std::vector<RunInfo>> runs_values;
    std::vector<TypographicBounds> lineTypoBounds_values;
    std::vector<Point> origin_values;
    for (auto v = values.begin(); v != values.end(); v++) {
        runs_values.push_back(v->runs);
        lineTypoBounds_values.push_back(v->lineTypoBounds);
        origin_values.push_back(v->origin);
    }
    __RunInfo_Array_Array__push(runs_values, isReturn);
    __TypographicBounds_Array__push(lineTypoBounds_values, isReturn);
    __Point_Array__push(origin_values, isReturn);
}

std::vector<LineInfo> __LineInfo_Array__pop() {
    auto origin_values = __Point_Array__pop();
    auto lineTypoBounds_values = __TypographicBounds_Array__pop();
    auto runs_values = __RunInfo_Array_Array__pop();
    std::vector<LineInfo> __ret;
    for (auto i = 0; i < origin_values.size(); i++) {
        LineInfo __value;
        __value.origin = origin_values[i];
        __value.lineTypoBounds = lineTypoBounds_values[i];
        __value.runs = runs_values[i];
        __ret.push_back(__value);
    }
    return __ret;
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

void Image__push(Image value) {
    ni_pushPtr(value);
}

Image Image__pop() {
    return (Image)ni_popPtr();
}

inline void ImageAlphaInfo__push(ImageAlphaInfo value) {
    ni_pushInt32((int32_t)value);
}

inline ImageAlphaInfo ImageAlphaInfo__pop() {
    auto tag = ni_popInt32();
    return (ImageAlphaInfo)tag;
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


void MutablePathTransformException__push(MutablePathTransformException e) {
    pushStringInternal(e.error);
}

void MutablePathTransformException__buildAndThrow() {
    auto error = popStringInternal();
    throw MutablePathTransformException(error);
}

void MutablePath__push(MutablePath value) {
    ni_pushPtr(value);
}

MutablePath MutablePath__pop() {
    return (MutablePath)ni_popPtr();
}

inline void TextAlignment__push(TextAlignment value) {
    ni_pushInt32((int32_t)value);
}

inline TextAlignment TextAlignment__pop() {
    auto tag = ni_popInt32();
    return (TextAlignment)tag;
}

void ParagraphStyleSetting__push(ParagraphStyleSetting value, bool isReturn) {
    switch (value.tag) {
    case ParagraphStyleSetting::Tag::alignment:
        TextAlignment__push(value.alignment->value);
        break;
    }
    ni_pushInt32((int32_t)value.tag);
}

ParagraphStyleSetting ParagraphStyleSetting__pop() {
    auto which = ni_popInt32();
    switch ((ParagraphStyleSetting::Tag)which) {
    case ParagraphStyleSetting::Tag::alignment: {
        auto value = TextAlignment__pop();
        return ParagraphStyleSetting::alignment::make(value); }
    default:
        throw "ParagraphStyleSetting__pop(): unknown tag!";
    }
}

void __ParagraphStyleSetting_Array__push(std::vector<ParagraphStyleSetting> values, bool isReturn) {
    for (auto v = values.rbegin(); v != values.rend(); v++) {
        ParagraphStyleSetting__push(*v, isReturn);
    }
    ni_pushSizeT(values.size());
}

std::vector<ParagraphStyleSetting> __ParagraphStyleSetting_Array__pop() {
    std::vector<ParagraphStyleSetting> __ret;
    auto count = ni_popSizeT();
    for (auto i = 0; i < count; i++) {
        auto value = ParagraphStyleSetting__pop();
        __ret.push_back(value);
    }
    return __ret;
}

void ParagraphStyle__push(ParagraphStyle value) {
    ni_pushPtr(value);
}

ParagraphStyle ParagraphStyle__pop() {
    return (ParagraphStyle)ni_popPtr();
}

void Path__push(Path value) {
    ni_pushPtr(value);
}

Path Path__pop() {
    return (Path)ni_popPtr();
}

void Run__push(Run value) {
    ni_pushPtr(value);
}

Run Run__pop() {
    return (Run)ni_popPtr();
}

void __AffineTransformOps_Array__push(std::vector<AffineTransformOps> values, bool isReturn) {
    for (auto v = values.rbegin(); v != values.rend(); v++) {
        AffineTransformOps__push(*v, isReturn);
    }
    ni_pushSizeT(values.size());
}

std::vector<AffineTransformOps> __AffineTransformOps_Array__pop() {
    std::vector<AffineTransformOps> __ret;
    auto count = ni_popSizeT();
    for (auto i = 0; i < count; i++) {
        auto value = AffineTransformOps__pop();
        __ret.push_back(value);
    }
    return __ret;
}

void AffineTransformTranslate__wrapper() {
    auto input = AffineTransform__pop();
    auto tx = ni_popDouble();
    auto ty = ni_popDouble();
    AffineTransform__push(AffineTransformTranslate(input, tx, ty), true);
}

void AffineTransformRotate__wrapper() {
    auto input = AffineTransform__pop();
    auto angle = ni_popDouble();
    AffineTransform__push(AffineTransformRotate(input, angle), true);
}

void AffineTransformScale__wrapper() {
    auto input = AffineTransform__pop();
    auto sx = ni_popDouble();
    auto sy = ni_popDouble();
    AffineTransform__push(AffineTransformScale(input, sx, sy), true);
}

void AffineTransformConcat__wrapper() {
    auto t1 = AffineTransform__pop();
    auto t2 = AffineTransform__pop();
    AffineTransform__push(AffineTransformConcat(t1, t2), true);
}

void AffineTransformModify__wrapper() {
    auto input = AffineTransform__pop();
    auto ops = __AffineTransformOps_Array__pop();
    AffineTransform__push(AffineTransformModify(input, ops), true);
}

void Color_dispose__wrapper() {
    auto _this = Color__pop();
    Color_dispose(_this);
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

void ColorSpace_dispose__wrapper() {
    auto _this = ColorSpace__pop();
    ColorSpace_dispose(_this);
}

void ColorSpace_createWithName__wrapper() {
    auto name = ColorSpaceName__pop();
    ColorSpace__push(ColorSpace_createWithName(name));
}

void ColorSpace_createDeviceGray__wrapper() {
    ColorSpace__push(ColorSpace_createDeviceGray());
}

void Gradient_dispose__wrapper() {
    auto _this = Gradient__pop();
    Gradient_dispose(_this);
}

void Gradient_createWithColorComponents__wrapper() {
    auto space = ColorSpace__pop();
    auto stops = __GradientStop_Array__pop();
    Gradient__push(Gradient_createWithColorComponents(space, stops));
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

void MutablePath_addPath__wrapper() {
    auto _this = MutablePath__pop();
    auto path2 = Path__pop();
    auto optArgs = OptArgs__pop();
    MutablePath_addPath(_this, path2, optArgs);
}

void MutablePath_addRect__wrapper() {
    auto _this = MutablePath__pop();
    auto rect = Rect__pop();
    auto optArgs = OptArgs__pop();
    MutablePath_addRect(_this, rect, optArgs);
}

void MutablePath_addRects__wrapper() {
    auto _this = MutablePath__pop();
    auto rects = __Rect_Array__pop();
    auto optArgs = OptArgs__pop();
    MutablePath_addRects(_this, rects, optArgs);
}

void MutablePath_addRoundedRect__wrapper() {
    auto _this = MutablePath__pop();
    auto rect = Rect__pop();
    auto cornerWidth = ni_popDouble();
    auto cornerHeight = ni_popDouble();
    auto optArgs = OptArgs__pop();
    MutablePath_addRoundedRect(_this, rect, cornerWidth, cornerHeight, optArgs);
}

void MutablePath_addEllipseInRect__wrapper() {
    auto _this = MutablePath__pop();
    auto rect = Rect__pop();
    auto optArgs = OptArgs__pop();
    MutablePath_addEllipseInRect(_this, rect, optArgs);
}

void MutablePath_moveToPoint__wrapper() {
    auto _this = MutablePath__pop();
    auto x = ni_popDouble();
    auto y = ni_popDouble();
    auto optArgs = OptArgs__pop();
    try {
        MutablePath_moveToPoint(_this, x, y, optArgs);
    }
    catch (const MutablePathTransformException& e) {
        ni_setException(mutablePathTransformException);
        MutablePathTransformException__push(e);
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
    auto optArgs = OptArgs__pop();
    try {
        MutablePath_addArc(_this, x, y, radius, startAngle, endAngle, clockwise, optArgs);
    }
    catch (const MutablePathTransformException& e) {
        ni_setException(mutablePathTransformException);
        MutablePathTransformException__push(e);
    }
}

void MutablePath_addRelativeArc__wrapper() {
    auto _this = MutablePath__pop();
    auto x = ni_popDouble();
    auto y = ni_popDouble();
    auto radius = ni_popDouble();
    auto startAngle = ni_popDouble();
    auto delta = ni_popDouble();
    auto optArgs = OptArgs__pop();
    try {
        MutablePath_addRelativeArc(_this, x, y, radius, startAngle, delta, optArgs);
    }
    catch (const MutablePathTransformException& e) {
        ni_setException(mutablePathTransformException);
        MutablePathTransformException__push(e);
    }
}

void MutablePath_addArcToPoint__wrapper() {
    auto _this = MutablePath__pop();
    auto x1 = ni_popDouble();
    auto y1 = ni_popDouble();
    auto x2 = ni_popDouble();
    auto y2 = ni_popDouble();
    auto radius = ni_popDouble();
    auto optArgs = OptArgs__pop();
    try {
        MutablePath_addArcToPoint(_this, x1, y1, x2, y2, radius, optArgs);
    }
    catch (const MutablePathTransformException& e) {
        ni_setException(mutablePathTransformException);
        MutablePathTransformException__push(e);
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
    auto optArgs = OptArgs__pop();
    try {
        MutablePath_addCurveToPoint(_this, cp1x, cp1y, cp2x, cp2y, x, y, optArgs);
    }
    catch (const MutablePathTransformException& e) {
        ni_setException(mutablePathTransformException);
        MutablePathTransformException__push(e);
    }
}

void MutablePath_addLines__wrapper() {
    auto _this = MutablePath__pop();
    auto points = __Point_Array__pop();
    auto optArgs = OptArgs__pop();
    try {
        MutablePath_addLines(_this, points, optArgs);
    }
    catch (const MutablePathTransformException& e) {
        ni_setException(mutablePathTransformException);
        MutablePathTransformException__push(e);
    }
}

void MutablePath_addLineToPoint__wrapper() {
    auto _this = MutablePath__pop();
    auto x = ni_popDouble();
    auto y = ni_popDouble();
    auto optArgs = OptArgs__pop();
    try {
        MutablePath_addLineToPoint(_this, x, y, optArgs);
    }
    catch (const MutablePathTransformException& e) {
        ni_setException(mutablePathTransformException);
        MutablePathTransformException__push(e);
    }
}

void MutablePath_addQuadCurveToPoint__wrapper() {
    auto _this = MutablePath__pop();
    auto cpx = ni_popDouble();
    auto cpy = ni_popDouble();
    auto x = ni_popDouble();
    auto y = ni_popDouble();
    auto optArgs = OptArgs__pop();
    try {
        MutablePath_addQuadCurveToPoint(_this, cpx, cpy, x, y, optArgs);
    }
    catch (const MutablePathTransformException& e) {
        ni_setException(mutablePathTransformException);
        MutablePathTransformException__push(e);
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

void MutablePath_create__wrapper() {
    MutablePath__push(MutablePath_create());
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

void AttributedString_getLength__wrapper() {
    auto _this = AttributedString__pop();
    ni_pushInt64(AttributedString_getLength(_this));
}

void AttributedString_createMutableCopy__wrapper() {
    auto _this = AttributedString__pop();
    auto maxLength = ni_popInt64();
    MutableAttributedString__push(AttributedString_createMutableCopy(_this, maxLength));
}

void AttributedString_dispose__wrapper() {
    auto _this = AttributedString__pop();
    AttributedString_dispose(_this);
}

void AttributedString_create__wrapper() {
    auto s = popStringInternal();
    auto opts = AttributedStringOptions__pop();
    AttributedString__push(AttributedString_create(s, opts));
}

void MutableAttributedString_replaceString__wrapper() {
    auto _this = MutableAttributedString__pop();
    auto range = Range__pop();
    auto str = popStringInternal();
    MutableAttributedString_replaceString(_this, range, str);
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

void MutableAttributedString_beginEditing__wrapper() {
    auto _this = MutableAttributedString__pop();
    MutableAttributedString_beginEditing(_this);
}

void MutableAttributedString_endEditing__wrapper() {
    auto _this = MutableAttributedString__pop();
    MutableAttributedString_endEditing(_this);
}

void MutableAttributedString_dispose__wrapper() {
    auto _this = MutableAttributedString__pop();
    MutableAttributedString_dispose(_this);
}

void MutableAttributedString_create__wrapper() {
    auto maxLength = ni_popInt64();
    MutableAttributedString__push(MutableAttributedString_create(maxLength));
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

void Font_dispose__wrapper() {
    auto _this = Font__pop();
    Font_dispose(_this);
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

void Run_getAttributes__wrapper() {
    auto _this = Run__pop();
    auto customKeys = popStringArrayInternal();
    AttributedStringOptions__push(Run_getAttributes(_this, customKeys), true);
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

void Line_getStringRange__wrapper() {
    auto _this = Line__pop();
    Range__push(Line_getStringRange(_this), true);
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

void Line_getOffsetForStringIndex__wrapper() {
    auto _this = Line__pop();
    auto charIndex = ni_popInt64();
    __DoubleDouble_Tuple__push(Line_getOffsetForStringIndex(_this, charIndex), true);
}

void Line_getStringIndexForPosition__wrapper() {
    auto _this = Line__pop();
    auto p = Point__pop();
    ni_pushInt64(Line_getStringIndexForPosition(_this, p));
}

void Line_dispose__wrapper() {
    auto _this = Line__pop();
    Line_dispose(_this);
}

void Line_createWithAttributedString__wrapper() {
    auto str = AttributedString__pop();
    Line__push(Line_createWithAttributedString(str));
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

void Frame_getLinesExtended__wrapper() {
    auto _this = Frame__pop();
    auto customKeys = popStringArrayInternal();
    __LineInfo_Array__push(Frame_getLinesExtended(_this, customKeys), true);
}

void Frame_dispose__wrapper() {
    auto _this = Frame__pop();
    Frame_dispose(_this);
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

void FrameSetter_createWithAttributedString__wrapper() {
    auto str = AttributedString__pop();
    FrameSetter__push(FrameSetter_createWithAttributedString(str));
}

void ParagraphStyle_dispose__wrapper() {
    auto _this = ParagraphStyle__pop();
    ParagraphStyle_dispose(_this);
}

void ParagraphStyle_create__wrapper() {
    auto settings = __ParagraphStyleSetting_Array__pop();
    ParagraphStyle__push(ParagraphStyle_create(settings));
}

void BitmapLock_dispose__wrapper() {
    auto _this = BitmapLock__pop();
    BitmapLock_dispose(_this);
}

void Image_dispose__wrapper() {
    auto _this = Image__pop();
    Image_dispose(_this);
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

void BitmapDrawContext_create__wrapper() {
    auto width = ni_popInt32();
    auto height = ni_popInt32();
    auto bitsPerComponent = ni_popInt32();
    auto bytesPerRow = ni_popInt32();
    auto space = ColorSpace__pop();
    auto bitmapInfo = BitmapInfo__pop();
    BitmapDrawContext__push(BitmapDrawContext_create(width, height, bitsPerComponent, bytesPerRow, space, bitmapInfo));
}

void Drawing__constantsFunc() {
    AffineTransform__push(AffineTransformIdentity, false);
}

int Drawing__register() {
    auto m = ni_registerModule("Drawing");
    ni_registerModuleConstants(m, &Drawing__constantsFunc);
    ni_registerModuleMethod(m, "AffineTransformTranslate", &AffineTransformTranslate__wrapper);
    ni_registerModuleMethod(m, "AffineTransformRotate", &AffineTransformRotate__wrapper);
    ni_registerModuleMethod(m, "AffineTransformScale", &AffineTransformScale__wrapper);
    ni_registerModuleMethod(m, "AffineTransformConcat", &AffineTransformConcat__wrapper);
    ni_registerModuleMethod(m, "AffineTransformModify", &AffineTransformModify__wrapper);
    ni_registerModuleMethod(m, "Color_dispose", &Color_dispose__wrapper);
    ni_registerModuleMethod(m, "Color_createGenericRGB", &Color_createGenericRGB__wrapper);
    ni_registerModuleMethod(m, "Color_getConstantColor", &Color_getConstantColor__wrapper);
    ni_registerModuleMethod(m, "ColorSpace_dispose", &ColorSpace_dispose__wrapper);
    ni_registerModuleMethod(m, "ColorSpace_createWithName", &ColorSpace_createWithName__wrapper);
    ni_registerModuleMethod(m, "ColorSpace_createDeviceGray", &ColorSpace_createDeviceGray__wrapper);
    ni_registerModuleMethod(m, "Gradient_dispose", &Gradient_dispose__wrapper);
    ni_registerModuleMethod(m, "Gradient_createWithColorComponents", &Gradient_createWithColorComponents__wrapper);
    ni_registerModuleMethod(m, "Path_getCurrentPoint", &Path_getCurrentPoint__wrapper);
    ni_registerModuleMethod(m, "Path_createCopy", &Path_createCopy__wrapper);
    ni_registerModuleMethod(m, "Path_createMutableCopy", &Path_createMutableCopy__wrapper);
    ni_registerModuleMethod(m, "Path_dispose", &Path_dispose__wrapper);
    ni_registerModuleMethod(m, "Path_createWithRect", &Path_createWithRect__wrapper);
    ni_registerModuleMethod(m, "Path_createWithEllipseInRect", &Path_createWithEllipseInRect__wrapper);
    ni_registerModuleMethod(m, "Path_createWithRoundedRect", &Path_createWithRoundedRect__wrapper);
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
    ni_registerModuleMethod(m, "MutablePath_create", &MutablePath_create__wrapper);
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
    ni_registerModuleMethod(m, "AttributedString_getLength", &AttributedString_getLength__wrapper);
    ni_registerModuleMethod(m, "AttributedString_createMutableCopy", &AttributedString_createMutableCopy__wrapper);
    ni_registerModuleMethod(m, "AttributedString_dispose", &AttributedString_dispose__wrapper);
    ni_registerModuleMethod(m, "AttributedString_create", &AttributedString_create__wrapper);
    ni_registerModuleMethod(m, "MutableAttributedString_replaceString", &MutableAttributedString_replaceString__wrapper);
    ni_registerModuleMethod(m, "MutableAttributedString_setAttribute", &MutableAttributedString_setAttribute__wrapper);
    ni_registerModuleMethod(m, "MutableAttributedString_setCustomAttribute", &MutableAttributedString_setCustomAttribute__wrapper);
    ni_registerModuleMethod(m, "MutableAttributedString_beginEditing", &MutableAttributedString_beginEditing__wrapper);
    ni_registerModuleMethod(m, "MutableAttributedString_endEditing", &MutableAttributedString_endEditing__wrapper);
    ni_registerModuleMethod(m, "MutableAttributedString_dispose", &MutableAttributedString_dispose__wrapper);
    ni_registerModuleMethod(m, "MutableAttributedString_create", &MutableAttributedString_create__wrapper);
    ni_registerModuleMethod(m, "Font_createCopyWithSymbolicTraits", &Font_createCopyWithSymbolicTraits__wrapper);
    ni_registerModuleMethod(m, "Font_getAscent", &Font_getAscent__wrapper);
    ni_registerModuleMethod(m, "Font_getDescent", &Font_getDescent__wrapper);
    ni_registerModuleMethod(m, "Font_getUnderlineThickness", &Font_getUnderlineThickness__wrapper);
    ni_registerModuleMethod(m, "Font_getUnderlinePosition", &Font_getUnderlinePosition__wrapper);
    ni_registerModuleMethod(m, "Font_dispose", &Font_dispose__wrapper);
    ni_registerModuleMethod(m, "Font_createFromFile", &Font_createFromFile__wrapper);
    ni_registerModuleMethod(m, "Font_createWithName", &Font_createWithName__wrapper);
    ni_registerModuleMethod(m, "Run_getAttributes", &Run_getAttributes__wrapper);
    ni_registerModuleMethod(m, "Run_getTypographicBounds", &Run_getTypographicBounds__wrapper);
    ni_registerModuleMethod(m, "Run_getStringRange", &Run_getStringRange__wrapper);
    ni_registerModuleMethod(m, "Run_getStatus", &Run_getStatus__wrapper);
    ni_registerModuleMethod(m, "Run_dispose", &Run_dispose__wrapper);
    ni_registerModuleMethod(m, "Line_getStringRange", &Line_getStringRange__wrapper);
    ni_registerModuleMethod(m, "Line_getTypographicBounds", &Line_getTypographicBounds__wrapper);
    ni_registerModuleMethod(m, "Line_getBoundsWithOptions", &Line_getBoundsWithOptions__wrapper);
    ni_registerModuleMethod(m, "Line_draw", &Line_draw__wrapper);
    ni_registerModuleMethod(m, "Line_getGlyphRuns", &Line_getGlyphRuns__wrapper);
    ni_registerModuleMethod(m, "Line_getOffsetForStringIndex", &Line_getOffsetForStringIndex__wrapper);
    ni_registerModuleMethod(m, "Line_getStringIndexForPosition", &Line_getStringIndexForPosition__wrapper);
    ni_registerModuleMethod(m, "Line_dispose", &Line_dispose__wrapper);
    ni_registerModuleMethod(m, "Line_createWithAttributedString", &Line_createWithAttributedString__wrapper);
    ni_registerModuleMethod(m, "Frame_draw", &Frame_draw__wrapper);
    ni_registerModuleMethod(m, "Frame_getLines", &Frame_getLines__wrapper);
    ni_registerModuleMethod(m, "Frame_getLineOrigins", &Frame_getLineOrigins__wrapper);
    ni_registerModuleMethod(m, "Frame_getLinesExtended", &Frame_getLinesExtended__wrapper);
    ni_registerModuleMethod(m, "Frame_dispose", &Frame_dispose__wrapper);
    ni_registerModuleMethod(m, "FrameSetter_createFrame", &FrameSetter_createFrame__wrapper);
    ni_registerModuleMethod(m, "FrameSetter_dispose", &FrameSetter_dispose__wrapper);
    ni_registerModuleMethod(m, "FrameSetter_createWithAttributedString", &FrameSetter_createWithAttributedString__wrapper);
    ni_registerModuleMethod(m, "ParagraphStyle_dispose", &ParagraphStyle_dispose__wrapper);
    ni_registerModuleMethod(m, "ParagraphStyle_create", &ParagraphStyle_create__wrapper);
    ni_registerModuleMethod(m, "BitmapLock_dispose", &BitmapLock_dispose__wrapper);
    ni_registerModuleMethod(m, "Image_dispose", &Image_dispose__wrapper);
    ni_registerModuleMethod(m, "BitmapDrawContext_createImage", &BitmapDrawContext_createImage__wrapper);
    ni_registerModuleMethod(m, "BitmapDrawContext_getData", &BitmapDrawContext_getData__wrapper);
    ni_registerModuleMethod(m, "BitmapDrawContext_dispose", &BitmapDrawContext_dispose__wrapper);
    ni_registerModuleMethod(m, "BitmapDrawContext_create", &BitmapDrawContext_create__wrapper);
    mutablePathTransformException = ni_registerException(m, "MutablePathTransformException", &MutablePathTransformException__buildAndThrow);
    return 0; // = OK
}
