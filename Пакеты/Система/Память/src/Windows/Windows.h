#define WINDOWS_COMMIT_MEMORY          0x00001000
#define WINDOWS_PAGE_EXECUTE_READWRITE 0x40
#define WINDOWS_RELEASE_MEMORY         0x8000


import Bit8* VirtualAlloc (Bit8* start_address, Bit32 size, Bit32 type, Bit32 protection);
import void  VirtualFree  (Bit8* address, Bit32 size, Bit32 type);


#include "Windows.c"
