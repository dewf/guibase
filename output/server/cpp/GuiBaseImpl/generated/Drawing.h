#pragma once

#include "../support/NativeImplServer.h"
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <set>

#include "Foundation.h"

struct __DrawContext; typedef struct __DrawContext* DrawContext;
struct __Color; typedef struct __Color* Color;
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
        FontField = 1,
        ForegroundColorField = 2
    };
    int32_t _usedFields;
    Font _font;
    Color _foregroundColor;
protected:
    int32_t getUsedFields() {
        return _usedFields;
    }
    friend void AttributedStringOptions__push(AttributedStringOptions value, bool isReturn);
    friend AttributedStringOptions AttributedStringOptions__pop();
public:
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

Rect makeRect(double x, double y, double width, double height);
void DrawContext_saveGState(DrawContext _this);
void DrawContext_restoreGState(DrawContext _this);
void DrawContext_setRGBFillColor(DrawContext _this, double red, double green, double blue, double alpha);
void DrawContext_setRGBStrokeColor(DrawContext _this, double red, double green, double blue, double alpha);
void DrawContext_fillRect(DrawContext _this, Rect rect);
void DrawContext_setTextMatrix(DrawContext _this, AffineTransform t);
void DrawContext_setTextPosition(DrawContext _this, double x, double y);
void DrawContext_beginPath(DrawContext _this);
void DrawContext_addArc(DrawContext _this, double x, double y, double radius, double startAngle, double endAngle, bool clockwise);
void DrawContext_drawPath(DrawContext _this, PathDrawingMode mode);
void DrawContext_setStrokeColorWithColor(DrawContext _this, Color color);
void DrawContext_strokeRectWithWidth(DrawContext _this, Rect rect, double width);
void DrawContext_moveToPoint(DrawContext _this, double x, double y);
void DrawContext_addLineToPoint(DrawContext _this, double x, double y);
void DrawContext_strokePath(DrawContext _this);
void DrawContext_setLineDash(DrawContext _this, double phase, std::vector<double> lengths);
void DrawContext_setLineWidth(DrawContext _this, double width);
void DrawContext_dispose(DrawContext _this);
Color Color_create(double red, double green, double blue, double alpha);
void Color_dispose(Color _this);
AttributedString AttributedString_create(std::string s, AttributedStringOptions opts);
void AttributedString_dispose(AttributedString _this);
Font Font_createFromFile(std::string path, double size, AffineTransform matrix);
void Font_dispose(Font _this);
TypographicBounds Line_getTypographicBounds(Line _this);
Rect Line_getBoundsWithOptions(Line _this, uint32_t opts);
void Line_draw(Line _this, DrawContext context);
Line Line_createWithAttributedString(AttributedString str);
void Line_dispose(Line _this);
