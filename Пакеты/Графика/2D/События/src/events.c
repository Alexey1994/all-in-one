#include <system.h>
#include "events.h"


Byte *pressed_border_id = 0;


export function Boolean is_hover (Byte *border, function Boolean (*on_border)(Byte *border, N_32 x, N_32 y))
{
    if(!pressed_border_id || border == pressed_border_id)
        return on_border(border, get_mouse_coord_x(), get_mouse_coord_y());

    return 0;
}


export function Boolean pressed (Byte *border, function Boolean (*on_border)(Byte *border, N_32 x, N_32 y))
{
    if(pressed_left_mouse_key() && (!border || border == pressed_border_id))
        return on_border(border, get_mouse_coord_x(), get_mouse_coord_y());

    return 0;
}


export function Boolean clicked (Byte *border, function Boolean (*on_border)(Byte *border, N_32 x, N_32 y))
{
    if(!on_border(border, get_mouse_coord_x(), get_mouse_coord_y()))
    {
        if(border == pressed_border_id)
            pressed_border_id = 0;

        pressed_left_mouse_key();
        return 0;
    }

    if(pressed_left_mouse_key())
    {
        if(on_border(border, get_mouse_coord_x(), get_mouse_coord_y()))
        {
            if(!pressed_border_id)
                pressed_border_id = border;
        }
    }
    else if(border == pressed_border_id)
    {
        pressed_border_id = 0;
        return 1;
    }

    return 0;
}


export function Boolean move_if_moved(
    Byte              *border,
    function Boolean (*on_border)(Byte *border, N_32 x, N_32 y),
    function N_32    (*get_border_x)(Byte *border),
    function N_32    (*get_border_y)(Byte *border),
    procedure        (*set_border_x)(Byte *border, N_32 x),
    procedure        (*set_border_y)(Byte *border, N_32 y)
)
{
    static Z_32 pressed_width;
    static Z_32 pressed_height;

    if(pressed_border_id && border != pressed_border_id)
        return 0;

    if(pressed_left_mouse_key())
    {
        if(!pressed_border_id)
        {
            if(on_border(border, get_mouse_coord_x(), get_mouse_coord_y()))
            {
                pressed_border_id = border;
                pressed_width  = get_mouse_coord_x() - get_border_x(border);
                pressed_height = get_mouse_coord_y() - get_border_y(border);
            }
        }
        else
        {
            set_border_x(border, get_mouse_coord_x() - pressed_width);
            set_border_y(border, get_mouse_coord_y() - pressed_height);
        }
    }
    else if(border == pressed_border_id)
    {
        pressed_border_id = 0;
        return 1;
    }

    return 0;
}


function N_32 main()
{
    return 0;
}