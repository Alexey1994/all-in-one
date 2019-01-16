#ifndef OUTPUT_H_INCLUDED
#define OUTPUT_H_INCLUDED


typedef struct
{
    Byte       *source;
    procedure (*write_byte)(Byte *source, Byte byte);
    procedure (*deinitialize_source)(Byte *source);
}
Output;


import procedure initialize_output   (Output *output, Byte *source, procedure (*write_byte)(Byte *source, Byte byte));
import procedure deinitialize_output (Output *output);

import procedure write_byte          (Output *output, Byte byte);
//import procedure write_character     (Output *output, Character character);
import procedure write_N_32          (Output *output, N_32 number);

import procedure write_byte_array                 (Output *output, Byte *data, N_32 length);
import procedure write_null_terminated_byte_array (Output *output, Byte *data);
import procedure write_binary_N_32                (Output *output, N_32 number);
import procedure write_binary_N_16                (Output *output, N_16 number);
import procedure write_binary_N_8                 (Output *output, N_8 number);
import procedure write_binary_R_32                (Output *output, R_32 number);

import procedure write_hex_array                  (Output *output, Byte *array, N_32 length);
import procedure write_hex_N_16                   (Output *output, N_16 number);
import procedure write_hex_N_32                   (Output *output, N_32 number);


#define OUTPUT(source, write_byte)\
{\
    Output output;\
    initialize_output(&output, (source), (write_byte));

#define END_OUTPUT\
    deinitialize_output(&output);\
}


#endif // OUTPUT_H_INCLUDED
