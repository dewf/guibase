#include "generated/Drawing.h"
#include "deps/opendl/source/opendl.h"

const AffineTransform AffineTransformIdentity = *((AffineTransform*)&dl_CGAffineTransformIdentity);

FontDescriptorArray fontManagerCreateFontDescriptorsFromURL(URL fileUrl)
{
    return (FontDescriptorArray)dl_CTFontManagerCreateFontDescriptorsFromURL((dl_CFURLRef)fileUrl);
}

Font fontCreateWithFontDescriptor(FontDescriptor descriptor, double size, AffineTransform matrix)
{
    auto res = (Font)dl_CTFontCreateWithFontDescriptor((dl_CTFontDescriptorRef)descriptor, size, (dl_CGAffineTransform*)&matrix);
    printf("fontCreateWithFontDescriptor: [%p]\n", res);
    return res;
}

void DrawContext_saveGState(DrawContext _this) {
    dl_CGContextSaveGState((dl_CGContextRef)_this);
}

void DrawContext_restoreGState(DrawContext _this) {
    dl_CGContextRestoreGState((dl_CGContextRef)_this);
}

void DrawContext_setRGBFillColor(DrawContext _this, double red, double green, double blue, double alpha) {
    dl_CGContextSetRGBFillColor((dl_CGContextRef)_this, red, green, blue, alpha);
}

void DrawContext_fillRect(DrawContext _this, Rect rect) {
    dl_CGContextFillRect((dl_CGContextRef)_this, *((dl_CGRect*)&rect));
}

std::vector<FontDescriptor> FontDescriptorArray_items(FontDescriptorArray _this)
{
    auto arr = (dl_CFArrayRef)_this;
    std::vector<FontDescriptor> ret;
    for (int i = 0; i < dl_CFArrayGetCount(arr); i++) {
        auto fd = (dl_CTFontDescriptorRef)dl_CFArrayGetValueAtIndex(arr, i);
        ret.push_back((FontDescriptor)fd);
    }
    return ret;
}
