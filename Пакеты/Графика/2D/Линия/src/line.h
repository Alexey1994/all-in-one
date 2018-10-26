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


#define LINE(x1, y1, x2, y2)\
{\
    Line line;\
    initialize_line(&line, (x1), (y1), (x2), (y2));

#define DRAW_LINE(color)\
    draw_line(&graphics, &line, (color));

#define END_LINE }


#endif // GRAPHICS_LINE_H_INCLUDED
