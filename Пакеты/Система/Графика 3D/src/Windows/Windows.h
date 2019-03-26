#include <system/memory.h>

#define UNIQUE_FOR_EACH_WINDOW_CONTEXT_CLASS_STYLE  32

#define CLOSE_WINDOW_MESSAGE                        16
#define DESTROY_WINDOW_MESSAGE                      2
#define PAINT_WINDOW_MESSAGE                        15
#define ERASE_BACKGROUND_MESSAGE                    20

#define DEFAULT_ICON                                32512
#define DEFAULT_ARROW                               32512

#define POPUP_WINDOW_STYLE                          0x80000000
#define SHOW_MAXIMIZED_WINDOW                       3

#define REMOVED_FROM_QUEUE_MESSAGE                  1
#define QUIT_WINDOW_MESSAGE                         0x0012
#define UPDATE_NOW                                  256

#define USER_DATA                                   -21


//wingdi.h
#define PFD_DRAW_TO_WINDOW  4
#define PFD_SUPPORT_OPENGL  32
#define PFD_DOUBLEBUFFER    1
#define PFD_TYPE_RGBA   0
#define PFD_MAIN_PLANE  0


typedef struct
{

}
Icon;

typedef struct
{

}
Cursor;

typedef struct
{

}
Brush;

typedef struct
{
    Bit32            structure_size;
    Bit32            style;
    function Bit32 (*window_procedure)();
    Bit32            class;
    Bit8*            window;
    Bit16*           instance;
    Icon*            icon;
    Cursor*          cursor;
    Brush*           background;
    Bit8*            menu_name;
    Bit8*            class_name;
    Icon*            small_icon;
}
Window_Class;

typedef struct
{
    Z_32 left;
    Z_32 top;
    Z_32 right;
    Z_32 botom;
}
Windows_Rectangle;
/*
typedef struct
{
    Byte              *context;
    Z_32               erase_background;
    Windows_Rectangle  rectangle;
    Z_32               restore;
    Z_32               update;
    Byte               color[32];
}
Windows_Paint;
*/
typedef struct
{
    Z_32 x;
    Z_32 y;
}
Windows_Point;

typedef struct
{
    Bit8*          window;
    Bit32          message;
    Bit32*         parameters1;
    Bit32*         parameters2;
    Bit32          time;
    Windows_Point  point;
}
Windows_Message;

typedef struct
{
    Bit16  size;
    Bit16  nVersion;
    Bit32  dwFlags;
    Bit8   iPixelType;
    Bit8   cColorBits;
    Bit8   cRedBits;
    Bit8   cRedShift;
    Bit8   cGreenBits;
    Bit8   cGreenShift;
    Bit8   cBlueBits;
    Bit8   cBlueShift;
    Bit8   cAlphaBits;
    Bit8   cAlphaShift;
    Bit8   cAccumBits;
    Bit8   cAccumRedBits;
    Bit8   cAccumGreenBits;
    Bit8   cAccumBlueBits;
    Bit8   cAccumAlphaBits;
    Bit8   cDepthBits;
    Bit8   cStencilBits;
    Bit8   cAuxBuffers;
    Bit8   iLayerType;
    Bit8   bReserved;
    Bit32  dwLayerMask;
    Bit32  dwVisibleMask;
    Bit32  dwDamageMask;
}
Windows_Pixel_Format_Descriptor;


typedef struct
{
    Window_Class  class;
    Bit8*         context;
    Bit8*         window;
    Bit8*         graphics_context;
}
Windows_Graphics;


import void     PostQuitMessage  (N_32 exit_code);
import N_32     DefWindowProcA   (Byte* window, N_32 message, N_16* parameter1, N_32* parameter2);
import Icon*    LoadIconA        (Byte* instance, Byte* icon_name);
import Cursor*  LoadCursorA      (Byte* instance, Byte* cursor_name);
import N_16     RegisterClassExA (Window_Class* class);
import N_32     ShowWindow       (Byte* window, N_32 options);
import N_32     SetWindowLongA   (Byte* window, N_32 field_index, N_32 value);
import N_32     GetWindowLongA   (Byte* window, N_32 field_index);
import Byte*    GetDC            (Byte* window);
import N_32     PeekMessageA     (Windows_Message* message, Byte* window, N_32 filter_min, N_32 filter_max, N_32 remove_message);
import Z_32     DispatchMessageA (Windows_Message* message);
import N_32     TranslateMessage (Windows_Message* message);

import Byte* CreateWindowExA(
    N_32 extended_style,
    Byte *class_name,
    Byte *window_name,
    N_32 style,
    Z_32 x,
    Z_32 y,
    Z_32 width,
    Z_32 height,
    Byte *parent_window,
    Byte *menu,
    Byte *instance,
    N_32 *parameters
);

import N_32    ChoosePixelFormat(Byte *context, Windows_Pixel_Format_Descriptor *format_descriptor);
import Boolean SetPixelFormat(Byte *context, N_32 format, Windows_Pixel_Format_Descriptor *format_descriptor);

import Byte*   wglCreateContext(Byte* context);
import Boolean wglDeleteContext(Byte* graphics_context);
import void    wglSwapBuffers(Byte* context);

typedef enum
{
    GL_COLOR_BUFFER_BIT = 0x00004000
}
GL_Clear_Mode;

typedef enum
{
    GL_TRIANGLES = 0x0004
}
GL_Begin_Mode;

typedef enum
{
    GL_RGBA = 0x1908,
    GL_BGRA = 0x80E1
}
GL_Data_Format;

typedef enum
{
    GL_UNSIGNED_BYTE = 0x1401
}
GL_Data_Type;

typedef enum
{
    GL_BLEND = 0x0BE2
}
GL_Option;

typedef enum
{
    GL_SRC_ALPHA           = 0x0302,
    GL_ONE_MINUS_SRC_ALPHA = 0x0303
}
GL_Blend_Factor;

typedef enum
{
    GL_MODELVIEW = 0x1700
}
GL_Matrix_Mode;

import void glDrawPixels (N_32 width, N_32 height, GL_Data_Format format, GL_Data_Type type, Byte* pixels);
import void glRasterPos2f (R_32 x, R_32 y);

import void glEnable (GL_Option option);
import void glBlendFunc (GL_Blend_Factor source_factor, GL_Blend_Factor destination_factor);

import void glColor3f (R_32 red, R_32 green, R_32 blue);
import void glVertex3f (R_32 x, R_32 y, R_32 z);
import void glBegin (GL_Begin_Mode mode);
import void glEnd ();
import void glClear (GL_Clear_Mode mode);
import void glClearColor (R_32 red, R_32 green, R_32 blue, R_32 alpha);

import void glMatrixMode(GL_Matrix_Mode mode);
import void glLoadIdentity();
import void glPushMatrix();
import void glPopMatrix();
import void glLoadMatrixf(R_32* matrix);

import void glTranslatef (R_32 x, R_32 y, R_32 z);
import void glScalef (R_32 x, R_32 y, R_32 z);
import void glRotatef (R_32 angle, R_32 x, R_32 y, R_32 z);