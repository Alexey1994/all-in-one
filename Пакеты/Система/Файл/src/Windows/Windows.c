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


export Boolean create_file (Bit8* path, Bit64 size)
{
    File  file;
    Bit8  buffer[512];
    Bit8  byte_buffer;
    Bit64 count;
    Bit32 remind;
    Bit32 i;
    Bit32 bytes_writed;

    if(file_exist(path))
        goto error;

    file = CreateFileA(path, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

    count = size / 512;
    remind = size % 512;

    clear_memory(buffer, 512);

    for(i = 0; i < count; ++i)
    {
        WriteFile(file, buffer, 512, &bytes_writed, 0);

        if(bytes_writed != 512)
            goto error2;
    }

    byte_buffer = 0;

    for(i = 0; i < remind; ++i)
    {
        WriteFile(file, &byte_buffer, 1, &bytes_writed, 0);

        if(bytes_writed != 1)
            goto error2;
    }

    CloseHandle(file);

    return 1;

error:
    return 0;
error2:
    CloseHandle(file);
    delete_file(path);
    return 0;
}


export void delete_file (Bit8* path)
{
    DeleteFileA(path);
}


export Bit64 read_from_file (Bit8* path, Bit64 position, Bit8* data, Bit32 data_length)
{
    File      file;
    File_Data file_data;
    Bit32     bytes_readed;

    file = OpenFile(path, &file_data, OPEN_FILE_READ);

    if(file_data.error_code)
        goto error;

    if(position)
        SetFilePointer(file, position, 0, 0);

    ReadFile(file, data, data_length, &bytes_readed, 0);
    CloseHandle(file);

    return bytes_readed;

error:
    return 0;
}


export Bit64 write_in_file  (Bit8* path, Bit64 position, Bit8* data, Bit32 data_length)
{
    File      file;
    File_Data file_data;
    Bit32     bytes_writed;

    file = OpenFile(path, &file_data, OPEN_FILE_WRITE);

    if(file_data.error_code)
        goto error;

    if(position)
        SetFilePointer(file, position, 0, 0);

    WriteFile(file, data, data_length, &bytes_writed, 0);
    CloseHandle(file);

    return bytes_writed;

error:
    return 0;
}


export Bit64 get_file_size  (Bit8* path)
{
    File             file;
    File_Data        file_data;
    File_Information file_information;

    file = OpenFile(path, &file_data, OPEN_FILE_READ);

    if(file_data.error_code)
        goto error;

    GetFileInformationByHandle(file, &file_information);
    CloseHandle(file);

    return file_information.size_low;

error:
    return 0;
}
