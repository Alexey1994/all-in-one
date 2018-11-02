internal procedure initialize_Apple_Address_from_Address (Apple_Address *apple_address, Address *address)
{
    memset(apple_address, 0, sizeof(Apple_Address));

    if(address->family == IPv4)
    {
        memcpy(apple_address, address, 16);
        apple_address->length = 16;
        apple_address->family = address->family;
    }
}


internal procedure initialize_Address_from_Apple_Address (Address *address, Apple_Address *apple_address)
{
    memset(address, 0, sizeof(Address));
    memcpy(address, apple_address, apple_address->length);
    address->family = apple_address->family;
    address->zero = 0;
}


internal function Boolean initialize_address (Address *address, Byte *host, Byte *port, N_32 protocol)
{
    Address_Info *address_info;
    Address_Info  hints;

    memset(&hints, 0, sizeof(Address_Info));

    if(protocol == UDP_PROTOCOL)
    {
        hints.family      = ANY_INTERNET_PROTOCOL;
        hints.socket_type = SOCKET_DATAGRAMS;
        hints.protocol    = UDP_PROTOCOL;
    }
    else if(protocol == TCP_PROTOCOL)
    {
        hints.family      = ANY_INTERNET_PROTOCOL;
        hints.socket_type = SOCKET_STREAM;
        hints.protocol    = TCP_PROTOCOL;
    }
    else
        goto error;

    if(getaddrinfo(host, port, &hints, &address_info))
        goto error;

    initialize_Address_from_Apple_Address(address, address_info->address);

    freeaddrinfo(address_info);

    return 1;

error:
    log_begin();
        if(debug_output.write_byte)
            write_null_terminated_byte_array(&debug_output, "error in initialize_address");
    log_end();

    return 0;
}