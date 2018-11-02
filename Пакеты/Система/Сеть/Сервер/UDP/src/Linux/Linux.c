private procedure listen_UDP_Server_requests (UDP_Server *server)
{
    Address client_address;
    N_32    client_address_length;
    Byte    buffer[UDP_SERVER_RECEIVE_BUFFER_SIZE];
    Z_32    buffer_data_size;

    while(server->server_is_running)
    {
        client_address_length = sizeof(Address);
        buffer_data_size = recvfrom(server->socket, buffer, UDP_SERVER_RECEIVE_BUFFER_SIZE, 0, &client_address, &client_address_length);

        if(buffer_data_size == -1)
            goto stop;

        server->on_request(&client_address, buffer, buffer_data_size, server->attributes);
    }

    if(debug_output.write_byte)
        write_null_terminated_byte_array(&debug_output, "stopping UDP server\n");

    close(server->socket);

    return;

stop:
    if(debug_output.write_byte)
        write_null_terminated_byte_array(&debug_output, "error listening UDP server in listen_UDP_Server_requests\n");

    close(server->socket);
}


internal function Boolean initialize_UDP_Server (UDP_Server *server, Address *server_address, function Boolean (*on_request) (Address *client_address, Byte *data, N_32 data_length, Byte *attributes), Byte *attributes)
{
    server->socket = socket(IPv4, SOCKET_DATAGRAMS, UDP_PROTOCOL);

    if(server->socket == -1)
        goto error;

    if(bind(server->socket, server_address, sizeof(Address)))
        goto error;

    server->attributes = attributes;
    server->on_request = on_request;
    server->server_is_running = 1;
    run_thread(&listen_UDP_Server_requests, server);

    return 1;

error:
    if(debug_output.write_byte)
        write_null_terminated_byte_array(&debug_output, "error in initialize_UDP_Server\n");

    return 0;
}


internal procedure deinitialize_UDP_Server (UDP_Server *server)
{
    server->server_is_running = 0;
}