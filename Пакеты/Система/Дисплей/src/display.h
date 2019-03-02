#ifndef SYSTEM_DISPLAY_H_INCLUDED
#define SYSTEM_DISPLAY_H_INCLUDED

typedef struct
{
    Bit32 width;
    Bit32 height;
    Bit32 frequency;
}
Display_Settings;


import Bit32 get_number_of_displays ();
import void  get_display_settings   (Bit32 display_number, Display_Settings* settings);
import void  set_display_settings   (Bit32 display_number, Display_Settings* settings);


#endif // SYSTEM_DISPLAY_H_INCLUDED
