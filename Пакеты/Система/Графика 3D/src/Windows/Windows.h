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
    N_32            structure_size;
    N_32            style;
    function N_32 (*window_procedure)();
    N_32            class;
    Byte           *window;
    N_16           *instance;
    Icon           *icon;
    Cursor         *cursor;
    Brush          *background;
    Byte           *menu_name;
    Byte           *class_name;
    Icon           *small_icon;
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
    Byte          *window;
    N_32           message;
    N_32          *parameters1;
    Z_32          *parameters2;
    N_32           time;
    Windows_Point  point;
}
Windows_Message;

typedef struct
{
    N_16  size;
    N_16  nVersion;
    N_32  dwFlags;
    N_8   iPixelType;
    N_8   cColorBits;
    N_8   cRedBits;
    N_8   cRedShift;
    N_8   cGreenBits;
    N_8   cGreenShift;
    N_8   cBlueBits;
    N_8   cBlueShift;
    N_8   cAlphaBits;
    N_8   cAlphaShift;
    N_8   cAccumBits;
    N_8   cAccumRedBits;
    N_8   cAccumGreenBits;
    N_8   cAccumBlueBits;
    N_8   cAccumAlphaBits;
    N_8   cDepthBits;
    N_8   cStencilBits;
    N_8   cAuxBuffers;
    N_8   iLayerType;
    N_8   bReserved;
    N_32  dwLayerMask;
    N_32  dwVisibleMask;
    N_32  dwDamageMask;
}
Windows_Pixel_Format_Descriptor;


typedef struct
{
    Window_Class  class;
    Byte         *context;
    Byte         *window;
    Byte         *graphics_context;
}
Windows_Graphics;


import procedure          PostQuitMessage  (N_32 exit_code);
import function  N_32     DefWindowProcA   (Byte* window, N_32 message, N_16* parameter1, N_32* parameter2);
import function  Icon*    LoadIconA        (Byte* instance, Byte* icon_name);
import function  Cursor*  LoadCursorA      (Byte* instance, Byte* cursor_name);
import function  N_16     RegisterClassExA (Window_Class* class);
import function  N_32     ShowWindow       (Byte* window, N_32 options);
import function  N_32     SetWindowLongA   (Byte* window, N_32 field_index, N_32 value);
import function  N_32     GetWindowLongA   (Byte* window, N_32 field_index);
import function  Byte*    GetDC            (Byte* window);
import function  N_32     PeekMessageA     (Windows_Message* message, Byte* window, N_32 filter_min, N_32 filter_max, N_32 remove_message);
import function  Z_32     DispatchMessageA (Windows_Message* message);
import function  N_32     TranslateMessage (Windows_Message* message);

import function  Byte*   CreateWindowExA(
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

import function N_32 ChoosePixelFormat(Byte *context, Windows_Pixel_Format_Descriptor *format_descriptor);
import function Boolean SetPixelFormat(Byte *context, N_32 format, Windows_Pixel_Format_Descriptor *format_descriptor);

import function Byte* wglCreateContext(Byte* context);
import function Boolean wglDeleteContext(Byte* graphics_context);
import procedure wglSwapBuffers(Byte* context);

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

import procedure glDrawPixels(N_32 width, N_32 height, GL_Data_Format format, GL_Data_Type type, Byte* pixels);
import procedure glRasterPos2f(R_32 x, R_32 y);

import procedure glEnable(GL_Option option);
import procedure glBlendFunc(GL_Blend_Factor source_factor, GL_Blend_Factor destination_factor);

import procedure glColor3f(R_32 red, R_32 green, R_32 blue);
import procedure glVertex3f(R_32 x, R_32 y, R_32 z);
import procedure glBegin(GL_Begin_Mode mode);
import procedure glEnd();
import procedure glClear(GL_Clear_Mode mode);
import procedure glClearColor(R_32 red, R_32 green, R_32 blue, R_32 alpha);


#include "Windows.c"
