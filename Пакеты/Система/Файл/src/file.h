#ifndef SYSTEM_FILE_H_INCLUDED
#define SYSTEM_FILE_H_INCLUDED


import function  Boolean create_file    (Byte *path, N_64 size);
import procedure         delete_file    (Byte *path);
import function  N_64    read_from_file (Byte *path, N_64 position, Byte *data, N_32 data_length);
import function  N_64    write_in_file  (Byte *path, N_64 position, Byte *data, N_32 data_length);
import function  N_64    get_file_size  (Byte *path);


#endif // SYSTEM_FILE_H_INCLUDED
