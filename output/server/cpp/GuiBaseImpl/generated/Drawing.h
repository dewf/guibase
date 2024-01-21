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

struct AffineTransform {
    double a;
    double b;
    double c;
    double d;
    double tx;
    double ty;
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

struct __DrawContext; typedef struct __DrawContext* DrawContext;

struct __Font; typedef struct __Font* Font;

struct __FontDescriptor; typedef struct __FontDescriptor* FontDescriptor;

// std::vector<FontDescriptor>

struct __FontDescriptorArray; typedef struct __FontDescriptorArray* FontDescriptorArray;

extern const AffineTransform AffineTransformIdentity;

FontDescriptorArray fontManagerCreateFontDescriptorsFromURL(URL fileUrl);
Font fontCreateWithFontDescriptor(FontDescriptor descriptor, double size, AffineTransform matrix);
void DrawContext_saveGState(DrawContext _this);
void DrawContext_restoreGState(DrawContext _this);
void DrawContext_setRGBFillColor(DrawContext _this, double red, double green, double blue, double alpha);
void DrawContext_fillRect(DrawContext _this, Rect rect);
std::vector<FontDescriptor> FontDescriptorArray_items(FontDescriptorArray _this);
