#include "Drawing.h"

void AffineTransform__push(AffineTransform value, bool isReturn);
AffineTransform AffineTransform__pop();

void AttributedStringOptions__push(AttributedStringOptions value, bool isReturn);
AttributedStringOptions AttributedStringOptions__pop();

void AttributedString__push(AttributedString value);
AttributedString AttributedString__pop();

void ColorConstants__push(ColorConstants value);
ColorConstants ColorConstants__pop();

void Color__push(Color value);
Color Color__pop();
void ColorSpaceName__push(ColorSpaceName value, bool isReturn);
ColorSpaceName ColorSpaceName__pop();

void ColorSpace__push(ColorSpace value);
ColorSpace ColorSpace__pop();

void Point__push(Point value, bool isReturn);
Point Point__pop();

void Size__push(Size value, bool isReturn);
Size Size__pop();

void Rect__push(Rect value, bool isReturn);
Rect Rect__pop();

void PathDrawingMode__push(PathDrawingMode value);
PathDrawingMode PathDrawingMode__pop();

void GradientDrawingOptions__push(uint32_t value);
uint32_t GradientDrawingOptions__pop();

void DrawContext__push(DrawContext value);
DrawContext DrawContext__pop();

void OptArgs__push(OptArgs value, bool isReturn);
OptArgs OptArgs__pop();

void Font__push(Font value);
Font Font__pop();

void GradientStop__push(GradientStop value, bool isReturn);
GradientStop GradientStop__pop();

void Gradient__push(Gradient value);
Gradient Gradient__pop();

void TypographicBounds__push(TypographicBounds value, bool isReturn);
TypographicBounds TypographicBounds__pop();

void LineBoundsOptions__push(uint32_t value);
uint32_t LineBoundsOptions__pop();

void Line__push(Line value);
Line Line__pop();

void Path__push(Path value);
Path Path__pop();

void Color_createGenericRGB__wrapper();

void Color_getConstantColor__wrapper();

void Color_dispose__wrapper();

void ColorSpace_createWithName__wrapper();

void ColorSpace_createDeviceGray__wrapper();

void ColorSpace_dispose__wrapper();

void Gradient_createWithColorComponents__wrapper();

void Gradient_dispose__wrapper();

void Path_createWithRect__wrapper();

void Path_createWithEllipseInRect__wrapper();

void Path_createWithRoundedRect__wrapper();

void Path_dispose__wrapper();

void DrawContext_saveGState__wrapper();

void DrawContext_restoreGState__wrapper();

void DrawContext_setRGBFillColor__wrapper();

void DrawContext_setRGBStrokeColor__wrapper();

void DrawContext_fillRect__wrapper();

void DrawContext_setTextMatrix__wrapper();

void DrawContext_setTextPosition__wrapper();

void DrawContext_beginPath__wrapper();

void DrawContext_addArc__wrapper();

void DrawContext_addArcToPoint__wrapper();

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

void DrawContext_clipToRect__wrapper();

void DrawContext_translateCTM__wrapper();

void DrawContext_scaleCTM__wrapper();

void DrawContext_rotateCTM__wrapper();

void DrawContext_concatCTM__wrapper();

void DrawContext_addPath__wrapper();

void DrawContext_fillPath__wrapper();

void DrawContext_strokeRect__wrapper();

void DrawContext_addRect__wrapper();

void DrawContext_closePath__wrapper();

void DrawContext_drawLinearGradient__wrapper();

void DrawContext_dispose__wrapper();

void AttributedString_create__wrapper();

void AttributedString_dispose__wrapper();

void Font_createFromFile__wrapper();

void Font_createWithName__wrapper();

void Font_dispose__wrapper();

void Line_getTypographicBounds__wrapper();

void Line_getBoundsWithOptions__wrapper();

void Line_draw__wrapper();

void Line_createWithAttributedString__wrapper();

void Line_dispose__wrapper();

void __constantsFunc();

int Drawing__register();
