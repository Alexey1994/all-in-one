#ifndef UDP_NETWORK_SERVER_H_INCLUDED
#define UDP_NETWORK_SERVER_H_INCLUDED


//#include "../../connection/UDP/UDP.h"
//#include "../../../../interfaces/thread/thread.h"

#include <system/network/address.h>


#define UDP_SERVER_RECEIVE_BUFFER_SIZE 1536


typedef struct
{
    int      socket;

    Address* source;
    Address* destination;
    Bit8*    attributes;
    Boolean  server_is_running;

    Boolean (*on_request) (Address* client_address, Bit8* data, Bit32 data_length, Bit8* attributes);
}
UDP_Server;


import Boolean initialize_UDP_Server   (UDP_Server* server, Address* server_address, Boolean (*on_request) (Address* client_address, Bit8* data, Bit32 data_length, Bit8* attributes), Bit8* attributes);
import void    deinitailize_UDP_Server (UDP_Server* server);

//internal procedure         initialize_UDP_Connection_from_UDP_Server (UDP_Connection *connection, UDP_Server *server, Address *destination);


//#include "UDP.c"

#endif //UDP_NETWORK_SERVER_H_INCLUDED