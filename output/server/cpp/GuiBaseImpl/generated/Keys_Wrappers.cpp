#include "../support/NativeImplServer.h"
#include "Keys_wrappers.h"
#include "Keys.h"

namespace Keys
{
    void KeyLocation__push(KeyLocation value) {
        ni_pushInt32((int32_t)value);
    }

    KeyLocation KeyLocation__pop() {
        auto tag = ni_popInt32();
        return (KeyLocation)tag;
    }
    void Key__push(Key value) {
        ni_pushInt32((int32_t)value);
    }

    Key Key__pop() {
        auto tag = ni_popInt32();
        return (Key)tag;
    }

    int __register() {
        auto m = ni_registerModule("Keys");
        return 0; // = OK
    }
}
