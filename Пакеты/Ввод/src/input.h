#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED


#include <data-structures/buffer.h>


typedef struct
{
	Byte              *source;
	Buffer             buffer;
	N_32               buffer_data_index;

	function  Byte    (*read_byte)(Byte *source);
	function  Boolean (*end_of_data)(Byte *source);
	procedure         (*destroy_source)(Byte *source);
}
Input;


import procedure           initialize_input            (Input *input, Byte *source, function Byte (*read_byte)(Byte *source));
import procedure           deinitialize_input          (Input *input);

import procedure           read_input                  (Input *input);
import function  Byte      input_data                  (Input *input);
import function  Boolean   end_of_input                (Input *input);
import function  Boolean   read_if                     (Input *input, Byte *next);

import procedure           read_byte_array             (Input *input, Byte *array, N_32 length);
import function  N_8       read_binary_N_8             (Input *input);
import function  N_16      read_binary_N_16            (Input *input);
import function  N_32      read_binary_N_32            (Input *input);
import function  R_32      read_binary_R_32            (Input *input);
import function  N_32      read_N_32                   (Input *input);
import function  Z_32      read_Z_32                   (Input *input);
import function  R_32      read_R_32                   (Input *input);

import procedure           skip_spaces                 (Input *input);
import procedure           skip_input_text_empty_lines (Input *input);

#define INPUT(source, read_byte)\
{\
    Input input;\
    initialize_input(&input, (source), (read_byte));

#define END_INPUT\
    deinitialize_input(&input);\
}


#endif // INPUT_H_INCLUDED
