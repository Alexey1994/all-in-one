#include <system.h>
#include "data.h"


//["Hit\""{Hi\}}]


export procedure initialize_data (Data *data)
{
    initialize_buffer(&data->structure, 1);
}


export procedure add_static_data(Data *data, Byte *array, N_32 size)
{
    printf("%c", STATIC_DATA_TYPE);

    cycle(0, size, 1)
        if(array[i] == '\\' || array[i] == '"')
            printf("%c", '\\');

        printf("%c", array[i]);
    end

    printf("\"");
}


export procedure add_dynamic_data(Data *data, Byte *array, N_32 size)
{
    printf("%c", DYNAMIC_DATA_TYPE);

    cycle(0, size, 1)
        if(array[i] == '\\' || array[i] == '}')
            printf("%c", '\\');

        printf("%c", array[i]);
    end

    printf("}");
}


export procedure begin_inner_data(Data *data)
{
    printf("%c", INNER_DATA_TYPE);
}


export procedure end_inner_data(Data *data)
{
    printf("]");
}


export procedure deinitialize_data (Data *data)
{
    deinitialize_buffer(&data->structure);
}


function Byte* parse_data(Data_Parser *parser, Byte *data, Buffer *buffer)
{
    Byte    character;
    Buffer  inner_buffer;
    Byte   *inner_data;
    N_32    inner_data_address;

    if(parser->index >= parser->data_size)
        goto error;

    character = data[parser->index]; ++parser->index;

    switch(character)
    {
        case STATIC_DATA_TYPE:
            loop
                character = data[parser->index]; ++parser->index;

                if(character == '"')
                    break;

                if(character == '\\')
                {
                    if(parser->index >= parser->data_size)
                        goto error;

                    character = data[parser->index]; ++parser->index;
                }

                write_in_buffer(buffer, character);
            end

            if(character != '"')
                goto error;

            break;

        case DYNAMIC_DATA_TYPE:
            break;

        case INNER_DATA_TYPE:
            initialize_buffer(&inner_buffer, 10);
            inner_data = parse_data(parser, data, &inner_buffer);

            cycle(0, sizeof(N_32), 1)
                write_in_buffer(buffer, ((Byte*)&inner_data)[i]);
            end

            character = data[parser->index]; ++parser->index;

            if(character != ']')
                goto error;

            break;

        default:
            return 0;
    }

    return buffer->data;

error:
    return 0;
}


export function Byte* begin_parse_data (Data_Parser *parser, Byte *data, N_32 size)
{
    Buffer buffer;
    Byte *t;

    initialize_buffer(&buffer, 10);
    parser->index = 0;
    parser->data_size = size;

    do
    {
        t = parse_data(parser, data, &buffer);
    }
    while(parser->index < parser->data_size);

    return t;
}


export procedure end_parse_data   (Data_Parser *parser)
{

}

typedef struct
{
    Byte hi[2];
}
Inner_T;

typedef struct
{
    Byte hi[4];
    Inner_T *inner;
}
T;


function N_32 main()
{
    /*
    DATA
        ADD_STATIC_DATA("Hi", 2)
    END_DATA
    */
/*
    DATA
        INNER_DATA
            ADD_STATIC_DATA("Hit\"", 4)
            ADD_DYNAMIC_DATA("Hi}", 3)
        END_INNER_DATA
    END_DATA
*/

/*
    T t;

    t.inner = 123;

    T *y = &t;
    printf("%d", y->inner);
*/

    PARSE_DATA("\"Hitt\"[\"Y\"]", 11);
        T *t = data;
        printf(t->inner->hi);
    END_PARSE_DATA

    return 0;
}
