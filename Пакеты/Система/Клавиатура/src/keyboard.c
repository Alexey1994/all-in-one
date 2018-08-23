#include <system.h>


#ifdef __WIN32__
# include "Windows/Windows.h"
#endif

#ifdef __linux__
# include "Linux/Linux.h"
#endif

#ifdef __x86_32_bit__
# include "x86 32 bit/x86 32 bit.h"
#endif


N_32 main()
{
    while(!pressed_key('Q'));

    return 0;
}