#pragma once

#include "../support/NativeImplServer.h"
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <set>

struct __CFString; typedef struct __CFString* CFString;
struct __URL; typedef struct __URL* URL;


enum class URLPathStyle {
    POSIX = 0,
    Windows = 2
};


CFString CFString_makeConstant(std::string s);
CFString CFString_create(std::string s);
void CFString_dispose(CFString _this);
URL URL_createWithFileSystemPath(CFString path, URLPathStyle pathStyle, bool isDirectory);
void URL_dispose(URL _this);
