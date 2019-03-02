#ifndef SYSTEM_NETWORK_TCP_CLIENT
#define SYSTEM_NETWORK_TCP_CLIENT


#include <system/network/address.h>


typedef struct
{
    Bit32 socket;
}
TCP_Client;


import Boolean initialize_TCP_client   (TCP_Client* connection, Address* address);
import void    deinitialize_TCP_client (TCP_Client* connection);

import Bit32   write_in_TCP_client     (TCP_Client* connection, Bit8* data, Bit32 length_data);
import Bit32   read_from_TCP_client    (TCP_Client* connection, Bit8* data, Bit32 length_data);

#define TCP_CLIENT(context, address)\
{\
    TCP_Client (context);\
    initialize_TCP_client(&(context), (address));

#define END_TCP_CLIENT(context)\
    deinitialize_TCP_client(&(context));\
}


#endif //SYSTEM_NETWORK_TCP_CLIENT