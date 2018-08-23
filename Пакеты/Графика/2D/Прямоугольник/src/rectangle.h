#ifndef GRAPHICS_RECTANGLE_H_INCLUDED
#define GRAPHICS_RECTANGLE_H_INCLUDED


#include <system/graphics.h>


typedef struct
{
    N_32 x;
    N_32 y;
    N_32 width;
    N_32 height;
}
Rectangle;


import procedure            initialize_rectangle (Rectangle *rectangle, N_32 x, N_32 y, N_32 width, N_32 height);

import function  Boolean    on_rectangle         (Rectangle *rectangle, N_32 x, N_32 y);
//import function  N_32       get_rectangle_x      (Rectangle *rectangle);
//import function  N_32       get_rectangle_y      (Rectangle *rectangle);
//import procedure            set_rectangle_x      (Rectangle *rectangle, N_32 x);
//import procedure            set_rectangle_y      (Rectangle *rectangle, N_32 y);

import procedure            draw_rectangle       (Graphics *graphics, Rectangle *rectangle, N_32 color);


#endif // GRAPHICS_RECTANGLE_H_INCLUDED
