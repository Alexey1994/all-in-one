#include "Windows.h"
#include <memory.h>


//https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-enumdisplaydevicesa
import Boolean EnumDisplayDevicesA (Bit8* name, Bit32 display_number, Dispaly* display, Bit32 flags);

//https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-enumdisplaysettingsa
//http://jasinskionline.com/windowsapi/ref/e/enumdisplaysettings.html
import Boolean EnumDisplaySettingsA (Dispaly* display, Bit32 mode, Dispaly_Mode* display_mode);

//https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-changedisplaysettingsa
import Bit32 ChangeDisplaySettingsA (Dispaly_Mode* display_mode, Bit32 flags);


export Bit32 get_number_of_displays ()
{
    Dispaly display;
    Bit32   status;
    Bit32   i;
    Bit32   number_of_displays;

    display.structure_size = sizeof(Dispaly);

    for(i = 0, number_of_displays = 0; ; ++i)
    {
        status = EnumDisplayDevicesA(0, i, &display, 0);

        if(!status)
            return number_of_displays;

        if(display.state & DISPLAY_IS_ATTACHED_TO_DESKTOP)
            ++number_of_displays;
    }

    return number_of_displays;
}

Bit32 get_display_mode (Bit32 display_number, Dispaly_Mode* display_mode)
{
    Dispaly display;
    Bit32   status;
    Bit32   current_display_number;
    Bit32   i;

    display.structure_size = sizeof(Dispaly);

    for(i = 0, current_display_number = 0; ; ++i)
    {
        status = EnumDisplayDevicesA(0, i, &display, 0);

        if(!status)
            goto error;

        if(display.state & DISPLAY_IS_ATTACHED_TO_DESKTOP)
        {
            if(current_display_number == display_number)
                break;

            ++current_display_number;
        }
    }

    status = EnumDisplaySettingsA(display.device_name, -1, display_mode);

    return 1;

error:
    return 0;
}


export void get_display_settings (Bit32 display_number, Display_Settings* settings)
{
    Dispaly_Mode display_mode;

    get_display_mode(display_number, &display_mode);

    settings->width     = display_mode.width;
    settings->height    = display_mode.height;
    settings->frequency = display_mode.frequency;
}


export void set_display_settings (Bit32 display_number, Display_Settings* settings)
{
    Dispaly_Mode display_mode;

    clear_memory(&display_mode, sizeof(Dispaly_Mode));

    display_mode.structure_size = sizeof(Dispaly_Mode);
    display_mode.width          = settings->width;
    display_mode.height         = settings->height;
    display_mode.frequency      = settings->frequency;
    display_mode.fields         = DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

    ChangeDisplaySettingsA(&display_mode, CDS_UPDATEREGISTRY | CDS_RESET);
}