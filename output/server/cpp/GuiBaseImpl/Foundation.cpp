#include "generated/Foundation.h"
#include "deps/opendl/source/dlcf.h"

CFString CFString_makeConstant(std::string s)
{
    return (CFString)__dl_CFStringMakeConstantString(s.c_str());
}

CFString CFString_create(std::string s)
{
    return (CFString)dl_CFStringCreateWithCString(s.c_str());
}

void CFString_dispose(CFString _this)
{
    dl_CFRelease(_this);
}

URL URL_createWithFileSystemPath(CFString path, URLPathStyle pathStyle, bool isDirectory)
{
    return (URL)dl_CFURLCreateWithFileSystemPath((dl_CFStringRef)path, (dl_CFURLPathStyle)pathStyle, isDirectory);
}

void URL_dispose(URL _this)
{
    dl_CFRelease(_this);
}
