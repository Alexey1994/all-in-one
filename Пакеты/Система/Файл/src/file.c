#include <system.h>
#include "file.h"


#ifdef __WIN32__
# include "Windows/Windows.c"
#endif

#ifdef __linux__
# include "Linux/Linux.c"
#endif


N_32 main()
{
    File file;
    Byte data[256] = {};
    N_32 bytes;

    if(!create_file("a.txt", 513))
        printf("File exist\n");

    bytes = write_in_file("a.txt", 1, "Hi", 2);
    printf("%d bytes, %s\n", bytes, data);

    printf("%d\n", get_file_size("a.txt"));

    bytes = read_from_file("a.txt", 1, data, 2);
    printf("%d bytes, %s\n", bytes, data);

    return 0;
}
