#include <system.h>
#include "memory.h"


#ifdef __WIN32__
# include "Windows/Windows.h"
#endif

#ifdef __x86_32_bit__
# include "x86 32 bit/x86 32 bit.h"
#endif


N_32 main()
{
    ALLOCATE_MEMORY(32)
        printf(memory);
    END_ALLOCATE_MEMORY

    return 0;
}