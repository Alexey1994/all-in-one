#ifndef BUFFER_H_INCLUDED
#define BUFFER_H_INCLUDED


typedef struct
{
    N_32    reserve;
    N_32    length;
    Byte   *data;
}
Buffer;


import procedure         initialize_buffer        (Buffer *buffer, N_32 reserve);
import procedure         deinitialize_buffer      (Buffer *buffer);

import procedure         write_in_buffer          (Buffer *buffer, Byte byte);
import procedure         copy_buffer              (Buffer *copy, Buffer *original);
import procedure         add_buffer_to_buffer     (Buffer *left, Buffer *right);
import procedure         clear_buffer             (Buffer *buffer);

export void remove_from_buffer (Buffer* buffer, N_32 index, N_32 size_of_data, Byte* data);


#define BUFFER(reserve)\
{\
    Buffer buffer;\
    initialize_buffer(&buffer, (reserve));

#define END_BUFFER\
    deinitialize_buffer(&buffer);\
}

#define add_in_buffer(buffer, data, length)\
{\
    N_32 _index;\
    for(_index = 0; _index < (length); ++_index)\
        write_in_buffer((buffer), ((Byte*)&(data))[_index]);\
}

#define BUFFER_LENGTH(buffer, size_of_data)


#endif // BUFFER_H_INCLUDED
