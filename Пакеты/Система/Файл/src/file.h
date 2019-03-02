#ifndef SYSTEM_FILE_H_INCLUDED
#define SYSTEM_FILE_H_INCLUDED


import Boolean create_file    (Bit8* path, Bit64 size);
import void    delete_file    (Bit8* path);
import Bit64   read_from_file (Bit8* path, Bit64 position, Bit8* data, Bit32 data_length);
import Bit64   write_in_file  (Bit8* path, Bit64 position, Bit8* data, Bit32 data_length);
import Bit64   get_file_size  (Bit8* path);


#endif // SYSTEM_FILE_H_INCLUDED
