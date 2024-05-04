#include "../support/NativeImplServer.h"
#include "Text_wrappers.h"
#include "Text.h"

#include "Drawing_wrappers.h"
using namespace Drawing;

namespace Text
{
    void __ParagraphStyle_Setting_Array__push(std::vector<std::shared_ptr<ParagraphStyle::Setting::Base>> values, bool isReturn) {
        for (auto v = values.rbegin(); v != values.rend(); v++) {
            ParagraphStyle::Setting__push(*v, isReturn);
        }
        ni_pushSizeT(values.size());
    }

    std::vector<std::shared_ptr<ParagraphStyle::Setting::Base>> __ParagraphStyle_Setting_Array__pop() {
        std::vector<std::shared_ptr<ParagraphStyle::Setting::Base>> __ret;
        auto count = ni_popSizeT();
        for (auto i = 0; i < count; i++) {
            auto value = ParagraphStyle::Setting__pop();
            __ret.push_back(value);
        }
        return __ret;
    }
    // built-in array type: std::vector<std::string>
    // built-in array type: std::vector<double>
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
    inline void __Run_Status_Array__push(std::vector<uint32_t> values, bool isReturn) {
        pushUInt32ArrayInternal(values);
    }
    inline std::vector<uint32_t> __Run_Status_Array__pop() {
        return popUInt32ArrayInternal();
    }
    // built-in array type: std::vector<int64_t>
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
    void __AttributedString_Options_Array__push(std::vector<AttributedString::Options> values, bool isReturn) {
        for (auto v = values.rbegin(); v != values.rend(); v++) {
            AttributedString::Options__push(*v, isReturn);
        }
        ni_pushSizeT(values.size());
    }

    std::vector<AttributedString::Options> __AttributedString_Options_Array__pop() {
        std::vector<AttributedString::Options> __ret;
        auto count = ni_popSizeT();
        for (auto i = 0; i < count; i++) {
            auto value = AttributedString::Options__pop();
            __ret.push_back(value);
        }
        return __ret;
    }
    void __Run_Info_Array__push(std::vector<Run::Info> values, bool isReturn) {
        std::vector<TypographicBounds> typoBounds_values;
        std::vector<Rect> bounds_values;
        std::vector<uint32_t> status_values;
        std::vector<Range> sourceRange_values;
        std::vector<AttributedString::Options> attrs_values;
        for (auto v = values.begin(); v != values.end(); v++) {
            typoBounds_values.push_back(v->typoBounds);
            bounds_values.push_back(v->bounds);
            status_values.push_back(v->status);
            sourceRange_values.push_back(v->sourceRange);
            attrs_values.push_back(v->attrs);
        }
        __TypographicBounds_Array__push(typoBounds_values, isReturn);
        __Rect_Array__push(bounds_values, isReturn);
        __Run_Status_Array__push(status_values, isReturn);
        __Range_Array__push(sourceRange_values, isReturn);
        __AttributedString_Options_Array__push(attrs_values, isReturn);
    }

    std::vector<Run::Info> __Run_Info_Array__pop() {
        auto attrs_values = __AttributedString_Options_Array__pop();
        auto sourceRange_values = __Range_Array__pop();
        auto status_values = __Run_Status_Array__pop();
        auto bounds_values = __Rect_Array__pop();
        auto typoBounds_values = __TypographicBounds_Array__pop();
        std::vector<Run::Info> __ret;
        for (auto i = 0; i < attrs_values.size(); i++) {
            Run::Info __value;
            __value.attrs = attrs_values[i];
            __value.sourceRange = sourceRange_values[i];
            __value.status = status_values[i];
            __value.bounds = bounds_values[i];
            __value.typoBounds = typoBounds_values[i];
            __ret.push_back(__value);
        }
        return __ret;
    }
    void __Run_Info_Array_Array__push(std::vector<std::vector<Run::Info>> values, bool isReturn) {
        for (auto v = values.rbegin(); v != values.rend(); v++) {
            __Run_Info_Array__push(*v, isReturn);
        }
        ni_pushSizeT(values.size());
    }

    std::vector<std::vector<Run::Info>> __Run_Info_Array_Array__pop() {
        std::vector<std::vector<Run::Info>> __ret;
        auto count = ni_popSizeT();
        for (auto i = 0; i < count; i++) {
            auto value = __Run_Info_Array__pop();
            __ret.push_back(value);
        }
        return __ret;
    }
    void __Line_Info_Array__push(std::vector<Line::Info> values, bool isReturn) {
        std::vector<std::vector<Run::Info>> runs_values;
        std::vector<TypographicBounds> lineTypoBounds_values;
        std::vector<Point> origin_values;
        for (auto v = values.begin(); v != values.end(); v++) {
            runs_values.push_back(v->runs);
            lineTypoBounds_values.push_back(v->lineTypoBounds);
            origin_values.push_back(v->origin);
        }
        __Run_Info_Array_Array__push(runs_values, isReturn);
        __TypographicBounds_Array__push(lineTypoBounds_values, isReturn);
        __Point_Array__push(origin_values, isReturn);
    }

    std::vector<Line::Info> __Line_Info_Array__pop() {
        auto origin_values = __Point_Array__pop();
        auto lineTypoBounds_values = __TypographicBounds_Array__pop();
        auto runs_values = __Run_Info_Array_Array__pop();
        std::vector<Line::Info> __ret;
        for (auto i = 0; i < origin_values.size(); i++) {
            Line::Info __value;
            __value.origin = origin_values[i];
            __value.lineTypoBounds = lineTypoBounds_values[i];
            __value.runs = runs_values[i];
            __ret.push_back(__value);
        }
        return __ret;
    }
    void __Line_Array__push(std::vector<LineRef> items, bool isReturn) {
        ni_pushPtrArray((void**)items.data(), items.size());
    }

    std::vector<LineRef> __Line_Array__pop() {
        LineRef *values;
        size_t count;
        ni_popPtrArray((void***)&values, &count);
        return std::vector<LineRef>(values, values + count);
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
    void __Run_Array__push(std::vector<RunRef> items, bool isReturn) {
        ni_pushPtrArray((void**)items.data(), items.size());
    }

    std::vector<RunRef> __Run_Array__pop() {
        RunRef *values;
        size_t count;
        ni_popPtrArray((void***)&values, &count);
        return std::vector<RunRef>(values, values + count);
    }

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
    void Range__push(Range value, bool isReturn) {
        ni_pushInt64(value.length);
        ni_pushInt64(value.location);
    }

    Range Range__pop() {
        auto location = ni_popInt64();
        auto length = ni_popInt64();
        return Range { location, length };
    }
    void AttributedString__push(AttributedStringRef value) {
        ni_pushPtr(value);
    }

    AttributedStringRef AttributedString__pop() {
        return (AttributedStringRef)ni_popPtr();
    }
    namespace AttributedString {
        void Options__push(Options value, bool isReturn) {
            std::map<std::string,int64_t> custom;
            if (value.hasCustom(&custom)) {
                __String_Int64_Map__push(custom, isReturn);
            }
            ParagraphStyleRef paragraphStyle;
            if (value.hasParagraphStyle(&paragraphStyle)) {
                ParagraphStyle__push(paragraphStyle);
            }
            ColorRef strokeColor;
            if (value.hasStrokeColor(&strokeColor)) {
                Color__push(strokeColor);
            }
            double strokeWidth;
            if (value.hasStrokeWidth(&strokeWidth)) {
                ni_pushDouble(strokeWidth);
            }
            FontRef font;
            if (value.hasFont(&font)) {
                Font__push(font);
            }
            bool foregroundColorFromContext;
            if (value.hasForegroundColorFromContext(&foregroundColorFromContext)) {
                ni_pushBool(foregroundColorFromContext);
            }
            ColorRef foregroundColor;
            if (value.hasForegroundColor(&foregroundColor)) {
                Color__push(foregroundColor);
            }
            ni_pushInt32(value.getUsedFields());
        }

        Options Options__pop() {
            Options value = {};
            value._usedFields =  ni_popInt32();
            if (value._usedFields & Options::Fields::ForegroundColorField) {
                auto x = Color__pop();
                value.setForegroundColor(x);
            }
            if (value._usedFields & Options::Fields::ForegroundColorFromContextField) {
                auto x = ni_popBool();
                value.setForegroundColorFromContext(x);
            }
            if (value._usedFields & Options::Fields::FontField) {
                auto x = Font__pop();
                value.setFont(x);
            }
            if (value._usedFields & Options::Fields::StrokeWidthField) {
                auto x = ni_popDouble();
                value.setStrokeWidth(x);
            }
            if (value._usedFields & Options::Fields::StrokeColorField) {
                auto x = Color__pop();
                value.setStrokeColor(x);
            }
            if (value._usedFields & Options::Fields::ParagraphStyleField) {
                auto x = ParagraphStyle__pop();
                value.setParagraphStyle(x);
            }
            if (value._usedFields & Options::Fields::CustomField) {
                auto x = __String_Int64_Map__pop();
                value.setCustom(x);
            }
            return value;
        }

        void create__wrapper() {
            auto s = popStringInternal();
            auto opts = Options__pop();
            AttributedString__push(create(s, opts));
        }
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
    void MutableAttributedString__push(MutableAttributedStringRef value) {
        ni_pushPtr(value);
    }

    MutableAttributedStringRef MutableAttributedString__pop() {
        return (MutableAttributedStringRef)ni_popPtr();
    }
    namespace MutableAttributedString {

        void create__wrapper() {
            auto maxLength = ni_popInt64();
            MutableAttributedString__push(create(maxLength));
        }
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
        auto attr = AttributedString::Options__pop();
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
    void Font__push(FontRef value) {
        ni_pushPtr(value);
    }

    FontRef Font__pop() {
        return (FontRef)ni_popPtr();
    }
    namespace Font {
        void Traits__push(Traits value, bool isReturn) {
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

        Traits Traits__pop() {
            Traits value = {};
            value._usedFields =  ni_popInt32();
            if (value._usedFields & Traits::Fields::ItalicField) {
                auto x = ni_popBool();
                value.setItalic(x);
            }
            if (value._usedFields & Traits::Fields::BoldField) {
                auto x = ni_popBool();
                value.setBold(x);
            }
            if (value._usedFields & Traits::Fields::ExpandedField) {
                auto x = ni_popBool();
                value.setExpanded(x);
            }
            if (value._usedFields & Traits::Fields::CondensedField) {
                auto x = ni_popBool();
                value.setCondensed(x);
            }
            if (value._usedFields & Traits::Fields::MonospaceField) {
                auto x = ni_popBool();
                value.setMonospace(x);
            }
            if (value._usedFields & Traits::Fields::VerticalField) {
                auto x = ni_popBool();
                value.setVertical(x);
            }
            return value;
        }

        void createFromFile__wrapper() {
            auto path = popStringInternal();
            auto size = ni_popDouble();
            auto transform = __AffineTransform_Option__pop();
            Font__push(createFromFile(path, size, transform));
        }

        void createWithName__wrapper() {
            auto name = popStringInternal();
            auto size = ni_popDouble();
            auto transform = __AffineTransform_Option__pop();
            Font__push(createWithName(name, size, transform));
        }
    }

    void Font_createCopyWithSymbolicTraits__wrapper() {
        auto _this = Font__pop();
        auto size = ni_popDouble();
        auto transform = __AffineTransform_Option__pop();
        auto newTraits = Font::Traits__pop();
        Font__push(Font_createCopyWithSymbolicTraits(_this, size, transform, newTraits));
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
    void LineBoundsOptions__push(uint32_t value) {
        ni_pushUInt32(value);
    }

    uint32_t LineBoundsOptions__pop() {
        return ni_popUInt32();
    }
    void Run__push(RunRef value) {
        ni_pushPtr(value);
    }

    RunRef Run__pop() {
        return (RunRef)ni_popPtr();
    }
    namespace Run {
        void Status__push(uint32_t value) {
            ni_pushUInt32(value);
        }

        uint32_t Status__pop() {
            return ni_popUInt32();
        }
        void Info__push(Info value, bool isReturn) {
            TypographicBounds__push(value.typoBounds, isReturn);
            Rect__push(value.bounds, isReturn);
            Status__push(value.status);
            Range__push(value.sourceRange, isReturn);
            AttributedString::Options__push(value.attrs, isReturn);
        }

        Info Info__pop() {
            auto attrs = AttributedString::Options__pop();
            auto sourceRange = Range__pop();
            auto status = Status__pop();
            auto bounds = Rect__pop();
            auto typoBounds = TypographicBounds__pop();
            return Info { attrs, sourceRange, status, bounds, typoBounds };
        }
    }

    void Run_getAttributes__wrapper() {
        auto _this = Run__pop();
        auto customKeys = popStringArrayInternal();
        AttributedString::Options__push(Run_getAttributes(_this, customKeys), true);
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
        Run::Status__push(Run_getStatus(_this));
    }

    void Run_dispose__wrapper() {
        auto _this = Run__pop();
        Run_dispose(_this);
    }
    void Line__push(LineRef value) {
        ni_pushPtr(value);
    }

    LineRef Line__pop() {
        return (LineRef)ni_popPtr();
    }
    namespace Line {
        void Info__push(Info value, bool isReturn) {
            __Run_Info_Array__push(value.runs, isReturn);
            TypographicBounds__push(value.lineTypoBounds, isReturn);
            Point__push(value.origin, isReturn);
        }

        Info Info__pop() {
            auto origin = Point__pop();
            auto lineTypoBounds = TypographicBounds__pop();
            auto runs = __Run_Info_Array__pop();
            return Info { origin, lineTypoBounds, runs };
        }

        void createWithAttributedString__wrapper() {
            auto str = AttributedString__pop();
            Line__push(createWithAttributedString(str));
        }
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
    void Frame__push(FrameRef value) {
        ni_pushPtr(value);
    }

    FrameRef Frame__pop() {
        return (FrameRef)ni_popPtr();
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
        __Line_Info_Array__push(Frame_getLinesExtended(_this, customKeys), true);
    }

    void Frame_dispose__wrapper() {
        auto _this = Frame__pop();
        Frame_dispose(_this);
    }
    void FrameSetter__push(FrameSetterRef value) {
        ni_pushPtr(value);
    }

    FrameSetterRef FrameSetter__pop() {
        return (FrameSetterRef)ni_popPtr();
    }
    namespace FrameSetter {

        void createWithAttributedString__wrapper() {
            auto str = AttributedString__pop();
            FrameSetter__push(createWithAttributedString(str));
        }
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
    void ParagraphStyle__push(ParagraphStyleRef value) {
        ni_pushPtr(value);
    }

    ParagraphStyleRef ParagraphStyle__pop() {
        return (ParagraphStyleRef)ni_popPtr();
    }
    namespace ParagraphStyle {
        void TextAlignment__push(TextAlignment value) {
            ni_pushInt32((int32_t)value);
        }

        TextAlignment TextAlignment__pop() {
            auto tag = ni_popInt32();
            return (TextAlignment)tag;
        }

        class Setting_PushVisitor : public Setting::Visitor {
        private:
            bool isReturn;
        public:
            Setting_PushVisitor(bool isReturn) : isReturn(isReturn) {}
            void onAlignment(const Setting::Alignment* alignment) override {
                TextAlignment__push(alignment->value);
                // kind:
                ni_pushInt32(0);
            }
        };

        void Setting__push(std::shared_ptr<Setting::Base> value, bool isReturn) {
            Setting_PushVisitor v(isReturn);
            value->accept((Setting::Visitor*)&v);
        }

        std::shared_ptr<Setting::Base> Setting__pop() {
            Setting::Base* __ret = nullptr;
            switch (ni_popInt32()) {
            case 0: {
                auto value = TextAlignment__pop();
                __ret = new Setting::Alignment(value);
                break;
            }
            default:
                printf("C++ Setting__pop() - unknown kind! returning null\n");
            }
            return std::shared_ptr<Setting::Base>(__ret);
        }

        void create__wrapper() {
            auto settings = __ParagraphStyle_Setting_Array__pop();
            ParagraphStyle__push(create(settings));
        }
    }

    void ParagraphStyle_dispose__wrapper() {
        auto _this = ParagraphStyle__pop();
        ParagraphStyle_dispose(_this);
    }

    int __register() {
        auto m = ni_registerModule("Text");
        ni_registerModuleMethod(m, "AttributedString_getLength", &AttributedString_getLength__wrapper);
        ni_registerModuleMethod(m, "AttributedString_createMutableCopy", &AttributedString_createMutableCopy__wrapper);
        ni_registerModuleMethod(m, "AttributedString_dispose", &AttributedString_dispose__wrapper);
        ni_registerModuleMethod(m, "MutableAttributedString_replaceString", &MutableAttributedString_replaceString__wrapper);
        ni_registerModuleMethod(m, "MutableAttributedString_setAttribute", &MutableAttributedString_setAttribute__wrapper);
        ni_registerModuleMethod(m, "MutableAttributedString_setCustomAttribute", &MutableAttributedString_setCustomAttribute__wrapper);
        ni_registerModuleMethod(m, "MutableAttributedString_beginEditing", &MutableAttributedString_beginEditing__wrapper);
        ni_registerModuleMethod(m, "MutableAttributedString_endEditing", &MutableAttributedString_endEditing__wrapper);
        ni_registerModuleMethod(m, "MutableAttributedString_dispose", &MutableAttributedString_dispose__wrapper);
        ni_registerModuleMethod(m, "Font_createCopyWithSymbolicTraits", &Font_createCopyWithSymbolicTraits__wrapper);
        ni_registerModuleMethod(m, "Font_getAscent", &Font_getAscent__wrapper);
        ni_registerModuleMethod(m, "Font_getDescent", &Font_getDescent__wrapper);
        ni_registerModuleMethod(m, "Font_getUnderlineThickness", &Font_getUnderlineThickness__wrapper);
        ni_registerModuleMethod(m, "Font_getUnderlinePosition", &Font_getUnderlinePosition__wrapper);
        ni_registerModuleMethod(m, "Font_dispose", &Font_dispose__wrapper);
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
        ni_registerModuleMethod(m, "Frame_draw", &Frame_draw__wrapper);
        ni_registerModuleMethod(m, "Frame_getLines", &Frame_getLines__wrapper);
        ni_registerModuleMethod(m, "Frame_getLineOrigins", &Frame_getLineOrigins__wrapper);
        ni_registerModuleMethod(m, "Frame_getLinesExtended", &Frame_getLinesExtended__wrapper);
        ni_registerModuleMethod(m, "Frame_dispose", &Frame_dispose__wrapper);
        ni_registerModuleMethod(m, "FrameSetter_createFrame", &FrameSetter_createFrame__wrapper);
        ni_registerModuleMethod(m, "FrameSetter_dispose", &FrameSetter_dispose__wrapper);
        ni_registerModuleMethod(m, "ParagraphStyle_dispose", &ParagraphStyle_dispose__wrapper);
        ni_registerModuleMethod(m, "AttributedString.create", &AttributedString::create__wrapper);
        ni_registerModuleMethod(m, "MutableAttributedString.create", &MutableAttributedString::create__wrapper);
        ni_registerModuleMethod(m, "Font.createFromFile", &Font::createFromFile__wrapper);
        ni_registerModuleMethod(m, "Font.createWithName", &Font::createWithName__wrapper);
        ni_registerModuleMethod(m, "Line.createWithAttributedString", &Line::createWithAttributedString__wrapper);
        ni_registerModuleMethod(m, "FrameSetter.createWithAttributedString", &FrameSetter::createWithAttributedString__wrapper);
        ni_registerModuleMethod(m, "ParagraphStyle.create", &ParagraphStyle::create__wrapper);
        return 0; // = OK
    }
}
