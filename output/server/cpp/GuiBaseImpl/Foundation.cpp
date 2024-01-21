#include "generated/Foundation.h"
#include "deps/opendl/source/dlcf.h"

CFString makeConstantString(std::string s) {
    return (CFString)__dl_CFStringMakeConstantString(s.c_str());
}

CFString createWithString(std::string s) {
    return (CFString)dl_CFStringCreateWithCString(s.c_str());
}

URL createWithFileSystemPath(CFString path, URLPathStyle pathStyle, bool isDirectory) {
    return (URL)dl_CFURLCreateWithFileSystemPath((dl_CFStringRef)path, (dl_CFURLPathStyle)pathStyle, isDirectory);
}
