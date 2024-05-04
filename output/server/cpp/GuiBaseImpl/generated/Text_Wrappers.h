#pragma once
#include "Text.h"

namespace Text
{

    void __DoubleDouble_Tuple__push(std::tuple<double,double> value, bool isReturn);
    std::tuple<double,double> __DoubleDouble_Tuple__pop();

    void __AffineTransform_Option__push(std::optional<AffineTransform> value, bool isReturn);
    std::optional<AffineTransform> __AffineTransform_Option__pop();

    void __String_Int64_Map__push(std::map<std::string,int64_t> _map, bool isReturn);
    std::map<std::string,int64_t> __String_Int64_Map__pop();

    void Range__push(Range value, bool isReturn);
    Range Range__pop();

    void AttributedString__push(AttributedStringRef value);
    AttributedStringRef AttributedString__pop();
    namespace AttributedString {

        void Options__push(Options value, bool isReturn);
        Options Options__pop();

        void create__wrapper();
    }

    void AttributedString_getLength__wrapper();

    void AttributedString_createMutableCopy__wrapper();

    void AttributedString_dispose__wrapper();

    void MutableAttributedString__push(MutableAttributedStringRef value);
    MutableAttributedStringRef MutableAttributedString__pop();
    namespace MutableAttributedString {

        void create__wrapper();
    }

    void MutableAttributedString_replaceString__wrapper();

    void MutableAttributedString_setAttribute__wrapper();

    void MutableAttributedString_setCustomAttribute__wrapper();

    void MutableAttributedString_beginEditing__wrapper();

    void MutableAttributedString_endEditing__wrapper();

    void MutableAttributedString_dispose__wrapper();

    void Font__push(FontRef value);
    FontRef Font__pop();
    namespace Font {

        void Traits__push(Traits value, bool isReturn);
        Traits Traits__pop();

        void createFromFile__wrapper();

        void createWithName__wrapper();
    }

    void Font_createCopyWithSymbolicTraits__wrapper();

    void Font_getAscent__wrapper();

    void Font_getDescent__wrapper();

    void Font_getUnderlineThickness__wrapper();

    void Font_getUnderlinePosition__wrapper();

    void Font_dispose__wrapper();

    void TypographicBounds__push(TypographicBounds value, bool isReturn);
    TypographicBounds TypographicBounds__pop();

    void LineBoundsOptions__push(uint32_t value);
    uint32_t LineBoundsOptions__pop();

    void Run__push(RunRef value);
    RunRef Run__pop();
    namespace Run {

        void Status__push(uint32_t value);
        uint32_t Status__pop();

        void Info__push(Info value, bool isReturn);
        Info Info__pop();
    }

    void Run_getAttributes__wrapper();

    void Run_getTypographicBounds__wrapper();

    void Run_getStringRange__wrapper();

    void Run_getStatus__wrapper();

    void Run_dispose__wrapper();

    void Line__push(LineRef value);
    LineRef Line__pop();
    namespace Line {

        void Info__push(Info value, bool isReturn);
        Info Info__pop();

        void createWithAttributedString__wrapper();
    }

    void Line_getStringRange__wrapper();

    void Line_getTypographicBounds__wrapper();

    void Line_getBoundsWithOptions__wrapper();

    void Line_draw__wrapper();

    void Line_getGlyphRuns__wrapper();

    void Line_getOffsetForStringIndex__wrapper();

    void Line_getStringIndexForPosition__wrapper();

    void Line_dispose__wrapper();

    void Frame__push(FrameRef value);
    FrameRef Frame__pop();

    void Frame_draw__wrapper();

    void Frame_getLines__wrapper();

    void Frame_getLineOrigins__wrapper();

    void Frame_getLinesExtended__wrapper();

    void Frame_dispose__wrapper();

    void FrameSetter__push(FrameSetterRef value);
    FrameSetterRef FrameSetter__pop();
    namespace FrameSetter {

        void createWithAttributedString__wrapper();
    }

    void FrameSetter_createFrame__wrapper();

    void FrameSetter_dispose__wrapper();

    void ParagraphStyle__push(ParagraphStyleRef value);
    ParagraphStyleRef ParagraphStyle__pop();
    namespace ParagraphStyle {

        void TextAlignment__push(TextAlignment value);
        TextAlignment TextAlignment__pop();
        void Setting__push(std::shared_ptr<Setting::Base> value, bool isReturn);
        std::shared_ptr<Setting::Base> Setting__pop();

        void create__wrapper();
    }

    void ParagraphStyle_dispose__wrapper();

    int __register();
}
