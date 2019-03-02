#define IPv4                      2
#define SOCKET_STREAM             1
#define TCP_PROTOCOL              6

#define SHUTDOWN_RECEIVE_AND_SEND 2

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
    //Z_16 family;
    Bit16 family;
    Bit16 port;
    Bit32 in_address;
    Bit8  zero[8];
}
Windows_Socket_Address_Info;

typedef struct
{
    Bit8*  host_name;
    Bit8** aliases;
    Bit16  address_type;
    Bit16  length;
    Bit8** address_list;
}
Host_Data;


import Bit32       WSAStartup    (Bit16 version, Windows_Sockets* sockets);
import Host_Data*  gethostbyname (Bit8* host);
import Bit16       htons         (Bit16 port);
import int         socket        (Bit32 family, Bit32 type, Bit32 protocol);
import Bit32       closesocket   (Z_32 socket);
import Bit32       connect       (Z_32 socket, Windows_Socket_Address_Info* address_info, Bit32 size_of_address_info);
import Bit32       send          (Z_32 socket, Bit8* data, Bit32 length_data, Bit32 flags);
import Bit32       recv          (Z_32 socket, Bit8* data, Bit32 length_data, Bit32 flags);
