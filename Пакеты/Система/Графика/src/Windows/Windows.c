Byte         *current_window;
Window_Class  current_window_class;
N_16         *current_window_instance;
Byte         *current_window_context;
//Canvas        current_canvas;
//Bitmap_Info   bitmap_info;


N_32 update_window_state(Byte *window, N_32 message, N_32 *parameters_1, Z_32 *parameters_2)
{
    Windows_Graphics *graphics;
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

        BeginPaint(window, &paint);
            SetDIBitsToDevice(
                graphics->context,
                0,
                0,
                graphics->graphics.width,
                graphics->graphics.height,
                0,
                0,
                0,
                graphics->graphics.height,
                graphics->graphics.data,
                &graphics->bitmap_info,
                0
            );
        EndPaint(window, &paint);
        return 0;
    }

    return DefWindowProcA(window, message, parameters_1, parameters_2);
}


procedure initialize_graphics (N_32 width, N_32 height, N_32 frames_per_second, procedure (*draw)())
{
    Windows_Message  message;
    N_32             sleep_time;

    memset(&current_window_class, 0, sizeof(Window_Class));

    current_window_class.structure_size   = sizeof(Window_Class);
    current_window_class.style            = UNIQUE_FOR_EACH_WINDOW_CONTEXT_CLASS_STYLE;
    current_window_class.window_procedure = update_window_state;
    current_window_class.icon             = LoadIconA(0, DEFAULT_ICON);
    current_window_class.cursor           = LoadCursorA(0, DEFAULT_ARROW);
    current_window_class.class_name       = "Main window class";
    current_window_class.small_icon       = LoadIconA(0, DEFAULT_ICON);

    RegisterClassExA(&current_window_class);

    current_window = CreateWindowExA(
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
        current_window_instance,
        0
    );

    ShowWindow(current_window, SHOW_MAXIMIZED_WINDOW);

    current_window_context = GetDC(current_window);
/*
    memset(&bitmap_info, 0, sizeof(Bitmap_Info));
    bitmap_info.header.size_of_structure = sizeof(Bitmap_Info_Header);
    bitmap_info.header.bit_count         = 32;
    bitmap_info.header.width             = width;
    bitmap_info.header.height            = height;
    bitmap_info.header.planes            = 1;
*/

/*
    initialize_canvas(&current_canvas, width, height, 4);
    sleep_time = 1000 / frames_per_second;

    for(;;)
    {
        if(PeekMessageA(&message, 0, 0, 0, REMOVED_FROM_QUEUE_MESSAGE))
        {
            if(message.message == QUIT_WINDOW_MESSAGE)
                break;
            else
            {
                TranslateMessage(&message);
                DispatchMessageA(&message);
            }
        }
        else
        {
            draw(&current_canvas);
            InvalidateRect(current_window, 0, 1);
            RedrawWindow(current_window, 0, 0, UPDATE_NOW);
            UpdateWindow(current_window);
            sleep_thread(sleep_time);
        }
    }*/
}


procedure _initialize_graphics (Windows_Graphics *graphics, N_32 width, N_32 height)
{
    graphics->graphics.width  = width;
    graphics->graphics.height = height;

    graphics->class.structure_size   = sizeof(Window_Class);
    graphics->class.style            = UNIQUE_FOR_EACH_WINDOW_CONTEXT_CLASS_STYLE;
    graphics->class.window_procedure = update_window_state;
    graphics->class.class            = 0;
    graphics->class.window           = 0;
    graphics->class.instance         = 0;
    graphics->class.icon             = LoadIconA(0, DEFAULT_ICON);
    graphics->class.cursor           = LoadCursorA(0, DEFAULT_ARROW);
    graphics->class.background       = 0;
    graphics->class.menu_name        = 0;
    graphics->class.class_name       = "Main window class";
    graphics->class.small_icon       = LoadIconA(0, DEFAULT_ICON);

    RegisterClassExA(&graphics->class);

    graphics->window = CreateWindowExA(
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
        graphics->class.instance,
        graphics
    );

    SetWindowLongA(graphics->window, USER_DATA, graphics);
    ShowWindow(graphics->window, SHOW_MAXIMIZED_WINDOW);
    graphics->context = GetDC(graphics->window);

    graphics->bitmap_info.header.size_of_structure                 = sizeof(Bitmap_Info_Header);
    graphics->bitmap_info.header.width                             = width;
    graphics->bitmap_info.header.height                            = height;
    graphics->bitmap_info.header.planes                            = 1;
    graphics->bitmap_info.header.bit_count                         = 32;
    graphics->bitmap_info.header.compression                       = 0;
    graphics->bitmap_info.header.size_image                        = 0;
    graphics->bitmap_info.header.x_pels_per_meter                  = 0;
    graphics->bitmap_info.header.y_pels_per_meter                  = 0;
    graphics->bitmap_info.header.number_of_color_indexes           = 0;
    graphics->bitmap_info.header.number_of_color_indexes_important = 0;

    graphics->bitmap_info.color[0]                                 = 0;

    graphics->graphics.data = malloc(width * height * 4);
}


procedure draw_graphics (Windows_Graphics *graphics)
{
    Windows_Message message;

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
        //draw(&current_canvas);
        InvalidateRect(graphics->window, 0, 1);
        RedrawWindow(graphics->window, 0, 0, UPDATE_NOW);
        UpdateWindow(graphics->window);
        //sleep_thread(sleep_time);
    }
}
