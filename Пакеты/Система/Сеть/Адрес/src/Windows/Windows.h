#ifndef SYSTEM_NETWORK_ADDRESS
#define SYSTEM_NETWORK_ADDRESS


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

typedef struct
{
    N_32                  flags;
    N_32                  family;
    N_32                  socket_type;
    N_32                  protocol;
    N_32                  address_length;
    Byte                 *name;
    Address              *address;
    struct Address_Info  *next;
}
Address_Info;


import function  N_32  WSAStartup      (N_16 version, Windows_Sockets *sockets);
import procedure       WSACleanup      ();
import function  N_32  WSAGetLastError ();

import function  Address_Info* getaddrinfo   (Byte *host, Byte *port, Address_Info *hints, Address_Info **result);
import procedure               freeaddrinfo  (Address_Info *address_info);


#endif // SYSTEM_NETWORK_ADDRESS
