#pragma once
#include "Keys.h"

namespace Keys
{

    void KeyLocation__push(KeyLocation value);
    KeyLocation KeyLocation__pop();

    void Key__push(Key value);
    Key Key__pop();

    int __register();
}
