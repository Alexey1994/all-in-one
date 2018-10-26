#include <system.h>
#include "graphics.h"


#ifdef __WIN32__
# include "Windows/Windows.h"
#endif

#ifdef __x86_32_bit__
# include "x86 32 bit/x86 32 bit.h"
#endif


typedef struct
{
    N_32 x;
    N_32 y;
    N_32 width;
    N_32 height;
}
Rectangle;


procedure clear(Graphics *graphics)
{
    N_32 i;
    N_32 size = graphics->width * graphics->height;
    N_32 *data = graphics->data;

    for(i = 0; i < size; ++i)
        data[i] = 0;
}


procedure draw_rectangle(Rectangle *rectangle, Graphics *graphics)
{
    N_32  x;
    N_32  y;
    Byte *pixel;

    for(y=rectangle->y; y<rectangle->y + rectangle->height; ++y)
    {
        for(x=rectangle->x; x<rectangle->x + rectangle->width; ++x)
        {
            pixel = graphics->data + (graphics->width * y + x) * 4;
            pixel[0] = 255;
        }
    }
}


N_32 main()
{
    N_32 x = 0;
    N_32 y = 0;
    Rectangle rect;

    GRAPHICS(1440, 900)
        loop
            rect.x = 10 + x;//get_mouse_coord_x();
            rect.y = 10;//get_mouse_coord_y();
            rect.width = 800;
            rect.height = 800;

            //++x;
            x+=10;

            //clear_canvas(canvas);
            //set_canvas_color(canvas, 255, 0, 0, 255);
            clear(&graphics);
            draw_rectangle(&rect, &graphics);

            DRAW

            //if(!(x %= 30))
                //printf("frame");
        end
    END_GRAPHICS

    return 0;
}
