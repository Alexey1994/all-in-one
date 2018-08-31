#ifndef GRAPHICS_LINE_H_INCLUDED
#define GRAPHICS_LINE_H_INCLUDED


#include <system/graphics.h>


typedef struct
{
    N_32 x1;
    N_32 y1;
    N_32 x2;
    N_32 y2;
}
Line;


import procedure initialize_line (Line *line, N_32 x1, N_32 y1, N_32 x2, N_32 y2);
import procedure draw_line       (Graphics *graphics, Line *line, N_32 color);


#endif // GRAPHICS_LINE_H_INCLUDED
