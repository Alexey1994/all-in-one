#ifndef SYSTEM_GRAPHICS_H_INCLUDED
#define SYSTEM_GRAPHICS_H_INCLUDED


typedef struct
{
    Bit32 width;
    Bit32 height;
    Bit8* data;
    Bit8* system_graphics;
}
Graphics;


import void initialize_graphics   (Graphics* graphics, Bit32 width, Bit32 height);
import void draw_graphics         (Graphics* graphics);
import void deinitialize_graphics (Graphics* graphics);


#define GRAPHICS(width, height)\
{\
    Graphics graphics;\
    initialize_graphics(&graphics, (width), (height));

#define DRAW\
    draw_graphics(&graphics);

#define END_GRAPHICS\
    deinitialize_graphics(&graphics);\
}


#endif // SYSTEM_GRAPHICS_H_INCLUDED
