#include <system.h>
#include "memory.h"


export procedure copy_memory (Byte *data1, Byte *data2, N_32 length)
{
    N_32 system_length;
    N_32 remind;

    system_length = length / 4;
    remind = length % 4;

    while(system_length)
    {
        *((N_32*)data1) = *((N_32*)data2);

        --system_length;
        data1 += 4;
        data2 += 4;
    }

    while(remind)
    {
        *data1 = *data2;

        --remind;
        ++data1;
        ++data2;
    }
}


function N_32 main()
{
    Byte *source;
    Byte  destination[6];

    source = "Hi!!!";
    copy_memory(destination, source, 6);
    printf("%s\n", destination);

    return 0;
}