#include "Windows.h"
#include <memory.h>


import function File    OpenFile    (Byte *path, File_Data *file_data, N_32 flags);
import function Boolean CloseHandle (File file);

import function File CreateFileA(
    Byte *name,
    N_32  flags1,              // режим доступа
    N_32  flags2,              // разрешить другим процессам доступ к файлу, 0 - запретить всё
    void *security_attributes, // 0 если не наследуется дочерними процессами
    N_32  flags4,              // CREATE_NEW | CREATE_ALWAYS | OPEN_EXISTING | OPEN_ALWAYS | TRUNCATE_EXISTING
    N_32  flags5,
    File  file
);

import function Boolean DeleteFileA (Byte *path);

import function Boolean ReadFile(
    File  file,
    Byte *buffer,
    N_32  buffer_length,
    N_32 *bytes_readed,
    Byte *overlapped
);

import function Boolean WriteFile(
    File  file,
    Byte *data,
    N_32  data_length,
    N_32 *bytes_writed,
    Byte *overlapped
);

//https://docs.microsoft.com/ru-ru/windows/desktop/api/fileapi/nf-fileapi-setfilepointer
import function N_32 SetFilePointer(
    File  file,
    N_32  position,
    N_32 *position_high,
    N_32  method
);

import function Boolean GetFileInformationByHandle(File file, File_Information *information);


function Boolean file_exist (Byte *path)
{
    File      file;
    File_Data file_data;

    file = OpenFile(path, &file_data, OPEN_FILE_READ);
    CloseHandle(file);

    return !file_data.error_code;
}


export function Boolean create_file (Byte *path, N_64 size)
{
    File file;
    Byte buffer[512];
    Byte byte_buffer;
    N_64 count;
    N_32 remind;
    N_32 i;
    N_32 bytes_writed;

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


export procedure delete_file (Byte *path)
{
    DeleteFileA(path);
}


export function N_64 read_from_file (Byte *path, N_64 position, Byte *data, N_32 data_length)
{
    File      file;
    File_Data file_data;
    N_32      bytes_readed;

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


export function N_64 write_in_file  (Byte *path, N_64 position, Byte *data, N_32 data_length)
{
    File      file;
    File_Data file_data;
    N_32      bytes_writed;

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


export function N_64 get_file_size  (Byte *path)
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
