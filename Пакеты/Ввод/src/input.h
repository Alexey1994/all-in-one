#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED


#include <data-structures/buffer.h>


typedef struct
{
	Byte*  source;
	Buffer buffer;
	N_32   buffer_data_index;

	Byte    (*read_byte)(Byte* source);
	Boolean (*end_of_data)(Byte* source);
	void    (*destroy_source)(Byte* source);
}
Input;


import void    initialize_input            (Input* input, Byte* source, function Byte (*read_byte)(Byte* source));
import void    deinitialize_input          (Input* input);

import void    read_input                  (Input* input);
import Byte    input_data                  (Input* input);
import N_32    input_UTF_8_data            (Input* input);
import Boolean end_of_input                (Input* input);
import Boolean read_if                     (Input* input, Byte* next);

import void    read_byte_array             (Input* input, Byte* array, N_32 length);
import N_8     read_binary_N_8             (Input* input);
import N_16    read_binary_N_16            (Input* input);
import N_32    read_binary_N_32            (Input* input);
import R_32    read_binary_R_32            (Input* input);
import N_32    read_N_32                   (Input* input);
import Z_32    read_Z_32                   (Input* input);
import R_32    read_R_32                   (Input* input);
import N_32    read_UTF_8_character        (Input* input);

import void    skip_spaces                 (Input* input);
import void    skip_input_text_empty_lines (Input* input);

#define INPUT(source, read_byte)\
{\
    Input input;\
    initialize_input(&input, (source), (read_byte));

#define END_INPUT\
    deinitialize_input(&input);\
}


#endif // INPUT_H_INCLUDED
