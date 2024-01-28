#pragma once

#include "../support/NativeImplServer.h"
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <set>

struct __Color; typedef struct __Color* Color;
struct __ColorSpace; typedef struct __ColorSpace* ColorSpace;
struct __Gradient; typedef struct __Gradient* Gradient;
struct __Path; typedef struct __Path* Path;
struct __DrawContext; typedef struct __DrawContext* DrawContext;
struct __AttributedString; typedef struct __AttributedString* AttributedString;
struct __MutableAttributedString; typedef struct __MutableAttributedString* MutableAttributedString;
struct __Font; typedef struct __Font* Font;
struct __Run; typedef struct __Run* Run;
struct __Line; typedef struct __Line* Line;
struct __Frame; typedef struct __Frame* Frame;
struct __FrameSetter; typedef struct __FrameSetter* FrameSetter;

struct AffineTransform {
    double a;
    double b;
    double c;
    double d;
    double tx;
    double ty;
};

// std::vector<std::string>

// std::vector<int64_t>

// std::map<std::string,int64_t>

struct AttributedStringOptions {
private:
    enum Fields {
        ForegroundColorField = 1,
        ForegroundColorFromContextField = 2,
        FontField = 4,
        StrokeWidthField = 8,
        StrokeColorField = 16,
        CustomField = 32
    };
    int32_t _usedFields;
    Color _foregroundColor;
    bool _foregroundColorFromContext;
    Font _font;
    double _strokeWidth;
    Color _strokeColor;
    std::map<std::string,int64_t> _custom;
protected:
    int32_t getUsedFields() {
        return _usedFields;
    }
    friend void AttributedStringOptions__push(AttributedStringOptions value, bool isReturn);
    friend AttributedStringOptions AttributedStringOptions__pop();
public:
    void setForegroundColor(Color value) {
        _foregroundColor = value;
        _usedFields |= Fields::ForegroundColorField;
    }
    bool hasForegroundColor(Color *value) {
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
    void setFont(Font value) {
        _font = value;
        _usedFields |= Fields::FontField;
    }
    bool hasFont(Font *value) {
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
    void setStrokeColor(Color value) {
        _strokeColor = value;
        _usedFields |= Fields::StrokeColorField;
    }
    bool hasStrokeColor(Color *value) {
        if (_usedFields & Fields::StrokeColorField) {
            *value = _strokeColor;
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


enum class ColorConstants {
    White,
    Black,
    Clear
};


enum class ColorSpaceName {
    GenericGray,
    GenericRGB,
    GenericCMYK,
    GenericRGBLinear,
    AdobeRGB1998,
    SRGB,
    GenericGrayGamma2_2
};


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

enum class PathDrawingMode {
    Fill,
    EOFill,
    Stroke,
    FillStroke,
    EOFillStroke
};

// std::vector<double>

enum GradientDrawingOptions {
    DrawsBeforeStartLocation = 1,
    DrawsAfterEndLocation = 2
};


struct FontTraits {
private:
    enum Fields {
        ItalicField = 1,
        BoldField = 2,
        ExpandedField = 4,
        CondensedField = 8,
        MonospaceField = 16,
        VerticalField = 32
    };
    int32_t _usedFields;
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
    friend void FontTraits__push(FontTraits value, bool isReturn);
    friend FontTraits FontTraits__pop();
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

struct OptArgs {
private:
    enum Fields {
        TransformField = 1
    };
    int32_t _usedFields;
    AffineTransform _transform;
protected:
    int32_t getUsedFields() {
        return _usedFields;
    }
    friend void OptArgs__push(OptArgs value, bool isReturn);
    friend OptArgs OptArgs__pop();
public:
    void setTransform(AffineTransform value) {
        _transform = value;
        _usedFields |= Fields::TransformField;
    }
    bool hasTransform(AffineTransform *value) {
        if (_usedFields & Fields::TransformField) {
            *value = _transform;
            return true;
        }
        return false;
    }
};


// std::vector<Line>

// std::vector<Point>

struct Range {
    int64_t location;
    int64_t length;
};



struct GradientStop {
    double location;
    double red;
    double green;
    double blue;
    double alpha;
};

// std::vector<GradientStop>


struct TypographicBounds {
    double width;
    double ascent;
    double descent;
    double leading;
};

enum LineBoundsOptions {
    ExcludeTypographicLeading = 1,
    ExcludeTypographicShifts = 2,
    UseHangingPunctuation = 4,
    UseGlyphPathBounds = 8,
    UseOpticalBounds = 16
};

// std::vector<Run>

// std::tuple<double,double>




enum RunStatus {
    NoStatus = 0,
    RightToLeft = 1,
    NonMonotonic = 2,
    HasNonIdentityMatrix = 4
};


extern const AffineTransform AffineTransformIdentity;

Color Color_createGenericRGB(double red, double green, double blue, double alpha);
Color Color_getConstantColor(ColorConstants which);
void Color_dispose(Color _this);
ColorSpace ColorSpace_createWithName(ColorSpaceName name);
ColorSpace ColorSpace_createDeviceGray();
void ColorSpace_dispose(ColorSpace _this);
Gradient Gradient_createWithColorComponents(ColorSpace space, std::vector<GradientStop> stops);
void Gradient_dispose(Gradient _this);
Path Path_createWithRect(Rect rect, OptArgs optArgs);
Path Path_createWithEllipseInRect(Rect rect, OptArgs optArgs);
Path Path_createWithRoundedRect(Rect rect, double cornerWidth, double cornerHeight, OptArgs optArgs);
void Path_dispose(Path _this);
void DrawContext_saveGState(DrawContext _this);
void DrawContext_restoreGState(DrawContext _this);
void DrawContext_setRGBFillColor(DrawContext _this, double red, double green, double blue, double alpha);
void DrawContext_setRGBStrokeColor(DrawContext _this, double red, double green, double blue, double alpha);
void DrawContext_setFillColorWithColor(DrawContext _this, Color color);
void DrawContext_fillRect(DrawContext _this, Rect rect);
void DrawContext_setTextMatrix(DrawContext _this, AffineTransform t);
void DrawContext_setTextPosition(DrawContext _this, double x, double y);
void DrawContext_beginPath(DrawContext _this);
void DrawContext_addArc(DrawContext _this, double x, double y, double radius, double startAngle, double endAngle, bool clockwise);
void DrawContext_addArcToPoint(DrawContext _this, double x1, double y1, double x2, double y2, double radius);
void DrawContext_drawPath(DrawContext _this, PathDrawingMode mode);
void DrawContext_setStrokeColorWithColor(DrawContext _this, Color color);
void DrawContext_strokeRectWithWidth(DrawContext _this, Rect rect, double width);
void DrawContext_moveToPoint(DrawContext _this, double x, double y);
void DrawContext_addLineToPoint(DrawContext _this, double x, double y);
void DrawContext_strokePath(DrawContext _this);
void DrawContext_setLineDash(DrawContext _this, double phase, std::vector<double> lengths);
void DrawContext_clearLineDash(DrawContext _this);
void DrawContext_setLineWidth(DrawContext _this, double width);
void DrawContext_clip(DrawContext _this);
void DrawContext_clipToRect(DrawContext _this, Rect clipRect);
void DrawContext_translateCTM(DrawContext _this, double tx, double ty);
void DrawContext_scaleCTM(DrawContext _this, double scaleX, double scaleY);
void DrawContext_rotateCTM(DrawContext _this, double angle);
void DrawContext_concatCTM(DrawContext _this, AffineTransform transform);
void DrawContext_addPath(DrawContext _this, Path path);
void DrawContext_fillPath(DrawContext _this);
void DrawContext_strokeRect(DrawContext _this, Rect rect);
void DrawContext_addRect(DrawContext _this, Rect rect);
void DrawContext_closePath(DrawContext _this);
void DrawContext_drawLinearGradient(DrawContext _this, Gradient gradient, Point startPoint, Point endPoint, uint32_t drawOpts);
void DrawContext_dispose(DrawContext _this);
AttributedString AttributedString_create(std::string s, AttributedStringOptions opts);
void AttributedString_dispose(AttributedString _this);
int64_t MutableAttributedString_getLength(MutableAttributedString _this);
void MutableAttributedString_replaceString(MutableAttributedString _this, Range range, std::string str);
void MutableAttributedString_beginEditing(MutableAttributedString _this);
void MutableAttributedString_endEditing(MutableAttributedString _this);
void MutableAttributedString_setAttribute(MutableAttributedString _this, Range range, AttributedStringOptions attr);
void MutableAttributedString_setCustomAttribute(MutableAttributedString _this, Range range, std::string key, int64_t value);
AttributedString MutableAttributedString_getNormalAttributedString_REMOVEME(MutableAttributedString _this);
MutableAttributedString MutableAttributedString_create(int64_t maxLength);
void MutableAttributedString_dispose(MutableAttributedString _this);
Font Font_createCopyWithSymbolicTraits(Font _this, double size, FontTraits newTraits, OptArgs optArgs);
double Font_getAscent(Font _this);
double Font_getDescent(Font _this);
double Font_getUnderlineThickness(Font _this);
double Font_getUnderlinePosition(Font _this);
Font Font_createFromFile(std::string path, double size, OptArgs optArgs);
Font Font_createWithName(std::string name, double size, OptArgs optArgs);
void Font_dispose(Font _this);
AttributedStringOptions Run_getAttributes(Run _this, std::vector<std::string> customKeys);
TypographicBounds Run_getTypographicBounds(Run _this, Range range);
Range Run_getStringRange(Run _this);
uint32_t Run_getStatus(Run _this);
void Run_dispose(Run _this);
TypographicBounds Line_getTypographicBounds(Line _this);
Rect Line_getBoundsWithOptions(Line _this, uint32_t opts);
void Line_draw(Line _this, DrawContext context);
std::vector<Run> Line_getGlyphRuns(Line _this);
std::tuple<double,double> Line_getLineOffsetForStringIndex(Line _this, int64_t charIndex);
Line Line_createWithAttributedString(AttributedString str);
void Line_dispose(Line _this);
void Frame_draw(Frame _this, DrawContext context);
std::vector<Line> Frame_getLines(Frame _this);
std::vector<Point> Frame_getLineOrigins(Frame _this, Range range);
void Frame_dispose(Frame _this);
FrameSetter FrameSetter_createWithAttributedString(AttributedString str);
Frame FrameSetter_createFrame(FrameSetter _this, Range range, Path path);
void FrameSetter_dispose(FrameSetter _this);
