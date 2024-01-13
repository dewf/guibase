#include "CGContext.h"

#include <d2d1_1.h>
#include <dwrite.h>
#include <wincodec.h> // for IWICBitmap stuff

#include "../common/comstuff.h"

static ID2D1Factory1* d2dFactory = nullptr;
static IDWriteFactory* writeFactory = nullptr;
static IWICImagingFactory* wicFactory = nullptr;

void CGContext2::setRGBFillColor(double red, double green, double blue, double alpha)
{
	// TODO
}

void CGContext2::fillRect(Rect rect)
{
	// TODO
}

void CGContext2::init()
{
	HR(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2dFactory));
	HR(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&writeFactory)));
	HR(CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory));
}

void CGContext2::shutdown()
{
	SafeRelease(&wicFactory);
	SafeRelease(&writeFactory);
	SafeRelease(&d2dFactory);
}

ID2D1Factory1* CGContext2::getFactory()
{
	return d2dFactory;
}
