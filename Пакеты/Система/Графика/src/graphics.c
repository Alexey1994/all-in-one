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
            *pixel = 255;

            //get_canvas_pixel(canvas, x, y);
            //fill_canvas_pixel(canvas, pixel);
        }
    }
}

/*
procedure draw_rectangle(Rectangle *rectangle, Canvas *canvas)
{
    N_32  x;
    N_32  y;
    Byte *pixel;

    for(y=rectangle->y; y<rectangle->y + rectangle->height; ++y)
    {
        for(x=rectangle->x; x<rectangle->x + rectangle->width; ++x)
        {
            pixel = get_canvas_pixel(canvas, x, y);
            fill_canvas_pixel(canvas, pixel);
        }
    }
}
*/
/*
procedure draw_scene(Canvas *canvas)
{
    Rectangle rect;
    static N_32 x = 0;
    static N_32 y = 0;

    rect.x = 10 + x;//get_mouse_coord_x();
    rect.y = 10;//get_mouse_coord_y();
    rect.width = 100;
    rect.height = 100;
++x;
    clear_canvas(canvas);
    set_canvas_color(canvas, 255, 0, 0, 255);
    draw_rectangle(&rect, canvas);
}*/

procedure draw_scene()
{

}


N_32 main()
{
    //initialize_graphics(1440, 900, 120, &draw_scene);

    Windows_Graphics graphics;
    N_32 x = 0;
    N_32 y = 0;
    Rectangle rect;

    _initialize_graphics(&graphics, 1440, 900);

    for(;;)
    {
        rect.x = 10 + x;//get_mouse_coord_x();
        rect.y = 10;//get_mouse_coord_y();
        rect.width = 800;
        rect.height = 800;

        //++x;
        x+=10;

        //clear_canvas(canvas);
        //set_canvas_color(canvas, 255, 0, 0, 255);
        clear(&graphics.graphics);
        draw_rectangle(&rect, &graphics.graphics);

        draw_graphics(&graphics);

        //if(!(x %= 30))
            //printf("frame");
    }

    return 0;
}
