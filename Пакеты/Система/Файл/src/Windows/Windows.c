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

import function Boolean GetFileInformationByHandle(File file, File_Information *information);


export function Boolean initialize_file (File *file, Byte *path)
{
    File_Data file_data;

    //*file = OpenFile(path, &file_data, 0);

    //if(file_data.error_code)
    //    goto error;

    *file = CreateFileA(path, GENERIC_WRITE | GENERIC_READ, 0, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

    if(*file < 0)
        goto error;

    return 1;

error:
    return 0;
}


export procedure deinitialize_file (File *file)
{
    CloseHandle(*file);
}

export function Boolean read_from_file (File *file, Byte *data, N_32 data_length)
{
    N_32 status;
    N_32 bytes_readed;

    status = ReadFile(*file, data, data_length, &bytes_readed, 0);

    return 1;

error:
    return 0;
}


export function Boolean write_in_file (File *file, Byte *data, N_32 data_length)
{
    N_32 status;
    N_32 bytes_writed;

    status = WriteFile(*file, data, data_length, &bytes_writed, 0);

    return 1;

error:
    return 0;
}


export function N_64 get_file_size (File *file)
{
    File_Information information;
    
    GetFileInformationByHandle(*file, &information);

    return information.size_low;
}

/*
private function Byte read_file_byte(File *file)
{
    Byte byte;
    N_32 bytes_readed;

    ReadFile(file->file_source, &byte, 1, &bytes_readed, 0);

    if(!bytes_readed)
        file->is_end_of_file = 1;

    return byte;
}


private function Boolean end_of_file(File *file)
{
    return file->is_end_of_file;
}


private procedure destroy_file(File *file)
{
    CloseHandle(file->file_source);
    free(file);
}


function Boolean initialize_file_input (Input *file_input, Character *path)
{
    Windows_File  file;
    File         *file_source;

    file_source = new(File);
    file_source->file_source = OpenFile(path, &file, 0);

    if(file.error_code)
        goto error;

    file_source->is_end_of_file = 0;
    initialize_input(file_input, file_source, &read_file_byte, &end_of_file);
    file_input->destroy_source = &destroy_file;

    return 1;

error:
    free(file_source);
    return 0;
}


private procedure write_byte_in_file (Windows_File *file, Byte byte)
{
    N_32 bytes_writed;

    WriteFile(file, &byte, 1, &bytes_writed, 0);
}


function Boolean initialize_file_output (Output *file_output, Character *path)
{
    Windows_File *file_source;

    file_source = CreateFileA(path, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

    if(file_source < 0)
        goto error;

    initialize_output(file_output, file_source, &write_byte_in_file);
    file_output->deinitialize_source = &CloseHandle;

    return 1;

error:
    return 0;
}*/
