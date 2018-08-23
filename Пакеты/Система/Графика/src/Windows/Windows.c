N_32 update_window_state(Byte *window, N_32 message, N_32 *parameters_1, Z_32 *parameters_2)
{
    Graphics         *graphics;
    Windows_Graphics *system_graphics;
    Windows_Paint     paint;

    if(message == CLOSE_WINDOW_MESSAGE)
    {
        PostQuitMessage(0);
        return 0;
    }

    if(message == DESTROY_WINDOW_MESSAGE)
        return 0;

    if(message == PAINT_WINDOW_MESSAGE)
    {
        graphics = GetWindowLongA(window, USER_DATA);
        system_graphics = graphics->system_graphics;

        BeginPaint(window, &paint);
            SetDIBitsToDevice(
                system_graphics->context,
                0,
                0,
                graphics->width,
                graphics->height,
                0,
                0,
                0,
                graphics->height,
                graphics->data,
                &system_graphics->bitmap_info,
                0
            );
        EndPaint(window, &paint);
        return 0;
    }

    return DefWindowProcA(window, message, parameters_1, parameters_2);
}


export procedure initialize_graphics (Graphics *graphics, N_32 width, N_32 height)
{
    Windows_Graphics *system_graphics;

    system_graphics = allocate_memory(sizeof(Windows_Graphics));

    graphics->width  = width;
    graphics->height = height;
    graphics->data = allocate_memory(width * height * 4);
    graphics->system_graphics = system_graphics;

    system_graphics->class.structure_size   = sizeof(Window_Class);
    system_graphics->class.style            = UNIQUE_FOR_EACH_WINDOW_CONTEXT_CLASS_STYLE;
    system_graphics->class.window_procedure = update_window_state;
    system_graphics->class.class            = 0;
    system_graphics->class.window           = 0;
    system_graphics->class.instance         = 0;
    system_graphics->class.icon             = LoadIconA(0, DEFAULT_ICON);
    system_graphics->class.cursor           = LoadCursorA(0, DEFAULT_ARROW);
    system_graphics->class.background       = 0;
    system_graphics->class.menu_name        = 0;
    system_graphics->class.class_name       = "Main window class";
    system_graphics->class.small_icon       = LoadIconA(0, DEFAULT_ICON);

    RegisterClassExA(&system_graphics->class);

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

    SetWindowLongA(system_graphics->window, USER_DATA, graphics);
    ShowWindow(system_graphics->window, SHOW_MAXIMIZED_WINDOW);
    system_graphics->context = GetDC(system_graphics->window);

    system_graphics->bitmap_info.header.size_of_structure                 = sizeof(Bitmap_Info_Header);
    system_graphics->bitmap_info.header.width                             = width;
    system_graphics->bitmap_info.header.height                            = height;
    system_graphics->bitmap_info.header.planes                            = 1;
    system_graphics->bitmap_info.header.bit_count                         = 32;
    system_graphics->bitmap_info.header.compression                       = 0;
    system_graphics->bitmap_info.header.size_image                        = 0;
    system_graphics->bitmap_info.header.x_pels_per_meter                  = 0;
    system_graphics->bitmap_info.header.y_pels_per_meter                  = 0;
    system_graphics->bitmap_info.header.number_of_color_indexes           = 0;
    system_graphics->bitmap_info.header.number_of_color_indexes_important = 0;

    system_graphics->bitmap_info.color[0]                                 = 0;
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
        InvalidateRect(system_graphics->window, 0, 1);
        RedrawWindow(system_graphics->window, 0, 0, UPDATE_NOW);
        UpdateWindow(system_graphics->window);
    }
}


export procedure deinitialize_graphics (Graphics *graphics)
{
    free_memory(graphics->system_graphics);
    free_memory(graphics->data);
}
