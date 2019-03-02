#include <system.h>
#include "display.h"


#ifdef __WIN32__
# include "Windows/Windows.c"
#endif

#ifdef __x86_32_bit__
# include "x86 32 bit/x86 32 bit.c"
#endif


Bit32 main()
{
    Bit32            i;
    Bit32            number_of_displays;
    Display_Settings settings;

    number_of_displays = get_number_of_displays();

    printf("number of displays: %d\n", number_of_displays);

    for(i = 0; i < number_of_displays; ++i)
    {
        get_display_settings(i, &settings);
        printf("width %d, height %d, frequency %d\n", settings.width, settings.height, settings.frequency);
    }

    set_display_settings(0, &settings);

    return 0;
}
