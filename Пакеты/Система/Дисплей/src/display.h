#ifndef SYSTEM_DISPLAY_H_INCLUDED
#define SYSTEM_DISPLAY_H_INCLUDED

typedef struct
{
    N_32 width;
    N_32 height;
    N_32 frequency;
}
Display_Settings;


import function  N_32 get_number_of_displays ();
import procedure      get_display_settings (N_32 display_number, Display_Settings *settings);
import procedure      set_display_settings (N_32 display_number, Display_Settings *settings);


#endif // SYSTEM_DISPLAY_H_INCLUDED
