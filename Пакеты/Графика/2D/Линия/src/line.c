#include <system.h>
#include "line.h"


export procedure initialize_line (Line *line, N_32 x1, N_32 y1, N_32 x2, N_32 y2)
{
    line->x1 = x1;
    line->y1 = y1;
    line->x2 = x2;
    line->y2 = y2;
}


export procedure draw_line (Graphics *graphics, Line *line, N_32 color)
{
    N_32 line_length;
    N_32 tail_length;
    N_32 number_of_tails;
    N_32 delta_x;
    N_32 delta_y;

    N_32 i;
    N_32 j;
    N_32 x;
    N_32 y;

    N_32 *screen;

    screen = graphics->data;

    delta_x = line->x2 - line->x1;
    delta_y = line->y2 - line->y1;

    if(delta_y < delta_x)
    {
        line_length = delta_x;
        number_of_tails = delta_y + 1;
        tail_length = line_length / number_of_tails;

        x = line->x1;
        y = line->y1;

        for(i = 0; i < number_of_tails; ++i)
        {
            for(j = 0; j < tail_length; ++j)
            {
                screen[(graphics->height - y) * graphics->width + x] = color;
                ++x;
            }

            ++y;
        }

        while(x < line->x2)
        {
            screen[(graphics->height - y) * graphics->width + x] = color;
            ++x;
        }
    }
}


#include <system/mouse.h>


procedure clear (Graphics *graphics)
{
    N_32 i;

    N_32 *screen;

    screen = graphics->data;

    for(i = 0; i < graphics->height * graphics->width; ++i)
        screen[i] = 0;
}


function N_32 main()
{
    GRAPHICS(1440, 900)
        loop
            LINE(10, 10, get_mouse_coord_x(), get_mouse_coord_y())
                DRAW_LINE(255)
            END_LINE

            DRAW
        end
    END_GRAPHICS

    return 0;
}
