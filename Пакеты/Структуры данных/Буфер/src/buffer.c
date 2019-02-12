#include <system.h>
#include <system/memory.h>
#include <memory.h>
#include "buffer.h"


export procedure initialize_buffer (Buffer *buffer, N_32 reserve)
{
    buffer->data    = allocate_memory(reserve);
    buffer->reserve = reserve;
    buffer->length  = 0;
}


export procedure deinitialize_buffer (Buffer *buffer)
{
    free_memory(buffer->data);
}


export procedure write_in_buffer (Buffer *buffer, Byte byte)
{
    Byte *old_data;
    N_32  old_data_length;

    if(buffer->length >= buffer->reserve)
    {
        old_data = buffer->data;
        old_data_length = buffer->length;

        buffer->reserve *= 2;
        buffer->data = allocate_memory(buffer->reserve);
        copy_memory(buffer->data, old_data, old_data_length);
        free_memory(old_data);
    }

    buffer->data[buffer->length] = byte;
    ++buffer->length;
}


export procedure copy_buffer (Buffer *copy, Buffer *original)
{
    if(copy == original)
        return;

    initialize_buffer(copy, original->length);

    cycle(0, original->length, 1)
        write_in_buffer(copy, original->data[i]);
    end
}


export procedure add_buffer_to_buffer (Buffer *left, Buffer *right)
{
    cycle(0, right->length, 1)
        write_in_buffer(left, right->data[i]);
    end
}


export procedure clear_buffer (Buffer *buffer)
{
    buffer->length = 0;
}


export void remove_from_buffer (Buffer* buffer, N_32 index, N_32 size_of_data, Byte* data)
{
    N_32  element_index;
    Byte* element;

    element_index = size_of_data * index;
    element = buffer->data + element_index;

    cycle(0, size_of_data, 1)
        data[i] = element[i];
    end

    for(i = element_index; i < buffer->length - size_of_data; ++i)
        data[i] = element[i + size_of_data];

    buffer->length -= size_of_data;
}


function N_32 main()
{
    BUFFER(1)
        write_in_buffer(&buffer, 'H');
        write_in_buffer(&buffer, 'i');
        write_in_buffer(&buffer, '!');

        add_in_buffer(&buffer, "hi!", 4);

        N_32 outt;
        remove_from_buffer(&buffer, 0, 4, &outt);

        printf("%s\n", buffer.data);
    END_BUFFER

    return 0;
}
