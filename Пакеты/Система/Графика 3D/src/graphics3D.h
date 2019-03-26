#ifndef SYSTEM_GRAPHICS3D_H_INCLUDED
#define SYSTEM_GRAPHICS3D_H_INCLUDED


typedef struct
{
    Bit32  width;
    Bit32  height;
    Bit32* data;
    Bit8*  system_graphics;
}
Graphics;


import void initialize_graphics   (Graphics* graphics, Bit32 width, Bit32 height, Boolean is_2D_graphics);
import void draw_graphics         (Graphics* graphics);
import void deinitialize_graphics (Graphics* graphics);

import void gl_clear();
import void gl_begin();
import void gl_color(float red, float green, float blue);
import void gl_vertex(float x, float y, float z);
import void gl_end();

import void gl_clear_view_matrix();

import void gl_scale(float x, float y, float z);
import void gl_rotate(float angle, float x, float y, float z);
import void gl_translate(float x, float y, float z);


#define GRAPHICS(width, height)\
{\
    Graphics graphics;\
    initialize_graphics(&graphics, (width), (height), 1);

#define GRAPHICS_3D(width, height)\
{\
    Graphics graphics;\
    initialize_graphics(&graphics, (width), (height), 0);

#define DRAW\
    draw_graphics(&graphics);

#define END_GRAPHICS\
    deinitialize_graphics(&graphics);\
}


#endif // SYSTEM_GRAPHICS3D_H_INCLUDED
