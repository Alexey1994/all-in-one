#ifndef SYSTEM_GRAPHICS_H_INCLUDED
#define SYSTEM_GRAPHICS_H_INCLUDED


typedef struct
{
    N_32 width;
    N_32 height;
    Byte *data;
    Byte *system_graphics;
}
Graphics;


import procedure initialize_graphics   (Graphics *graphics, N_32 width, N_32 height);
import procedure draw_graphics         (Graphics *graphics);
import procedure deinitialize_graphics (Graphics *graphics);


#define GRAPHICS(width, height)\
{\
    Graphics graphics;\
    initialize_graphics(&graphics, (width), (height));

#define END_GRAPHICS\
    deinitialize_graphics(&graphics);\
}


#endif // SYSTEM_GRAPHICS_H_INCLUDED
