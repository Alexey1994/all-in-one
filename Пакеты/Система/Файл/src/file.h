#ifndef SYSTEM_FILE_H_INCLUDED
#define SYSTEM_FILE_H_INCLUDED


#ifdef __WIN32__
# include "Windows/Windows.h"
#endif

#ifdef __linux__
# include "Linux/Linux.h"
#endif


import function  Boolean initialize_file    (File *file, Byte *path);
import procedure         deinitialize_file  (File *file);

import function  Boolean read_from_file     (File *file, Byte *data, N_32 data_length);
import function  Boolean write_in_file      (File *file, Byte *data, N_32 data_length);

import function  N_64    get_file_size      (File *file);

/*
#include <input/input.h>


export function  Boolean initialize_file_input  (Input *file_input, Character *path);
export function  Boolean initialize_file_output (Output *file_output, Character *path);
*/

#endif // SYSTEM_FILE_H_INCLUDED
