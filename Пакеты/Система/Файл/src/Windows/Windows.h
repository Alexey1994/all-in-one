#define GENERIC_READ          0x80000000
#define GENERIC_WRITE         0x40000000

#define CREATE_NEW            1
#define CREATE_ALWAYS         2
#define OPEN_EXISTING         3
#define OPEN_ALWAYS           4
#define TRUNCATE_EXISTING     5

#define FILE_ATTRIBUTE_NORMAL 128

#define OPEN_READ_AND_WRITE   0x00000002

typedef Bit8* File;

//https://docs.microsoft.com/en-us/windows/desktop/api/winbase/nf-winbase-openfile
typedef enum
{
    OPEN_FILE_READ = 0,
    OPEN_FILE_WRITE = 1
}
Open_File_Mode;

//https://docs.microsoft.com/ru-ru/windows/desktop/api/winbase/ns-winbase-_ofstruct
typedef struct
{
    Bit8  size_struct;
    Bit8  file_on_hard_disk;
    Bit16 error_code;
    Bit16 reserved1;
    Bit16 reserved2;
    Bit8  path_name[256];
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
    Bit32 dwLowDateTime;
    Bit32 dwHighDateTime;
}
File_Time;

//https://docs.microsoft.com/ru-ru/windows/desktop/api/fileapi/ns-fileapi-_by_handle_file_information
typedef struct
{
    Bit32     attributes;
    File_Time creation_time;
    File_Time last_access_time;
    File_Time last_write_time;
    Bit32     volume_serial_number;
    Bit32     size_high;
    Bit32     size_low;
    Bit32     number_of_links;
    Bit32     file_index_high;
    Bit32     file_index_low;
}
File_Information;