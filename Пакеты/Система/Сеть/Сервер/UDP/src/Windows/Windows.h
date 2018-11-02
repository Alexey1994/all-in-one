#ifndef SYSTEM_NETWORK_SERVER_UDP_WINDOWS
#define SYSTEM_NETWORK_SERVER_UDP_WINDOWS


#include <system/network/address.h>


typedef struct
{
    N_16  version;
    N_16  high_version;
    Byte  description[257];
    Byte  system_status[129];
    N_32  maximum_sockets;
    N_32  maximum_UDP_size;
    Byte *vendor_info;
}
Windows_Sockets;


import function  N_32  WSAStartup      (N_16 version, Windows_Sockets *sockets);
import procedure       WSACleanup      ();
import function  N_32  WSAGetLastError ();

import function  N_32 closesocket (Z_32 socket);
import function  N_32 bind        (Z_32 conection, Address *address, N_32 size_of_address);
import function  N_32 recvfrom    (Z_32 conection, Byte *data, N_32 length, N_32 flags, Address *address, N_32 size_of_address);


#endif //SYSTEM_NETWORK_SERVER_UDP_WINDOWS