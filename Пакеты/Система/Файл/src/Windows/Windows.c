#include "Windows.h"
#include <memory.h>


import File OpenFile    (Bit8* path, File_Data* file_data, Bit32 flags);
import Bit8 CloseHandle (File file);

import File CreateFileA(
    Bit8* name,
    Bit32 flags1,              // режим доступа
    Bit32 flags2,              // разрешить другим процессам доступ к файлу, 0 - запретить всё
    void* security_attributes, // 0 если не наследуется дочерними процессами
    Bit32 flags4,              // CREATE_NEW | CREATE_ALWAYS | OPEN_EXISTING | OPEN_ALWAYS | TRUNCATE_EXISTING
    Bit32 flags5,
    File  file
);

import Bit8 DeleteFileA (Bit8* path);

import Bit8 ReadFile(
    File   file,
    Bit8*  buffer,
    Bit32  buffer_length,
    Bit32* bytes_readed,
    Bit8*  overlapped
);

import Bit8 WriteFile(
    File   file,
    Bit8*  data,
    Bit32  data_length,
    Bit32* bytes_writed,
    Bit8*  overlapped
);

//https://docs.microsoft.com/ru-ru/windows/desktop/api/fileapi/nf-fileapi-setfilepointer
import Bit32 SetFilePointer(
    File   file,
    Bit32  position,
    Bit32* position_high,
    Bit32  method
);

import Bit32 GetFileInformationByHandle(File file, File_Information* information);


Bit32 file_exist (Bit8* path)
{
    File      file;
    File_Data file_data;

    file = OpenFile(path, &file_data, OPEN_FILE_READ);
    CloseHandle(file);

    return !file_data.error_code;
}


export Boolean create_file (Bit8* path, Bit8* data, Bit32 data_length)
{
    File  file;
    Bit32 bytes_writed;

    if(file_exist(path))
        goto error;

    file = CreateFileA(path, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

    WriteFile(file, data, data_length, &bytes_writed, 0);

    if(bytes_writed != data_length)
        goto error2;

    CloseHandle(file);

    return 1;

error:
    return 0;

error2:
    CloseHandle(file);
    delete_file(path);
    return 0;
}


export Boolean delete_file (Bit8* path)
{
    return DeleteFileA(path);
}


export File open_file (Bit8* path)
{
    File      file;
    File_Data file_data;

    file = OpenFile(path, &file_data, OPEN_READ_AND_WRITE);

    if(file_data.error_code)
        goto error;

    return file;

error:
    return 0;
}


export Boolean read_from_file (File file, Bit64 position, Bit8* data, Bit32 data_length)
{
    Bit32 bytes_readed;

    if(position)
        SetFilePointer(file, position, 0, 0);

    if(!ReadFile(file, data, data_length, &bytes_readed, 0) || bytes_readed != data_length)
        goto error;

    return 1;

error:
    return 0;
}


export Boolean write_in_file (File file, Bit64 position, Bit8* data, Bit32 data_length)
{
    Bit32 bytes_writed;

    if(position)
        SetFilePointer(file, position, 0, 0);

    if(!WriteFile(file, data, data_length, &bytes_writed, 0) || bytes_writed != data_length)
        goto error;

    return 1;

error:
    return 0;
}


export Bit64 get_file_size (File file)
{
    File_Information file_information;

    if(!GetFileInformationByHandle(file, &file_information))
        goto error;

    CloseHandle(file);

    return file_information.size_low;

error:
    return 0;
}
