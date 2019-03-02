#ifndef SYSTEM_FILE_H_INCLUDED
#define SYSTEM_FILE_H_INCLUDED


typedef Bit8* File;


import Boolean create_file    (Bit8* path, Bit8* data, Bit32 data_length);
import Boolean delete_file    (Bit8* path);

import File    open_file      (Bit8* path);
import Boolean read_from_file (File file, Bit64 position, Bit8* data, Bit32 data_length);
import Boolean write_in_file  (File file, Bit64 position, Bit8* data, Bit32 data_length);
import Bit64   get_file_size  (File file);
import void    close_file     (File file);


#endif // SYSTEM_FILE_H_INCLUDED
