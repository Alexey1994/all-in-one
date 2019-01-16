#include <system.h>
#include "output.h"


export procedure initialize_output (Output *output, Byte *source, procedure (*write_byte)(Byte *source, Byte byte))
{
    output->source     = source;
    output->write_byte = write_byte;
    output->deinitialize_source = 0;
}


export procedure deinitialize_output (Output *output)
{
    if(output->deinitialize_source)
        output->deinitialize_source(output->source);
}


export procedure write_byte (Output *output, Byte byte)
{
    output->write_byte(output->source, byte);
}

/*
procedure write_character (Output *output, Character character)
{
    write_byte(output, character);
}
*/

export procedure write_N_32 (Output *output, N_32 number)
{
    N_32 number_copy;
    N_32 right_selector;

    number_copy    = number;
    right_selector = 1;

    for(;;)
    {
        number_copy /= 10;

        if(!number_copy)
            break;

        right_selector *= 10;
    }

    do
    {
        write_byte(output, number / right_selector % 10 + '0');
        right_selector /= 10;
    }
    while(right_selector);
}


export procedure write_byte_array (Output *output, Byte *data, N_32 length)
{
    N_32 i;

    for(i=0; i<length; ++i)
        write_byte(output, data[i]);
}


export procedure write_null_terminated_byte_array (Output *output, Byte *data)
{
    for(; *data; ++data)
        write_byte(output, *data);
}


export procedure write_binary_N_32 (Output *output, N_32 number)
{
    write_byte_array(output, &number, 4);
}


export procedure write_binary_N_16 (Output *output, N_16 number)
{
    write_byte_array(output, &number, 2);
}


export procedure write_binary_N_8 (Output *output, N_8 number)
{
    write_byte_array(output, &number, 1);
}


export procedure write_binary_R_32 (Output *output, R_32 number)
{
    write_byte_array(output, &number, 4);
}


procedure write_hex_character (Output *output, char character)
{
    if(character < 10)
        write_byte(output, character + '0');
    else
        write_byte(output, character - 10 + 'A');
}


procedure write_hex_byte (Output *output, Byte byte)
{
    if(byte < 16)
    {
        write_byte(output, '0');
        write_hex_character(output, byte);
    }
    else
    {
        write_hex_character(output, byte >> 4);
        write_hex_character(output, byte & 0b00001111);
    }
}


export procedure write_hex_array (Output *output, Byte *array, N_32 length)
{
    N_32 i;

    for(i=0; i<length; ++i)
        write_hex_byte(output, array[i]);
}


export procedure write_hex_N_16 (Output *output, N_16 number)
{
    write_hex_array(output, &number, 2);
}


export procedure write_hex_N_32 (Output *output, N_32 number)
{
    write_hex_array(output, &number, 4);
}

/*
procedure write_byte_in_file(FILE *file, Byte byte)
{
    fputc(byte, file);
}
*/

#define STATIC_BUFFER_LENGTH 256

typedef struct
{
    N_32 length;
    Byte data[STATIC_BUFFER_LENGTH];
}
Static_Buffer;

void initialize_static_buffer(Static_Buffer *buffer)
{
    buffer->length = 0;
}

procedure write_byte_in_buffer(Static_Buffer *buffer, Byte byte)
{
    buffer->data[buffer->length] = byte;
    ++buffer->length;
}

function int main()
{
    Static_Buffer  buffer;
    Output         output;

    initialize_static_buffer(&buffer);

    OUTPUT(&buffer, &write_byte_in_buffer)
        write_null_terminated_byte_array(&output, "Hi ");
        write_N_32(&output, 123);

        printf(buffer.data);
    END_OUTPUT

    return 0;
}
