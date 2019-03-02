#include "Windows.h"


N_32 update_window_state(Byte *window, N_32 message, N_32 *parameters_1, Z_32 *parameters_2)
{
    if(message == CLOSE_WINDOW_MESSAGE)
    {
        PostQuitMessage(0);
        return 0;
    }

    if(message == DESTROY_WINDOW_MESSAGE)
        return 0;
/*
    if(message == PAINT_WINDOW_MESSAGE)
    {
        return 0;
    }
*/
    return DefWindowProcA(window, message, parameters_1, parameters_2);
}


void EnableOpenGL(Byte *window, Byte *hDC, Byte* hRC)
{
    Windows_Pixel_Format_Descriptor pfd;

    int iFormat;

    *hDC = GetDC(window);

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    *hRC = wglCreateContext(*hDC);
    wglMakeCurrent(*hDC, *hRC);
}


export procedure initialize_graphics (Graphics *graphics, N_32 width, N_32 height)
{
    Windows_Graphics*               system_graphics;
    N_32                            status;
    Windows_Pixel_Format_Descriptor pixel_format_descriptor;
    N_32                            pixel_format;

    system_graphics = allocate_memory(sizeof(Windows_Graphics));

    graphics->width  = width;
    graphics->height = height;
    graphics->data = allocate_memory(width * height * 4);
    graphics->system_graphics = system_graphics;

    system_graphics->class.structure_size   = sizeof(Window_Class);
    system_graphics->class.style            = UNIQUE_FOR_EACH_WINDOW_CONTEXT_CLASS_STYLE;
    system_graphics->class.window_procedure = &update_window_state;
    system_graphics->class.class            = 0;
    system_graphics->class.window           = 0;
    system_graphics->class.instance         = 0;
    system_graphics->class.icon             = LoadIconA(0, DEFAULT_ICON);
    system_graphics->class.cursor           = LoadCursorA(0, DEFAULT_ARROW);
    system_graphics->class.background       = 0;
    system_graphics->class.menu_name        = 0;
    system_graphics->class.class_name       = "Main window class";
    system_graphics->class.small_icon       = LoadIconA(0, DEFAULT_ICON);

    status = RegisterClassExA(&system_graphics->class);

    if(!status)
    {
        printf("error RegisterClassExA %d\n", GetLastError());
        goto error;
    }

    system_graphics->window = CreateWindowExA(
        0,
        "Main window class",
        "Window",
        POPUP_WINDOW_STYLE,
        0,
        0,
        width,
        height,
        0,
        0,
        system_graphics->class.instance,
        0
    );

    if(!system_graphics->window)
    {
        printf("error CreateWindowExA %d\n", GetLastError());
        goto error;
    }

    SetWindowLongA(system_graphics->window, USER_DATA, graphics);
    ShowWindow(system_graphics->window, SHOW_MAXIMIZED_WINDOW);
    system_graphics->context = GetDC(system_graphics->window);

    pixel_format_descriptor.size = sizeof(Windows_Pixel_Format_Descriptor);
    pixel_format_descriptor.nVersion = 0;
    pixel_format_descriptor.dwFlags = 0;
    pixel_format_descriptor.iPixelType = 0;
    pixel_format_descriptor.cColorBits = 0;
    pixel_format_descriptor.cRedBits = 0;
    pixel_format_descriptor.cRedShift = 0;
    pixel_format_descriptor.cGreenBits = 0;
    pixel_format_descriptor.cGreenShift = 0;
    pixel_format_descriptor.cBlueBits = 0;
    pixel_format_descriptor.cBlueShift = 0;
    pixel_format_descriptor.cAlphaBits = 0;
    pixel_format_descriptor.cAlphaShift = 0;
    pixel_format_descriptor.cAccumBits = 0;
    pixel_format_descriptor.cAccumRedBits = 0;
    pixel_format_descriptor.cAccumGreenBits = 0;
    pixel_format_descriptor.cAccumBlueBits = 0;
    pixel_format_descriptor.cAccumAlphaBits = 0;
    pixel_format_descriptor.cDepthBits = 0;
    pixel_format_descriptor.cStencilBits = 0;
    pixel_format_descriptor.cAuxBuffers = 0;
    pixel_format_descriptor.iLayerType = 0;
    pixel_format_descriptor.bReserved = 0;
    pixel_format_descriptor.dwLayerMask = 0;
    pixel_format_descriptor.dwVisibleMask = 0;
    pixel_format_descriptor.dwDamageMask = 0;

    pixel_format = ChoosePixelFormat(system_graphics->context, &pixel_format_descriptor);
    SetPixelFormat(system_graphics->context, pixel_format, &pixel_format_descriptor);

    system_graphics->graphics_context = wglCreateContext(system_graphics->context);

    if(!system_graphics->graphics_context)
    {
        printf("error in wglCreateContext %d", GetLastError());
        goto error;
    }

    wglMakeCurrent(system_graphics->context, system_graphics->graphics_context);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return;

error:
    //free_memory(graphics->data);
    //free_memory(system_graphics);
}


export procedure draw_graphics (Graphics *graphics)
{
    Windows_Message message;
    Windows_Graphics *system_graphics;

    system_graphics = graphics->system_graphics;

    if(PeekMessageA(&message, 0, 0, 0, REMOVED_FROM_QUEUE_MESSAGE))
    {
        if(message.message == QUIT_WINDOW_MESSAGE)
            ;//break;
        else
        {
            TranslateMessage(&message);
            DispatchMessageA(&message);
        }
    }
    else
    {
        //InvalidateRect(system_graphics->window, 0, 1);
        //RedrawWindow(system_graphics->window, 0, 0, UPDATE_NOW);
        //UpdateWindow(system_graphics->window);

        wglSwapBuffers(system_graphics->context);
    }
}


export procedure deinitialize_graphics (Graphics *graphics)
{
    free_memory(graphics->system_graphics);
    free_memory(graphics->data);
}
