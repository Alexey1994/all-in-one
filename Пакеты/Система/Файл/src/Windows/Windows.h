#define GENERIC_READ          0x80000000
#define GENERIC_WRITE         0x40000000

#define CREATE_NEW            1
#define CREATE_ALWAYS         2
#define OPEN_EXISTING         3
#define OPEN_ALWAYS           4
#define TRUNCATE_EXISTING     5

#define FILE_ATTRIBUTE_NORMAL 128


typedef Byte* File;

//https://docs.microsoft.com/ru-ru/windows/desktop/api/winbase/ns-winbase-_ofstruct
typedef struct
{
    N_8     size_struct;
    Boolean file_on_hard_disk;
    N_16    error_code;
    N_16    reserved1;
    N_16    reserved2;
    Byte    path_name[256];
}
File_Data;

/*
//https://msdn.microsoft.com/ru-ru/8f02e824-ca41-48c1-a5e8-5b12d81886b5
typedef enum
{
    BASIC_FILE_INFORMATION    = 0,
    STANDART_FILE_INFORMATION = 1
}
File_Information_Classes;
*/

typedef struct
{
    N_32 dwLowDateTime;
    N_32 dwHighDateTime;
}
File_Time;

//https://docs.microsoft.com/ru-ru/windows/desktop/api/fileapi/ns-fileapi-_by_handle_file_information
typedef struct
{
    N_32      attributes;
    File_Time creation_time;
    File_Time last_access_time;
    File_Time last_write_time;
    N_32      volume_serial_number;
    N_32      size_high;
    N_32      size_low;
    N_32      number_of_links;
    N_32      file_index_high;
    N_32      file_index_low;
}
File_Information;