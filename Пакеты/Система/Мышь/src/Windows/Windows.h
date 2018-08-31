typedef struct
{
    Z_32 x;
    Z_32 y;
}
Windows_Point;


import function N_32 GetAsyncKeyState (N_32 key);
import function N_32 GetCursorPos     (Windows_Point *coords);


#include "Windows.c"
