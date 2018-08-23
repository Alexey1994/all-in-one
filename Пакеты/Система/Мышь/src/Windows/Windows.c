export function Boolean pressed_left_mouse_key ()
{
    if(GetAsyncKeyState(1) & 0b1000000000000000)
        return 1;

    return 0;
}


export function Boolean pressed_right_mouse_key ()
{
    if(GetAsyncKeyState(2) & 0b1000000000000000)
        return 1;

    return 0;
}


export function N_32 get_mouse_coord_x ()
{
    Windows_Point coords;

    GetCursorPos(&coords);
    return coords.x;
}


export function N_32 get_mouse_coord_y ()
{
    Windows_Point coords;

    GetCursorPos(&coords);
    return coords.y;
}