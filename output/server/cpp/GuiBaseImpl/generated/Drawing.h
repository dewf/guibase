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
struct __Font; typedef struct __Font* Font;
struct __Line; typedef struct __Line* Line;

struct AffineTransform {
    double a;
    double b;
    double c;
    double d;
    double tx;
    double ty;
};

struct AttributedStringOptions {
private:
    enum Fields {
        ForegroundColorField = 1,
        ForegroundColorFromContextField = 2,
        FontField = 4,
        StrokeWidthField = 8,
        StrokeColorField = 16
    };
    int32_t _usedFields;
    Color _foregroundColor;
    bool _foregroundColorFromContext;
    Font _font;
    double _strokeWidth;
    Color _strokeColor;
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
Font Font_createFromFile(std::string path, double size, OptArgs optArgs);
Font Font_createWithName(std::string name, double size, OptArgs optArgs);
void Font_dispose(Font _this);
TypographicBounds Line_getTypographicBounds(Line _this);
Rect Line_getBoundsWithOptions(Line _this, uint32_t opts);
void Line_draw(Line _this, DrawContext context);
Line Line_createWithAttributedString(AttributedString str);
void Line_dispose(Line _this);
