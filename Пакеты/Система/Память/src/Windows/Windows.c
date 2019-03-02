export Bit8* allocate_memory (Bit32 size)
{
    return VirtualAlloc(0, size, WINDOWS_COMMIT_MEMORY, WINDOWS_PAGE_EXECUTE_READWRITE);
}


export void free_memory(Bit8* memory_address)
{
    VirtualFree(memory_address, 0, WINDOWS_RELEASE_MEMORY);
}
