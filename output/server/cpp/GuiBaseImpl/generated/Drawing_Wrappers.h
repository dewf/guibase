#include "Drawing.h"

void Point__push(Point value, bool isReturn);
Point Point__pop();

void Size__push(Size value, bool isReturn);
Size Size__pop();

void Rect__push(Rect value, bool isReturn);
Rect Rect__pop();

void DrawContext__push(DrawContext value);
DrawContext DrawContext__pop();

void DrawContext_saveGState__wrapper();

void DrawContext_restoreGState__wrapper();

void DrawContext_setRGBFillColor__wrapper();

void DrawContext_fillRect__wrapper();

int Drawing__register();
