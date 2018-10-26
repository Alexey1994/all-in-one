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


#define BUFFER(reserve)\
{\
    Buffer buffer;\
    initialize_buffer(&buffer, (reserve));

#define END_BUFFER\
    deinitialize_buffer(&buffer);\
}


#endif // BUFFER_H_INCLUDED
