#include "Drawing.h"
#include "Windowing.h"

#include <assert.h>

extern "C" int nativeLibraryInit() {
	// in dependency order if possible?
	assert(Drawing__init() == 0);
	assert(Windowing__init() == 0);
	return 0;
}

extern "C" void nativeLibraryShutdown() {
	Windowing__shutdown();
	Drawing__shutdown();
}
