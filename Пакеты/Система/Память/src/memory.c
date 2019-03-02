#include <system.h>
#include "memory.h"


#ifdef __WIN32__
# include "Windows/Windows.h"
#endif

#ifdef __x86_32_bit__
# include "x86 32 bit/x86 32 bit.h"
#endif


Bit32 main()
{
    MEMORY(m, 32)
        m[0] = 'H';
        m[1] = 'i';
        m[2] = '\0';
        printf(m);
    END_MEMORY(m)

    return 0;
}
