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
    Byte *memory_address;

    memory_address = allocate_memory(32);
    free_memory(memory_address);

    //printf("Hi");

    return 0;
}