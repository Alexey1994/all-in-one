#include <system.h>
#include "input.h"


export procedure initialize_input (Input *input, Byte *source, function Byte (*read_byte)(Byte *source), function Boolean (*end_of_data)(Byte *source))
{
    input->source            = source;
    input->read_byte         = read_byte;
    input->end_of_data       = end_of_data;
    input->destroy_source    = 0;
    input->buffer_data_index = 0;

    initialize_buffer(&input->buffer, 1);
}


export procedure deinitialize_input (Input *input)
{
    if(input->destroy_source)
        input->destroy_source(input->source);

    deinitialize_buffer(&input->buffer);
}


function N_32 input_buffer_length(Input *input)
{
    return input->buffer.length - input->buffer_data_index;
}


export function Byte input_head (Input *input)
{
    Byte head;

    if(!input_buffer_length(input))
        read_byte(input);

    return input->buffer.data[ input->buffer_data_index ];
}


export function Byte read_byte (Input *input)
{
    Byte last_byte;

    if(end_of_input(input) && input_buffer_length(input) <= 1)
        return 0;

    if(input_buffer_length(input) == 0)
        write_in_buffer(&input->buffer, input->read_byte(input->source));
    else if(input_buffer_length(input) == 1)
        *input->buffer.data = input->read_byte(input->source);
    else
    {
        ++input->buffer_data_index;

        if(input_buffer_length(input) == 1)
        {
            last_byte = input->buffer.data[ input->buffer_data_index ];
            clear_buffer(&input->buffer);
            write_in_buffer(&input->buffer, last_byte);
            input->buffer_data_index = 0;
        }
    }

    return input->buffer.data[ input->buffer_data_index ];
}


export function Boolean end_of_input (Input *input)
{
    if(!input->end_of_data)
        return 0;

    return input->end_of_data(input->source);
}


export function Boolean read_if_next (Input *input, Byte *next)
{
    Buffer accumulator;
    Buffer buffer_copy;

    initialize_buffer(&accumulator, 1);

    for(; *next && !end_of_input(input); ++next)
    {
        if(input_head(input) != *next)
        {
            copy_buffer(&buffer_copy, &input->buffer);
            clear_buffer(&input->buffer);
            add_buffer_to_buffer(&input->buffer, &accumulator);
            add_buffer_to_buffer(&input->buffer, &buffer_copy);

            deinitialize_buffer(&buffer_copy);
            deinitialize_buffer(&accumulator);
            return 0;
        }

        write_in_buffer(&accumulator, input_head(input));
        read_byte(input);
    }

    deinitialize_buffer(&accumulator);
    return 1;
}


export procedure read_byte_array (Input *input, Byte *array, N_32 length)
{/*
    N_32 i;

    array[0] = input_head(input);

    for(i = 1; i < length; ++i)
    {
        read_byte(input);
        array[i] = input_head(input);
    }

    ++input->buffer.begin_index;

    if(buffer_length(&input->buffer) == 0)
        clear_buffer(&input->buffer);*/
}


export function N_8 read_binary_N_8 (Input *input)
{
    N_8 number;
    read_byte_array(input, &number, 1);
    return number;
}


export function N_16 read_binary_N_16 (Input *input)
{
    N_16 number;
    read_byte_array(input, &number, 2);
    return number;
}


export function N_32 read_binary_N_32 (Input *input)
{
    N_32 number;
    read_byte_array(input, &number, 4);
    return number;
}


export function N_32 read_N_32 (Input *input)
{
    N_32 number;
/*
    number = 0;

    while(is_number(input_head(input)) && !end_of_input(input))
    {
        number = number*10 + input_head(input) - '0';
        read_byte(input);
    }
*/
    return number;
}


export procedure skip_input_spaces (Input *input)
{
    /*
    while(!end_of_input(input) && is_space(input_head(input)))
        read_byte(input);
        */
}


char fgetc(Byte *file);
char feof(Byte *file);


function N_32 main()
{
    Input input;

    Byte *file;

    file = fopen("a.txt", "rb");

    initialize_input(&input, file, &fgetc, &feof);
/*
    printf("%c", read_byte(&input));
    printf("%c", read_byte(&input));
    printf("%c", read_byte(&input));
    printf("%c", read_byte(&input));
  */

    if(read_if_next(&input, "#aaa"))
        printf("Ok\n");

    //if(read_if_next(&input, "#ifndef"))
    //    printf("Ok\n");

    printf("read %c\n", read_byte(&input));
    printf("read %c\n", read_byte(&input));
    printf("read %c\n", read_byte(&input));
    printf("read %c\n", read_byte(&input));


    return 0;
}
