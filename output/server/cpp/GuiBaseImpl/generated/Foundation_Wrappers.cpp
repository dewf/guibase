#include "../support/NativeImplServer.h"
#include "Foundation_wrappers.h"
#include "Foundation.h"


void CFString__push(CFString value) {
    ni_pushPtr(value);
}

CFString CFString__pop() {
    return (CFString)ni_popPtr();
}

inline void URLPathStyle__push(URLPathStyle value) {
    ni_pushInt32((int32_t)value);
}

inline URLPathStyle URLPathStyle__pop() {
    auto tag = ni_popInt32();
    return (URLPathStyle)tag;
}

void URL__push(URL value) {
    ni_pushPtr(value);
}

URL URL__pop() {
    return (URL)ni_popPtr();
}

void CFString_makeConstant__wrapper() {
    auto s = popStringInternal();
    CFString__push(CFString_makeConstant(s));
}

void CFString_create__wrapper() {
    auto s = popStringInternal();
    CFString__push(CFString_create(s));
}

void CFString_dispose__wrapper() {
    auto _this = CFString__pop();
    CFString_dispose(_this);
}

void URL_createWithFileSystemPath__wrapper() {
    auto path = CFString__pop();
    auto pathStyle = URLPathStyle__pop();
    auto isDirectory = ni_popBool();
    URL__push(URL_createWithFileSystemPath(path, pathStyle, isDirectory));
}

void URL_dispose__wrapper() {
    auto _this = URL__pop();
    URL_dispose(_this);
}

int Foundation__register() {
    auto m = ni_registerModule("Foundation");
    ni_registerModuleMethod(m, "CFString_makeConstant", &CFString_makeConstant__wrapper);
    ni_registerModuleMethod(m, "CFString_create", &CFString_create__wrapper);
    ni_registerModuleMethod(m, "CFString_dispose", &CFString_dispose__wrapper);
    ni_registerModuleMethod(m, "URL_createWithFileSystemPath", &URL_createWithFileSystemPath__wrapper);
    ni_registerModuleMethod(m, "URL_dispose", &URL_dispose__wrapper);
    return 0; // = OK
}
