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
struct __FontDescriptor; typedef struct __FontDescriptor* FontDescriptor;
struct __FontDescriptorArray; typedef struct __FontDescriptorArray* FontDescriptorArray;
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




// std::vector<FontDescriptor>


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
Color createColor(double red, double green, double blue, double alpha);
AttributedString createAttributedString(std::string s, AttributedStringOptions opts);
FontDescriptorArray fontManagerCreateFontDescriptorsFromURL(URL fileUrl);
Font fontCreateWithFontDescriptor(FontDescriptor descriptor, double size, AffineTransform matrix);
Line createLineWithAttributedString(AttributedString str);
void DrawContext_dispose(DrawContext _this);
void DrawContext_saveGState(DrawContext _this);
void DrawContext_restoreGState(DrawContext _this);
void DrawContext_setRGBFillColor(DrawContext _this, double red, double green, double blue, double alpha);
void DrawContext_fillRect(DrawContext _this, Rect rect);
void DrawContext_setTextMatrix(DrawContext _this, AffineTransform t);
void DrawContext_setTextPosition(DrawContext _this, double x, double y);
void Color_dispose(Color _this);
void AttributedString_dispose(AttributedString _this);
void FontDescriptor_dispose(FontDescriptor _this);
void FontDescriptorArray_dispose(FontDescriptorArray _this);
std::vector<FontDescriptor> FontDescriptorArray_items(FontDescriptorArray _this);
void Font_dispose(Font _this);
void Line_dispose(Line _this);
TypographicBounds Line_getTypographicBounds(Line _this);
Rect Line_getBoundsWithOptions(Line _this, uint32_t opts);
void Line_draw(Line _this, DrawContext context);
