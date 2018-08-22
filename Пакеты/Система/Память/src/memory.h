#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED


export function  Byte* allocate_memory (N_32 size);
export procedure       free_memory     (Byte *memory_address);


#endif // MEMORY_H_INCLUDED
