#include "Windows.h"
#include <system/thread.h>


Windows_Sockets windows_sockets = {0};


Boolean initialize_Windows_sockets()
{
    if(!windows_sockets.version)
        return !WSAStartup(0x0202, &windows_sockets);

    return 1;
}


void deinitialize_Windows_sockets()
{
    if(windows_sockets.version)
        WSACleanup();

    windows_sockets.version = 0;
}


void listen_UDP_Server_requests (UDP_Server* server)
{
    Address client_address;
    Bit32   client_address_length;
    Byte    buffer[UDP_SERVER_RECEIVE_BUFFER_SIZE];
    int     buffer_data_size;

    while(server->server_is_running)
    {
        client_address_length = sizeof(Address);
        buffer_data_size = recvfrom(server->socket, buffer, UDP_SERVER_RECEIVE_BUFFER_SIZE, 0, &client_address, &client_address_length);

        if(buffer_data_size == -1)
            goto stop;

        server->on_request(&client_address, buffer, buffer_data_size, server->attributes);
    }

    //if(debug_output.write_byte)
    //    write_null_terminated_byte_array(&debug_output, "stopping UDP server\n");

    closesocket(server->socket);

stop:
    //if(debug_output.write_byte)
    //    write_null_terminated_byte_array(&debug_output, "error listening UDP server in listen_UDP_Server_requests\n");

    closesocket(server->socket);
}


export Boolean initialize_UDP_Server (UDP_Server* server, Address* server_address, Boolean (*on_request) (Address* client_address, Bit8* data, Bit32 data_length, Bit8* attributes), Bit8* attributes)
{
    if(!initialize_Windows_sockets())
        goto error;

    server->socket = socket(IPv4, SOCKET_DATAGRAMS, UDP_PROTOCOL);

    if(server->socket == -1)
        goto error;

    if(bind(server->socket, server_address, sizeof(Address)))
        goto error;

    server->attributes = attributes;
    server->on_request = on_request;
    server->server_is_running = 1;
    run_thread(&listen_UDP_Server_requests, server);
for(;;)
{
    sleep_thread(1);
    draw_graphics(attributes);
}
    return 1;

error:
    printf("%d", WSAGetLastError());
    printf("fsdf");
    printf("fsdf");
    return 0;
}


export void deinitialize_UDP_Server (UDP_Server* server)
{
    server->server_is_running = 0;
}
