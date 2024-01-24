#include "../support/NativeImplServer.h"
#include "Foundation_wrappers.h"
#include "Foundation.h"


void CFString__push(CFString value) {
    ni_pushPtr(value);
}

CFString CFString__pop() {
    return (CFString)ni_popPtr();
}

void URL__push(URL value) {
    ni_pushPtr(value);
}

URL URL__pop() {
    return (URL)ni_popPtr();
}

inline void URLPathStyle__push(URLPathStyle value) {
    ni_pushInt32((int32_t)value);
}

inline URLPathStyle URLPathStyle__pop() {
    auto tag = ni_popInt32();
    return (URLPathStyle)tag;
}

void makeConstantString__wrapper() {
    auto s = popStringInternal();
    CFString__push(makeConstantString(s));
}

void createWithString__wrapper() {
    auto s = popStringInternal();
    CFString__push(createWithString(s));
}

void createWithFileSystemPath__wrapper() {
    auto path = CFString__pop();
    auto pathStyle = URLPathStyle__pop();
    auto isDirectory = ni_popBool();
    URL__push(createWithFileSystemPath(path, pathStyle, isDirectory));
}

void CFString_dispose__wrapper() {
    auto _this = CFString__pop();
    CFString_dispose(_this);
}

void URL_dispose__wrapper() {
    auto _this = URL__pop();
    URL_dispose(_this);
}

int Foundation__register() {
    auto m = ni_registerModule("Foundation");
    ni_registerModuleMethod(m, "makeConstantString", &makeConstantString__wrapper);
    ni_registerModuleMethod(m, "createWithString", &createWithString__wrapper);
    ni_registerModuleMethod(m, "createWithFileSystemPath", &createWithFileSystemPath__wrapper);
    ni_registerModuleMethod(m, "CFString_dispose", &CFString_dispose__wrapper);
    ni_registerModuleMethod(m, "URL_dispose", &URL_dispose__wrapper);
    return 0; // = OK
}
