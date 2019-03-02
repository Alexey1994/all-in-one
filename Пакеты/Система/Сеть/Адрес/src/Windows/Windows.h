#ifndef SYSTEM_NETWORK_ADDRESS
#define SYSTEM_NETWORK_ADDRESS


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

typedef struct
{
    Bit32                 flags;
    Bit32                 family;
    Bit32                 socket_type;
    Bit32                 protocol;
    Bit32                 address_length;
    Bit8*                 name;
    Address*              address;
    struct Address_Info*  next;
}
Address_Info;


import Bit32 WSAStartup      (Bit16 version, Windows_Sockets* sockets);
import void  WSACleanup      ();
import Bit32 WSAGetLastError ();

import Address_Info* getaddrinfo  (Bit8* host, Bit8* port, Address_Info* hints, Address_Info** result);
import void          freeaddrinfo (Address_Info* address_info);


#endif // SYSTEM_NETWORK_ADDRESS
