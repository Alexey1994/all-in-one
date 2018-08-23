#include <system.h>


#ifdef __WIN32__
# include "Windows/Windows.h"
#endif // __WIN32__

#ifdef __linux__
# include "Linux/Linux.h"
#endif


function N_32 main()
{
    for(;;)
        printf("%d %d\n", get_mouse_coord_x(), get_mouse_coord_y());

    return 0;
}