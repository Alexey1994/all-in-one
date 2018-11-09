#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED


#include <data-structures/buffer.h>


typedef enum
{
    STATIC_DATA_TYPE = '"',
    DYNAMIC_DATA_TYPE = '{',
    INNER_DATA_TYPE = '['
}
Data_Type;


typedef struct
{
    Buffer structure;
}
Data;


import procedure initialize_data   (Data *data);
    import procedure add_static_data(Data *data, Byte *array, N_32 size);
    import procedure add_dynamic_data(Data *data, Byte *array, N_32 size);
    import procedure begin_inner_data(Data *data);
    import procedure end_inner_data(Data *data);
import procedure deinitialize_data (Data *data);


#define DATA\
{\
    Data data;\
    initialize_data(&data);

#define ADD_STATIC_DATA(array, size)\
    add_static_data(&data, (array), (size));

#define ADD_DYNAMIC_DATA(array, size)\
    add_dynamic_data(&data, (array), (size));

#define INNER_DATA\
{\
    begin_inner_data(&data);

#define END_INNER_DATA\
    end_inner_data(&data);\
}

#define END_DATA\
    deinitialize_data(&data);\
}


typedef struct
{
    Buffer structure;

    N_32   data_size;
    N_32   index;
}
Data_Parser;

import function  Byte* begin_parse_data (Data_Parser *parser, Byte *data, N_32 size);
import procedure       end_parse_data   (Data_Parser *parser);


#define PARSE_DATA(in_data, size)\
{\
    Data_Parser data_parser;\
    Byte *data = begin_parse_data(&data_parser, (in_data), (size));

#define END_PARSE_DATA\
    end_parse_data(&data_parser);\
}


#endif // DATA_H_INCLUDED
