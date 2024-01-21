#include "Drawing.h"

void AffineTransform__push(AffineTransform value, bool isReturn);
AffineTransform AffineTransform__pop();

void Point__push(Point value, bool isReturn);
Point Point__pop();

void Size__push(Size value, bool isReturn);
Size Size__pop();

void Rect__push(Rect value, bool isReturn);
Rect Rect__pop();

void DrawContext__push(DrawContext value);
DrawContext DrawContext__pop();

void Font__push(Font value);
Font Font__pop();

void FontDescriptor__push(FontDescriptor value);
FontDescriptor FontDescriptor__pop();

void FontDescriptorArray__push(FontDescriptorArray value);
FontDescriptorArray FontDescriptorArray__pop();

void fontManagerCreateFontDescriptorsFromURL__wrapper();

void fontCreateWithFontDescriptor__wrapper();

void DrawContext_saveGState__wrapper();

void DrawContext_restoreGState__wrapper();

void DrawContext_setRGBFillColor__wrapper();

void DrawContext_fillRect__wrapper();

void FontDescriptorArray_items__wrapper();

void __constantsFunc();

int Drawing__register();
