#include "Drawing.h"

void AffineTransform__push(AffineTransform value, bool isReturn);
AffineTransform AffineTransform__pop();

void AttributedStringOptions__push(AttributedStringOptions value, bool isReturn);
AttributedStringOptions AttributedStringOptions__pop();

void AttributedString__push(AttributedString value);
AttributedString AttributedString__pop();

void Color__push(Color value);
Color Color__pop();

void Point__push(Point value, bool isReturn);
Point Point__pop();

void Size__push(Size value, bool isReturn);
Size Size__pop();

void Rect__push(Rect value, bool isReturn);
Rect Rect__pop();

void PathDrawingMode__push(PathDrawingMode value);
PathDrawingMode PathDrawingMode__pop();

void DrawContext__push(DrawContext value);
DrawContext DrawContext__pop();

void Font__push(Font value);
Font Font__pop();

void TypographicBounds__push(TypographicBounds value, bool isReturn);
TypographicBounds TypographicBounds__pop();

void LineBoundsOptions__push(uint32_t value);
uint32_t LineBoundsOptions__pop();

void Line__push(Line value);
Line Line__pop();

void makeRect__wrapper();

void DrawContext_saveGState__wrapper();

void DrawContext_restoreGState__wrapper();

void DrawContext_setRGBFillColor__wrapper();

void DrawContext_setRGBStrokeColor__wrapper();

void DrawContext_fillRect__wrapper();

void DrawContext_setTextMatrix__wrapper();

void DrawContext_setTextPosition__wrapper();

void DrawContext_beginPath__wrapper();

void DrawContext_addArc__wrapper();

void DrawContext_drawPath__wrapper();

void DrawContext_setStrokeColorWithColor__wrapper();

void DrawContext_strokeRectWithWidth__wrapper();

void DrawContext_moveToPoint__wrapper();

void DrawContext_addLineToPoint__wrapper();

void DrawContext_strokePath__wrapper();

void DrawContext_setLineDash__wrapper();

void DrawContext_clearLineDash__wrapper();

void DrawContext_setLineWidth__wrapper();

void DrawContext_clip__wrapper();

void DrawContext_translateCTM__wrapper();

void DrawContext_dispose__wrapper();

void Color_create__wrapper();

void Color_dispose__wrapper();

void AttributedString_create__wrapper();

void AttributedString_dispose__wrapper();

void Font_createFromFile__wrapper();

void Font_dispose__wrapper();

void Line_getTypographicBounds__wrapper();

void Line_getBoundsWithOptions__wrapper();

void Line_draw__wrapper();

void Line_createWithAttributedString__wrapper();

void Line_dispose__wrapper();

void __constantsFunc();

int Drawing__register();
