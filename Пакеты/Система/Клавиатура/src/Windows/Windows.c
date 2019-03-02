#include "Windows.h"


export Boolean pressed_key (Bit32 key_code)
{
    if(GetAsyncKeyState(key_code) & 0b1000000000000000)
        return 1;

    return 0;
}