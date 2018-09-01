#ifndef SYSTEM_MEMORY_H_INCLUDED
#define SYSTEM_MEMORY_H_INCLUDED


#define new(length) allocate_memory(sizeof(length))


import function  Byte* allocate_memory (N_32 size);
import procedure       free_memory     (Byte *memory_address);


#endif // SYSTEM_MEMORY_H_INCLUDED
