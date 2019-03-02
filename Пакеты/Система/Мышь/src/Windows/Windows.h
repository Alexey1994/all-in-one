typedef struct
{
    Bit32 x;
    Bit32 y;
}
Windows_Point;


import Bit32 GetAsyncKeyState (Bit32 key);
import Bit32 GetCursorPos     (Windows_Point* coords);


#include "Windows.c"
