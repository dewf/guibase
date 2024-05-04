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

#include "Drawing.h"
using namespace Drawing;

namespace Text
{

    struct __AttributedString; typedef struct __AttributedString* AttributedStringRef;
    struct __MutableAttributedString; typedef struct __MutableAttributedString* MutableAttributedStringRef; // extends AttributedStringRef
    struct __Font; typedef struct __Font* FontRef;
    struct __Run; typedef struct __Run* RunRef;
    struct __Line; typedef struct __Line* LineRef;
    struct __Frame; typedef struct __Frame* FrameRef;
    struct __FrameSetter; typedef struct __FrameSetter* FrameSetterRef;
    struct __ParagraphStyle; typedef struct __ParagraphStyle* ParagraphStyleRef;

    struct Range {
        int64_t location;
        int64_t length;
    };

    namespace AttributedString {

        struct Options {
        private:
            enum Fields {
                ForegroundColorField = 1,
                ForegroundColorFromContextField = 2,
                FontField = 4,
                StrokeWidthField = 8,
                StrokeColorField = 16,
                ParagraphStyleField = 32,
                CustomField = 64
            };
            int32_t _usedFields = 0;
            ColorRef _foregroundColor;
            bool _foregroundColorFromContext;
            FontRef _font;
            double _strokeWidth;
            ColorRef _strokeColor;
            ParagraphStyleRef _paragraphStyle;
            std::map<std::string,int64_t> _custom;
        protected:
            int32_t getUsedFields() {
                return _usedFields;
            }
            friend void Options__push(Options value, bool isReturn);
            friend Options Options__pop();
        public:
            void setForegroundColor(ColorRef value) {
                _foregroundColor = value;
                _usedFields |= Fields::ForegroundColorField;
            }
            bool hasForegroundColor(ColorRef *value) {
                if (_usedFields & Fields::ForegroundColorField) {
                    *value = _foregroundColor;
                    return true;
                }
                return false;
            }
            void setForegroundColorFromContext(bool value) {
                _foregroundColorFromContext = value;
                _usedFields |= Fields::ForegroundColorFromContextField;
            }
            bool hasForegroundColorFromContext(bool *value) {
                if (_usedFields & Fields::ForegroundColorFromContextField) {
                    *value = _foregroundColorFromContext;
                    return true;
                }
                return false;
            }
            void setFont(FontRef value) {
                _font = value;
                _usedFields |= Fields::FontField;
            }
            bool hasFont(FontRef *value) {
                if (_usedFields & Fields::FontField) {
                    *value = _font;
                    return true;
                }
                return false;
            }
            void setStrokeWidth(double value) {
                _strokeWidth = value;
                _usedFields |= Fields::StrokeWidthField;
            }
            bool hasStrokeWidth(double *value) {
                if (_usedFields & Fields::StrokeWidthField) {
                    *value = _strokeWidth;
                    return true;
                }
                return false;
            }
            void setStrokeColor(ColorRef value) {
                _strokeColor = value;
                _usedFields |= Fields::StrokeColorField;
            }
            bool hasStrokeColor(ColorRef *value) {
                if (_usedFields & Fields::StrokeColorField) {
                    *value = _strokeColor;
                    return true;
                }
                return false;
            }
            void setParagraphStyle(ParagraphStyleRef value) {
                _paragraphStyle = value;
                _usedFields |= Fields::ParagraphStyleField;
            }
            bool hasParagraphStyle(ParagraphStyleRef *value) {
                if (_usedFields & Fields::ParagraphStyleField) {
                    *value = _paragraphStyle;
                    return true;
                }
                return false;
            }
            void setCustom(std::map<std::string,int64_t> value) {
                _custom = value;
                _usedFields |= Fields::CustomField;
            }
            bool hasCustom(std::map<std::string,int64_t> *value) {
                if (_usedFields & Fields::CustomField) {
                    *value = _custom;
                    return true;
                }
                return false;
            }
        };
        AttributedStringRef create(std::string s, Options opts);
    }
    int64_t AttributedString_getLength(AttributedStringRef _this);
    MutableAttributedStringRef AttributedString_createMutableCopy(AttributedStringRef _this, int64_t maxLength);
    void AttributedString_dispose(AttributedStringRef _this);

    namespace MutableAttributedString {
        MutableAttributedStringRef create(int64_t maxLength);
    }
    void MutableAttributedString_replaceString(MutableAttributedStringRef _this, Range range, std::string str);
    void MutableAttributedString_setAttribute(MutableAttributedStringRef _this, Range range, AttributedString::Options attr);
    void MutableAttributedString_setCustomAttribute(MutableAttributedStringRef _this, Range range, std::string key, int64_t value);
    void MutableAttributedString_beginEditing(MutableAttributedStringRef _this);
    void MutableAttributedString_endEditing(MutableAttributedStringRef _this);
    void MutableAttributedString_dispose(MutableAttributedStringRef _this);

    namespace Font {

        struct Traits {
        private:
            enum Fields {
                ItalicField = 1,
                BoldField = 2,
                ExpandedField = 4,
                CondensedField = 8,
                MonospaceField = 16,
                VerticalField = 32
            };
            int32_t _usedFields = 0;
            bool _italic;
            bool _bold;
            bool _expanded;
            bool _condensed;
            bool _monospace;
            bool _vertical;
        protected:
            int32_t getUsedFields() {
                return _usedFields;
            }
            friend void Traits__push(Traits value, bool isReturn);
            friend Traits Traits__pop();
        public:
            void setItalic(bool value) {
                _italic = value;
                _usedFields |= Fields::ItalicField;
            }
            bool hasItalic(bool *value) {
                if (_usedFields & Fields::ItalicField) {
                    *value = _italic;
                    return true;
                }
                return false;
            }
            void setBold(bool value) {
                _bold = value;
                _usedFields |= Fields::BoldField;
            }
            bool hasBold(bool *value) {
                if (_usedFields & Fields::BoldField) {
                    *value = _bold;
                    return true;
                }
                return false;
            }
            void setExpanded(bool value) {
                _expanded = value;
                _usedFields |= Fields::ExpandedField;
            }
            bool hasExpanded(bool *value) {
                if (_usedFields & Fields::ExpandedField) {
                    *value = _expanded;
                    return true;
                }
                return false;
            }
            void setCondensed(bool value) {
                _condensed = value;
                _usedFields |= Fields::CondensedField;
            }
            bool hasCondensed(bool *value) {
                if (_usedFields & Fields::CondensedField) {
                    *value = _condensed;
                    return true;
                }
                return false;
            }
            void setMonospace(bool value) {
                _monospace = value;
                _usedFields |= Fields::MonospaceField;
            }
            bool hasMonospace(bool *value) {
                if (_usedFields & Fields::MonospaceField) {
                    *value = _monospace;
                    return true;
                }
                return false;
            }
            void setVertical(bool value) {
                _vertical = value;
                _usedFields |= Fields::VerticalField;
            }
            bool hasVertical(bool *value) {
                if (_usedFields & Fields::VerticalField) {
                    *value = _vertical;
                    return true;
                }
                return false;
            }
        };
        FontRef createFromFile(std::string path, double size, std::optional<AffineTransform> transform);
        FontRef createWithName(std::string name, double size, std::optional<AffineTransform> transform);
    }
    FontRef Font_createCopyWithSymbolicTraits(FontRef _this, double size, std::optional<AffineTransform> transform, Font::Traits newTraits);
    double Font_getAscent(FontRef _this);
    double Font_getDescent(FontRef _this);
    double Font_getUnderlineThickness(FontRef _this);
    double Font_getUnderlinePosition(FontRef _this);
    void Font_dispose(FontRef _this);

    struct TypographicBounds {
        double width;
        double ascent;
        double descent;
        double leading;
    };

    enum LineBoundsOptions {
        ExcludeTypographicLeading = 1,
        ExcludeTypographicShifts = 1 << 1,
        UseHangingPunctuation = 1 << 2,
        UseGlyphPathBounds = 1 << 3,
        UseOpticalBounds = 1 << 4
    };

    namespace Run {

        enum Status {
            NoStatus = 0,
            RightToLeft = 1,
            NonMonotonic = 1 << 1,
            HasNonIdentityMatrix = 1 << 2
        };

        struct Info {
            AttributedString::Options attrs;
            Range sourceRange;
            uint32_t status;
            Rect bounds;
            TypographicBounds typoBounds;
        };
    }
    AttributedString::Options Run_getAttributes(RunRef _this, std::vector<std::string> customKeys);
    TypographicBounds Run_getTypographicBounds(RunRef _this, Range range);
    Range Run_getStringRange(RunRef _this);
    uint32_t Run_getStatus(RunRef _this);
    void Run_dispose(RunRef _this);

    namespace Line {

        struct Info {
            Point origin;
            TypographicBounds lineTypoBounds;
            std::vector<Run::Info> runs;
        };
        LineRef createWithAttributedString(AttributedStringRef str);
    }
    Range Line_getStringRange(LineRef _this);
    TypographicBounds Line_getTypographicBounds(LineRef _this);
    Rect Line_getBoundsWithOptions(LineRef _this, uint32_t opts);
    void Line_draw(LineRef _this, DrawContextRef context);
    std::vector<RunRef> Line_getGlyphRuns(LineRef _this);
    std::tuple<double,double> Line_getOffsetForStringIndex(LineRef _this, int64_t charIndex);
    int64_t Line_getStringIndexForPosition(LineRef _this, Point p);
    void Line_dispose(LineRef _this);

    void Frame_draw(FrameRef _this, DrawContextRef context);
    std::vector<LineRef> Frame_getLines(FrameRef _this);
    std::vector<Point> Frame_getLineOrigins(FrameRef _this, Range range);
    std::vector<Line::Info> Frame_getLinesExtended(FrameRef _this, std::vector<std::string> customKeys);
    void Frame_dispose(FrameRef _this);

    namespace FrameSetter {
        FrameSetterRef createWithAttributedString(AttributedStringRef str);
    }
    FrameRef FrameSetter_createFrame(FrameSetterRef _this, Range range, PathRef path);
    void FrameSetter_dispose(FrameSetterRef _this);

    namespace ParagraphStyle {

        namespace Setting {
            class Base;
        }

        enum class TextAlignment {
            Left,
            Right,
            Center,
            Justified,
            Natural
        };

        namespace Setting {
            class Alignment;

            class Visitor {
            public:
                virtual void onAlignment(const Alignment* alignment) = 0;
            };

            class Base {
            public:
                virtual void accept(Visitor* visitor) = 0;
            };

            class Alignment : public Base {
            public:
                const TextAlignment value;
                Alignment(TextAlignment value) : value(value) {}
                void accept(Visitor* visitor) override {
                    visitor->onAlignment(this);
                }
            };
        }
        ParagraphStyleRef create(std::vector<std::shared_ptr<Setting::Base>> settings);
    }
    void ParagraphStyle_dispose(ParagraphStyleRef _this);
}
