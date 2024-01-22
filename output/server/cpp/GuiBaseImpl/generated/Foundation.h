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

CFString makeConstantString(std::string s);
CFString createWithString(std::string s);
URL createWithFileSystemPath(CFString path, URLPathStyle pathStyle, bool isDirectory);
void CFString_dispose(CFString _this);
void URL_dispose(URL _this);
