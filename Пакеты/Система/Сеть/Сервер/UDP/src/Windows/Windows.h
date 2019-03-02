#ifndef SYSTEM_NETWORK_SERVER_UDP_WINDOWS
#define SYSTEM_NETWORK_SERVER_UDP_WINDOWS


#include <system/network/address.h>


typedef struct
{
    Bit16  version;
    Bit16  high_version;
    Bit8   description[257];
    Bit8   system_status[129];
    Bit32  maximum_sockets;
    Bit32  maximum_UDP_size;
    Bit8*  vendor_info;
}
Windows_Sockets;


import Bit32  WSAStartup      (Bit16 version, Windows_Sockets* sockets);
import void   WSACleanup      ();
import Bit32  WSAGetLastError ();

import Bit32 closesocket (Z_32 socket);
import Bit32 bind        (Z_32 conection, Address* address, Bit32 size_of_address);
import Bit32 recvfrom    (Z_32 conection, Bit8* data, Bit32 length, Bit32 flags, Address* address, Bit32 size_of_address);


#endif //SYSTEM_NETWORK_SERVER_UDP_WINDOWS