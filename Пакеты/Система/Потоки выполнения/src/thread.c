#include <system.h>
#include "thread.h"

#ifdef __WIN32__
# include "Windows/Windows.h"
#endif

#ifdef __linux__
# include "Linux/Linux.h"
#endif


void a()
{
    for(;;)
    {
        printf("a");
        sleep_thread(1);
    }
}


void b()
{
    for(;;)
    {
        printf("b");
        sleep_thread(1);
    }
}


Bit32 main()
{
    printf("\nthread ID %d\n", run_thread(a, 0));
    printf("\nthread ID %d\n", run_thread(b, 0));
    run_thread(a, 0);

    for(;;);
        return 0;
}