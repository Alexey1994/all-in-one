#ifndef SYSTEM_MEMORY_H_INCLUDED
#define SYSTEM_MEMORY_H_INCLUDED


#define new(length) allocate_memory(sizeof(length))


import Bit8* allocate_memory (Bit32 size);
import void  free_memory     (Bit8* memory_address);


#define MEMORY(context, size)\
{\
    Bit8* context = allocate_memory((size));

#define END_MEMORY(context)\
    free_memory(context);\
}


#endif // SYSTEM_MEMORY_H_INCLUDED
