#pragma once

#include "../support/NativeImplServer.h"
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <set>

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

void DrawContext_saveGState(DrawContext _this);
void DrawContext_restoreGState(DrawContext _this);
void DrawContext_setRGBFillColor(DrawContext _this, double red, double green, double blue, double alpha);
void DrawContext_fillRect(DrawContext _this, Rect rect);
