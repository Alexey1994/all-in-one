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

    Bit8  data[256] = {};
    Bit32 bytes;

    if(!create_file("a.txt", 0, 0))
        printf("File exist\n");

    file = open_file("a.txt");

    write_in_file(file, 1, "Hi", 2);
    printf("%s\n", data);

    read_from_file(file, 1, data, 2);
    printf("%s\n", data);

    printf("%d bytes\n", get_file_size(file));

    return 0;
}
