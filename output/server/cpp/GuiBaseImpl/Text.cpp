#include "generated/Text.h"
#include "deps/opendl/source/opendl.h"
#include "deps/opendl/deps/CFMinimal/source/CF/CFMisc.h" // for exceptions

#include "util.h"

#define STRUCT_CAST(t, v) *((t*)&v)

namespace Text
{
    namespace AttributedString {
        AttributedStringRef create(std::string s, Options opts) {
            auto text = dl_CFStringCreateWithCString(s.c_str());
            auto dict = dl_CFDictionaryCreateMutable(0);

            ColorRef foregroundColor;
            if (opts.hasForegroundColor(&foregroundColor)) {
                dl_CFDictionarySetValue(dict, dl_kCTForegroundColorAttributeName, (dl_CGColorRef)foregroundColor);
            }

            bool foregroundColorFromContext;
            if (opts.hasForegroundColorFromContext(&foregroundColorFromContext)) {
                auto cfBool = foregroundColorFromContext ? dl_kCFBooleanTrue : dl_kCFBooleanFalse;
                dl_CFDictionarySetValue(dict, dl_kCTForegroundColorFromContextAttributeName, cfBool);
            }

            FontRef f;
            if (opts.hasFont(&f)) {
                dl_CFDictionarySetValue(dict, dl_kCTFontAttributeName, (dl_CTFontRef)f); // cast not actually necessary, but makes clear we're using CTFont
            }

            double strokeWidth;
            if (opts.hasStrokeWidth(&strokeWidth)) {
                auto cfNumber = dl_CFNumberWithFloat((float)strokeWidth);
                dl_CFDictionarySetValue(dict, dl_kCTStrokeWidthAttributeName, cfNumber);
                dl_CFRelease(cfNumber);
            }

            ColorRef strokeColor;
            if (opts.hasStrokeColor(&strokeColor)) {
                dl_CFDictionarySetValue(dict, dl_kCTStrokeColorAttributeName, (dl_CGColorRef)strokeColor);
            }

            auto str = dl_CFAttributedStringCreate(text, dict);

            dl_CFRelease(dict);
            dl_CFRelease(text);

            return (AttributedStringRef)str;
        }
    }

    int64_t AttributedString_getLength(AttributedStringRef _this) {
        return dl_CFAttributedStringGetLength((dl_CFAttributedStringRef)_this); // could be mutable for all we know!
    }

    MutableAttributedStringRef AttributedString_createMutableCopy(AttributedStringRef _this, int64_t maxLength) {
        return (MutableAttributedStringRef)dl_CFAttributedStringCreateMutableCopy(maxLength, (dl_CFAttributedStringRef)_this);
    }

    void AttributedString_dispose(AttributedStringRef _this) {
        dl_CFRelease(_this);
    }

    namespace MutableAttributedString {
        MutableAttributedStringRef create(int64_t maxLength) {
            return (MutableAttributedStringRef)dl_CFAttributedStringCreateMutable(maxLength);
        }
    }

    void MutableAttributedString_replaceString(MutableAttributedStringRef _this, Range range, std::string str) {
        auto replacement = dl_CFStringCreateWithCString(str.c_str());
        dl_CFAttributedStringReplaceString((dl_CFMutableAttributedStringRef)_this, STRUCT_CAST(dl_CFRange, range), replacement); // note the struct cast only works in 64-bit mode!
        dl_CFRelease(replacement);
    }

    void MutableAttributedString_setAttribute(MutableAttributedStringRef _this, Range range, AttributedString::Options attr) {
        auto cfRange = STRUCT_CAST(dl_CFRange, range);

        ColorRef foreground;
        if (attr.hasForegroundColor(&foreground)) {
            dl_CFAttributedStringSetAttribute((dl_CFMutableAttributedStringRef)_this, cfRange, dl_kCTForegroundColorAttributeName, foreground);
        }

        bool foregroundFromContext;
        if (attr.hasForegroundColorFromContext(&foregroundFromContext)) {
            auto cfBool = foregroundFromContext ? dl_kCFBooleanTrue : dl_kCFBooleanFalse;
            dl_CFAttributedStringSetAttribute((dl_CFMutableAttributedStringRef)_this, cfRange, dl_kCTForegroundColorFromContextAttributeName, cfBool);
        }

        FontRef font;
        if (attr.hasFont(&font)) {
            dl_CFAttributedStringSetAttribute((dl_CFMutableAttributedStringRef)_this, cfRange, dl_kCTFontAttributeName, font);
        }

        double strokeWidth;
        if (attr.hasStrokeWidth(&strokeWidth)) {
            auto cfWidth = dl_CFNumberWithFloat((float)strokeWidth); // because double isn't working (nothing supports casting yet)
            dl_CFAttributedStringSetAttribute((dl_CFMutableAttributedStringRef)_this, cfRange, dl_kCTStrokeWidthAttributeName, cfWidth);
            dl_CFRelease(cfWidth);
        }

        ColorRef strokeColor;
        if (attr.hasStrokeColor(&strokeColor)) {
            dl_CFAttributedStringSetAttribute((dl_CFMutableAttributedStringRef)_this, cfRange, dl_kCTStrokeColorAttributeName, strokeColor);
        }

        ParagraphStyleRef paraStyle;
        if (attr.hasParagraphStyle(&paraStyle)) {
            dl_CFAttributedStringSetAttribute((dl_CFMutableAttributedStringRef)_this, cfRange, dl_kCTParagraphStyleAttributeName, paraStyle);
        }
    }

    void MutableAttributedString_setCustomAttribute(MutableAttributedStringRef _this, Range range, std::string key, int64_t value) {
        auto cfKey = __dl_CFStringMakeConstantString(key.c_str()); // needs to be a constant (deduplicated) for anything key-related
        auto cfValue = dl_CFNumberCreate(dl_CFNumberType::dl_kCFNumberLongType, &value);

        dl_CFAttributedStringSetAttribute((dl_CFMutableAttributedStringRef)_this, STRUCT_CAST(dl_CFRange, range), cfKey, cfValue);

        dl_CFRelease(cfValue);
        // dl_CFRelease(cfKey); // constant strings don't need to be released
    }

    void MutableAttributedString_beginEditing(MutableAttributedStringRef _this) {
        dl_CFAttributedStringBeginEditing((dl_CFMutableAttributedStringRef)_this);
    }

    void MutableAttributedString_endEditing(MutableAttributedStringRef _this) {
        dl_CFAttributedStringEndEditing((dl_CFMutableAttributedStringRef)_this);
    }

    void MutableAttributedString_dispose(MutableAttributedStringRef _this) {
        dl_CFRelease(_this);
    }

    namespace Font {
        FontRef createFromFile(std::string path, double size, std::optional<AffineTransform> transform) {
            auto pathStr = dl_CFStringCreateWithCString(path.c_str());
            auto url = dl_CFURLCreateWithFileSystemPath(pathStr, dl_CFURLPathStyle::dl_kCFURLPOSIXPathStyle, false);
            auto descriptors = dl_CTFontManagerCreateFontDescriptorsFromURL(url);

            FontRef result = nullptr;
            if (dl_CFArrayGetCount(descriptors) > 0) {
                auto first = (dl_CTFontDescriptorRef)dl_CFArrayGetValueAtIndex(descriptors, 0);
                result = (FontRef)dl_CTFontCreateWithFontDescriptor(first, size, dlOptionalTransform(transform));
            }
            dl_CFRelease(descriptors);
            dl_CFRelease(url);
            dl_CFRelease(pathStr);
            return result;
        }

        FontRef createWithName(std::string name, double size, std::optional<AffineTransform> transform) {
            dl_CTFontRef ret;

            auto nameStr = dl_CFStringCreateWithCString(name.c_str());

            ret = dl_CTFontCreateWithName(nameStr, size, dlOptionalTransform(transform));
            dl_CFRelease(nameStr);

            return (FontRef)ret;
        }
    }

    FontRef Font_createCopyWithSymbolicTraits(FontRef _this, double size, std::optional<AffineTransform> transform, Font::Traits newTraits) {
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
        return (FontRef)dl_CTFontCreateCopyWithSymbolicTraits((dl_CTFontRef)_this, size, dlOptionalTransform(transform), value, mask);
    }

    double Font_getAscent(FontRef _this) {
        return dl_CTFontGetAscent((dl_CTFontRef)_this);
    }

    double Font_getDescent(FontRef _this) {
        return dl_CTFontGetDescent((dl_CTFontRef)_this);
    }

    double Font_getUnderlineThickness(FontRef _this) {
        return dl_CTFontGetUnderlineThickness((dl_CTFontRef)_this);
    }

    double Font_getUnderlinePosition(FontRef _this) {
        return dl_CTFontGetUnderlinePosition((dl_CTFontRef)_this);
    }

    void Font_dispose(FontRef _this) {
        dl_CFRelease(_this);
    }

    AttributedString::Options Run_getAttributes(RunRef _this, std::vector<std::string> customKeys) {
        AttributedString::Options ret;
        auto attrs = dl_CTRunGetAttributes((dl_CTRunRef)_this);

        auto foregroundColor = (ColorRef)dl_CFDictionaryGetValue(attrs, dl_kCTForegroundColorAttributeName);
        if (foregroundColor != nullptr) {
            ret.setForegroundColor(foregroundColor);
        }

        auto foregroundFromContext = (dl_CFBooleanRef)dl_CFDictionaryGetValue(attrs, dl_kCTForegroundColorFromContextAttributeName);
        if (foregroundFromContext != nullptr) {
            ret.setForegroundColorFromContext(foregroundFromContext == dl_kCFBooleanTrue);
        }

        auto font = (FontRef)dl_CFDictionaryGetValue(attrs, dl_kCTFontAttributeName);
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

        auto strokeColor = (ColorRef)dl_CFDictionaryGetValue(attrs, dl_kCTStrokeColorAttributeName);
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

    TypographicBounds Run_getTypographicBounds(RunRef _this, Range range) {
        TypographicBounds ret;
        ret.width = dl_CTRunGetTypographicBounds((dl_CTRunRef)_this, STRUCT_CAST(dl_CFRange, range), &ret.ascent, &ret.descent, &ret.leading);
        return ret;
    }

    Range Run_getStringRange(RunRef _this) {
        auto ret = dl_CTRunGetStringRange((dl_CTRunRef)_this);
        return STRUCT_CAST(Range, ret);
    }

    uint32_t Run_getStatus(RunRef _this) {
        return dl_CTRunGetStatus((dl_CTRunRef)_this);
    }

    void Run_dispose(RunRef _this) {
        // but I don't think these are ever owned by the existing API ...
        // dl_CFRelease(_this);
        printf("called Run_dispose ... why?\n");
    }

    namespace Line {
        LineRef createWithAttributedString(AttributedStringRef str) {
            return (LineRef)dl_CTLineCreateWithAttributedString((dl_CFAttributedStringRef)str);
        }
    }

    Range Line_getStringRange(LineRef _this) {
        auto ret = dl_CTLineGetStringRange((dl_CTLineRef)_this);
        return STRUCT_CAST(Range, ret);
    }

    TypographicBounds Line_getTypographicBounds(LineRef _this) {
        dl_CGFloat tb_width, ascent, descent, leading;
        tb_width = dl_CTLineGetTypographicBounds((dl_CTLineRef)_this, &ascent, &descent, &leading);
        return TypographicBounds{ tb_width, ascent, descent, leading };
    }

    Rect Line_getBoundsWithOptions(LineRef _this, uint32_t opts) {
        auto r = dl_CTLineGetBoundsWithOptions((dl_CTLineRef)_this, (dl_CTLineBoundsOptions)opts);
        return STRUCT_CAST(Rect, r);
    }

    void Line_draw(LineRef _this, DrawContextRef context) {
        dl_CTLineDraw((dl_CTLineRef)_this, (dl_CGContextRef)context);
    }

    std::vector<RunRef> Line_getGlyphRuns(LineRef _this) {
        std::vector<RunRef> ret;
        auto arr = dl_CTLineGetGlyphRuns((dl_CTLineRef)_this);
        auto count = dl_CFArrayGetCount(arr);
        for (auto i = 0; i < count; i++) {
            auto run = (RunRef)dl_CFArrayGetValueAtIndex(arr, i);
            ret.push_back(run);
        }
        return ret;
    }

    std::tuple<double, double> Line_getOffsetForStringIndex(LineRef _this, int64_t charIndex) {
        double secondary;
        auto primary = dl_CTLineGetOffsetForStringIndex((dl_CTLineRef)_this, charIndex, &secondary);
        return std::tuple<double, double>(primary, secondary);
    }

    int64_t Line_getStringIndexForPosition(LineRef _this, Point p) {
        return dl_CTLineGetStringIndexForPosition((dl_CTLineRef)_this, STRUCT_CAST(dl_CGPoint, p));
    }

    void Line_dispose(LineRef _this) {
        dl_CFRelease(_this);
    }

    void Frame_draw(FrameRef _this, DrawContextRef context) {
        dl_CTFrameDraw((dl_CTFrameRef)_this, (dl_CGContextRef)context);
    }

    std::vector<LineRef> Frame_getLines(FrameRef _this) {
        auto arr = dl_CTFrameGetLines((dl_CTFrameRef)_this);
        auto count = dl_CFArrayGetCount(arr);

        std::vector<LineRef> ret;
        for (auto i = 0; i < count; i++) {
            auto line = (dl_CTLineRef)dl_CFArrayGetValueAtIndex(arr, i);
            ret.push_back((LineRef)line);
        }
        return ret;
    }

    std::vector<Point> Frame_getLineOrigins(FrameRef _this, Range range) {
        auto ctLinesArr = dl_CTFrameGetLines((dl_CTFrameRef)_this);
        auto lineCount = dl_CFArrayGetCount(ctLinesArr);

        std::vector<Point> origins(lineCount);
        dl_CTFrameGetLineOrigins((dl_CTFrameRef)_this, STRUCT_CAST(dl_CFRange, range), (dl_CGPoint*)origins.data());
        return origins;
    }

    std::vector<Line::Info> Frame_getLinesExtended(FrameRef _this, std::vector<std::string> customKeys) {
        std::vector<Line::Info> ret;
        auto ctLinesArr = dl_CTFrameGetLines((dl_CTFrameRef)_this);
        auto lineCount = dl_CFArrayGetCount(ctLinesArr);

        std::vector<Point> origins(lineCount);
        dl_CTFrameGetLineOrigins((dl_CTFrameRef)_this, dl_CFRangeZero, (dl_CGPoint*)origins.data());

        for (auto lineIndex = 0; lineIndex < lineCount; lineIndex++) {
            Line::Info line;
            line.origin = origins[lineIndex];

            auto ctLine = (dl_CTLineRef)dl_CFArrayGetValueAtIndex(ctLinesArr, lineIndex);
            line.lineTypoBounds = Line_getTypographicBounds((LineRef)ctLine);

            auto ctRunsArr = dl_CTLineGetGlyphRuns(ctLine);
            auto runCount = dl_CFArrayGetCount(ctRunsArr);
            for (auto runIndex = 0; runIndex < runCount; runIndex++) {
                Run::Info run;

                auto ctRun = (dl_CTRunRef)dl_CFArrayGetValueAtIndex(ctRunsArr, runIndex);
                run.attrs = Run_getAttributes((RunRef)ctRun, customKeys);

                run.typoBounds = Run_getTypographicBounds((RunRef)ctRun, STRUCT_CAST(Range, dl_CFRangeZero));
                run.bounds = STRUCT_CAST(Rect, dl_CGRectZero);

                // might want to pad these with user-definable pads?
                run.bounds.size.width = run.typoBounds.width;
                run.bounds.size.height = run.typoBounds.ascent + run.typoBounds.descent;

                auto xOffset = 0.0;
                auto runRange = dl_CTRunGetStringRange(ctRun);
                run.sourceRange = STRUCT_CAST(Range, runRange);
                run.status = (Run::Status)dl_CTRunGetStatus(ctRun);
                if (run.status & Run::Status::RightToLeft) {
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

    void Frame_dispose(FrameRef _this) {
        dl_CFRelease((dl_CTFrameRef)_this);
    }

    namespace FrameSetter {
        FrameSetterRef createWithAttributedString(AttributedStringRef str) {
            return (FrameSetterRef)dl_CTFramesetterCreateWithAttributedString((dl_CFAttributedStringRef)str);
        }
    }

    FrameRef FrameSetter_createFrame(FrameSetterRef _this, Range range, PathRef path) {
        auto dict = dl_CFDictionaryCreate(nullptr, nullptr, 0);
        auto ret = (FrameRef)dl_CTFramesetterCreateFrame((dl_CTFramesetterRef)_this, STRUCT_CAST(dl_CFRange, range), (dl_CGPathRef)path, dict);
        dl_CFRelease(dict);
        return ret;
    }

    void FrameSetter_dispose(FrameSetterRef _this) {
        dl_CFRelease(_this);
    }

    namespace ParagraphStyle {
        class SettingVisitor : public Setting::Visitor {
            dl_CTParagraphStyleSetting& pss;
        public:
            SettingVisitor(dl_CTParagraphStyleSetting& pss) : pss(pss) {}
            void onAlignment(const Setting::Alignment* alignment) {
                pss.spec = dl_kCTParagraphStyleSpecifierAlignment;
                auto value = alignment->value;
                pss.value = &value;
                pss.valueSize = sizeof(value);
            }
        };

        ParagraphStyleRef create(std::vector<std::shared_ptr<Setting::Base>> settings) {
            std::vector<dl_CTParagraphStyleSetting> ctSettings;

            for (auto i = settings.begin(); i != settings.end(); i++) {
                dl_CTParagraphStyleSetting pss;

                SettingVisitor v(pss);
                i->get()->accept(&v);

                ctSettings.push_back(pss);
            }

            return (ParagraphStyleRef)dl_CTParagraphStyleCreate(ctSettings.data(), ctSettings.size());
        }
    }

    void ParagraphStyle_dispose(ParagraphStyleRef _this) {
        dl_CFRelease(_this);
    }
}
