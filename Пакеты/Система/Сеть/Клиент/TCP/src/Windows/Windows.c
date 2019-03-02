#include "Windows.h"


Windows_Sockets TCP_Sockets = {0};


export Boolean initialize_TCP_client (TCP_Client* connection, Address* address)
{
    Windows_Socket_Address_Info  address_info;
    Host_Data*                   host_data;
    Z_32                         connection_socket;

    if(!TCP_Sockets.version)
        WSAStartup(0x0202, &TCP_Sockets);

    connection->socket = socket(IPv4, SOCKET_STREAM, TCP_PROTOCOL);

    if(connection->socket == -1)
        goto error;

    if(connect(connection->socket, address, sizeof(Address)))
    {
        closesocket(connection->socket);
        goto error;
    }

    return 1;

error:
    return 0;
}


export void deinitialize_TCP_client (TCP_Client* connection)
{
    closesocket(connection->socket);
}


export Bit32 write_in_TCP_client (TCP_Client* connection, Bit8* data, Bit32 length_data)
{
    return send(connection->socket, data, length_data, 0);
}


export Bit32 read_from_TCP_client (TCP_Client* connection, Bit8* data, Bit32 length_data)
{
    return recv(connection->socket, data, length_data, 0);
}
