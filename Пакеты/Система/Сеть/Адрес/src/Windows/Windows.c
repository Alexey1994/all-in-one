#include "Windows.h"


Windows_Sockets windows_sockets = {0};


function Boolean initialize_Windows_sockets()
{
    if(!windows_sockets.version)
        return !WSAStartup(0x0202, &windows_sockets);

    return 1;
}


procedure deinitialize_Windows_sockets()
{
    if(windows_sockets.version)
        WSACleanup();

    windows_sockets.version = 0;
}


export function Boolean initialize_address (Address *address, Byte *host, Byte *port, N_32 protocol)
{
    Address_Info *address_info;
    Address_Info  hints;

    if(!initialize_Windows_sockets())
        goto error;

    memset(&hints, 0, sizeof(Address_Info));

    if(protocol == UDP_PROTOCOL)
    {
        hints.family      = IPv4;
        hints.socket_type = SOCKET_DATAGRAMS;
        hints.protocol    = UDP_PROTOCOL;
    }
    else if(protocol == TCP_PROTOCOL)
    {
        hints.family      = IPv4;
        hints.socket_type = SOCKET_STREAM;
        hints.protocol    = TCP_PROTOCOL;
    }
    else
        goto error;

    if(getaddrinfo(host, port, &hints, &address_info))
        goto error;

    memset(address, 0, sizeof(Address));
    memcpy(address, address_info->address, address_info->address_length);

    freeaddrinfo(address_info);

    return 1;

error:
    return 0;
}
