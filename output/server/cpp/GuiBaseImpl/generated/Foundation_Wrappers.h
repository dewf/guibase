#include "Foundation.h"

void CFString__push(CFString value);
CFString CFString__pop();

void URL__push(URL value);
URL URL__pop();

void URLPathStyle__push(URLPathStyle value);
URLPathStyle URLPathStyle__pop();

void makeConstantString__wrapper();

void createWithString__wrapper();

void createWithFileSystemPath__wrapper();

void CFString_dispose__wrapper();

void URL_dispose__wrapper();

int Foundation__register();
