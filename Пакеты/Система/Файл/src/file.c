#include <system.h>
#include "file.h"


#ifdef __WIN32__
# include "Windows/Windows.c"
#endif

#ifdef __linux__
# include "Linux/Linux.h"
#endif


N_32 main()
{
    File file;
    Byte data[256];

    initialize_file(&file, "a.txt");
        //read_from_file(&file, data, 256);
        //write_in_file(&file, "Hi", 2);
        printf("%d\n", get_file_size(&file));
    deinitialize_file(&file);

    /*
    Input file_input;

    initialize_file_input(&file_input, "a.txt");
    //if(!initialize_file_input(&file_input, "\\\\.\\ROOT\\NET\\0001"))
    //    printf("error");

    printf("%d", GetLastError());
    //printf("%c\n", read_byte(&file_input));
    //deinitialize_input(&file_input);
*/
    return 0;
}
