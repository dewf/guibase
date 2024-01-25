#include "Foundation.h"

void CFString__push(CFString value);
CFString CFString__pop();

void URLPathStyle__push(URLPathStyle value);
URLPathStyle URLPathStyle__pop();

void URL__push(URL value);
URL URL__pop();

void CFString_makeConstant__wrapper();

void CFString_create__wrapper();

void CFString_dispose__wrapper();

void URL_createWithFileSystemPath__wrapper();

void URL_dispose__wrapper();

int Foundation__register();
