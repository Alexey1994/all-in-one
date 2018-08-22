#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED


typedef struct
{
    N_32 width;
    N_32 height;
    Byte *data;
}
Graphics;


//export procedure _initialize_graphics (Graphics *graphics, N_32 width, N_32 height);

export procedure initialize_graphics (N_32 width, N_32 height, N_32 frames_per_second, procedure (*draw)(Byte *data));


#endif // GRAPHICS_H_INCLUDED
