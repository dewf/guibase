#include "Drawing_wrappers.h"
#include "Text_wrappers.h"
#include "Keys_wrappers.h"
#include "Windowing_wrappers.h"

extern "C" int nativeLibraryInit() {
    Drawing::__register();
    Text::__register();
    Keys::__register();
    Windowing::__register();
    // should we do module inits here as well?
    // currently they are manually done on the C# side inside the <module>.Init methods (which perform registration first) - and those are individually called by Library.Init, which first calls nativeImplInit
    return 0;
}

extern "C" void nativeLibraryShutdown() {
    // module shutdowns? see note above
}
