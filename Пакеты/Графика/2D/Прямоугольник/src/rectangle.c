#include <system.h>
#include "rectangle.h"


export procedure initialize_rectangle (Rectangle *rectangle, N_32 x, N_32 y, N_32 width, N_32 height)
{
    rectangle->x      = x;
    rectangle->y      = y;
    rectangle->width  = width;
    rectangle->height = height;
}


export function Boolean on_rectangle (Rectangle *rectangle, N_32 x, N_32 y)
{
    return x >= rectangle->x && x <= rectangle->x + rectangle->width &&
        y >= rectangle->y && y <= rectangle->y + rectangle->height;
}

/*
export function N_32 get_rectangle_x (Rectangle *rectangle)
{
    return rectangle->x;
}


export function N_32 get_rectangle_y (Rectangle *rectangle)
{
    return rectangle->y;
}


export procedure set_rectangle_x (Rectangle *rectangle, N_32 x)
{
    rectangle->x = x;
}


export procedure set_rectangle_y (Rectangle *rectangle, N_32 y)
{
    rectangle->y = y;
}
*/

export procedure draw_rectangle (Graphics *graphics, Rectangle *rectangle, N_32 color)
{
    N_32  x;
    N_32  y;
    N_32  rectangle_width;
    N_32  rectangle_height;
    N_32 *line;

    if(rectangle->x >= graphics->width || rectangle->y >= graphics->height)
        return;

    if(rectangle->x + rectangle->width < graphics->width)
        rectangle_width = rectangle->width;
    else
        rectangle_width = graphics->width - rectangle->x;

    if(rectangle->y + rectangle->height < graphics->height)
        rectangle_height = rectangle->height;
    else
        rectangle_height = graphics->height - rectangle->y;

    for(y = 0; y < rectangle_height; ++y)
    {
        line = graphics->data + (rectangle->y + y) * graphics->width + rectangle->x;

        for(x = 0; x < rectangle_width; ++x, ++line)
            *line = color;
    }
}


function N_32 main()
{
    Graphics graphics;
    Rectangle rectangle;

    GRAPHICS(1440, 900)
        loop
            gl_clear();

            initialize_rectangle(&rectangle, 100, 100, 100, 100);
            draw_rectangle(&graphics, &rectangle, 255 + (255 << 24));

            DRAW
        end
    END_GRAPHICS

    /*
    initialize_graphics(&graphics, 1440, 900);
    initialize_rectangle(&rectangle, 100, 100, 100, 100);
    draw_rectangle(&graphics, &rectangle, 255);

    for(;;)
        draw_graphics(&graphics);
*/
    return 0;
}
