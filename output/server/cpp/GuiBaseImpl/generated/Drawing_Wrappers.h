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

void ColorSpaceName__push(ColorSpaceName value);
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

void FontTraits__push(FontTraits value, bool isReturn);
FontTraits FontTraits__pop();

void OptArgs__push(OptArgs value, bool isReturn);
OptArgs OptArgs__pop();

void Font__push(Font value);
Font Font__pop();
void Range__push(Range value, bool isReturn);
Range Range__pop();

void Frame__push(Frame value);
Frame Frame__pop();

void FrameSetter__push(FrameSetter value);
FrameSetter FrameSetter__pop();

void GradientStop__push(GradientStop value, bool isReturn);
GradientStop GradientStop__pop();

void Gradient__push(Gradient value);
Gradient Gradient__pop();

void TypographicBounds__push(TypographicBounds value, bool isReturn);
TypographicBounds TypographicBounds__pop();

void LineBoundsOptions__push(uint32_t value);
uint32_t LineBoundsOptions__pop();

void __DoubleDouble_Tuple__push(std::tuple<double,double> value, bool isReturn);
std::tuple<double,double> __DoubleDouble_Tuple__pop();

void Line__push(Line value);
Line Line__pop();

void MutableAttributedString__push(MutableAttributedString value);
MutableAttributedString MutableAttributedString__pop();

void Path__push(Path value);
Path Path__pop();

void __String_Int64_Map__push(std::map<std::string,int64_t> _map, bool isReturn);
std::map<std::string,int64_t> __String_Int64_Map__pop();

void RunStatus__push(uint32_t value);
uint32_t RunStatus__pop();

void Run__push(Run value);
Run Run__pop();

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

void MutableAttributedString_getLength__wrapper();

void MutableAttributedString_replaceString__wrapper();

void MutableAttributedString_beginEditing__wrapper();

void MutableAttributedString_endEditing__wrapper();

void MutableAttributedString_setAttribute__wrapper();

void MutableAttributedString_setCustomAttribute__wrapper();

void MutableAttributedString_getNormalAttributedString_REMOVEME__wrapper();

void MutableAttributedString_create__wrapper();

void MutableAttributedString_dispose__wrapper();

void Font_createCopyWithSymbolicTraits__wrapper();

void Font_getAscent__wrapper();

void Font_getDescent__wrapper();

void Font_getUnderlineThickness__wrapper();

void Font_getUnderlinePosition__wrapper();

void Font_createFromFile__wrapper();

void Font_createWithName__wrapper();

void Font_dispose__wrapper();

void Run_getAttributes__wrapper();

void Run_getCustomAttributes__wrapper();

void Run_getTypographicBounds__wrapper();

void Run_getStringRange__wrapper();

void Run_getStatus__wrapper();

void Run_dispose__wrapper();

void Line_getTypographicBounds__wrapper();

void Line_getBoundsWithOptions__wrapper();

void Line_draw__wrapper();

void Line_getGlyphRuns__wrapper();

void Line_getLineOffsetForStringIndex__wrapper();

void Line_createWithAttributedString__wrapper();

void Line_dispose__wrapper();

void Frame_draw__wrapper();

void Frame_getLines__wrapper();

void Frame_getLineOrigins__wrapper();

void Frame_dispose__wrapper();

void FrameSetter_createWithAttributedString__wrapper();

void FrameSetter_createFrame__wrapper();

void FrameSetter_dispose__wrapper();

void __constantsFunc();

int Drawing__register();
