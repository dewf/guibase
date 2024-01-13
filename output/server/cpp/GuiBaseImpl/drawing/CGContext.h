#pragma once

#include "../generated/Drawing.h"

#include <d2d1_1.h>

class CGContext2 : public ServerCGContext {
public:
	// implementations
	void setRGBFillColor(double red, double green, double blue, double alpha) override;
	void fillRect(Rect rect) override;

	// static stuff
	static void init();
	static void shutdown();
	static ID2D1Factory1* getFactory();
};
