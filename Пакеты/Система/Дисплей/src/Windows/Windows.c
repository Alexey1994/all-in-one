#include "Windows.h"
#include <memory.h>


//https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-enumdisplaydevicesa
import function Boolean EnumDisplayDevicesA (Byte *name, N_32 display_number, Dispaly *display, N_32 flags);

//https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-enumdisplaysettingsa
//http://jasinskionline.com/windowsapi/ref/e/enumdisplaysettings.html
import function Boolean EnumDisplaySettingsA (Dispaly *display, N_32 mode, Dispaly_Mode *display_mode);

//https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-changedisplaysettingsa
import function N_32 ChangeDisplaySettingsA (Dispaly_Mode *display_mode, N_32 flags);


export function N_32 get_number_of_displays ()
{
    Dispaly display;
    N_32    status;
    N_32    i;
    N_32    number_of_displays;

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

function N_32 get_display_mode(N_32 display_number, Dispaly_Mode *display_mode)
{
    Dispaly display;
    N_32    status;
    N_32    current_display_number;
    N_32    i;

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


export procedure get_display_settings (N_32 display_number, Display_Settings *settings)
{
    Dispaly_Mode display_mode;

    get_display_mode(display_number, &display_mode);

    settings->width     = display_mode.width;
    settings->height    = display_mode.height;
    settings->frequency = display_mode.frequency;
}


export procedure set_display_settings (N_32 display_number, Display_Settings *settings)
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