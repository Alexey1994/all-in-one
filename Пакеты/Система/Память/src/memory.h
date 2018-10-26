#ifndef SYSTEM_MEMORY_H_INCLUDED
#define SYSTEM_MEMORY_H_INCLUDED


#define new(length) allocate_memory(sizeof(length))


import function  Byte* allocate_memory (N_32 size);
import procedure       free_memory     (Byte *memory_address);


#define ALLOCATE_MEMORY(size)\
{\
    Byte *memory = allocate_memory((size));

#define END_ALLOCATE_MEMORY\
    free_memory(memory);\
}


#endif // SYSTEM_MEMORY_H_INCLUDED
