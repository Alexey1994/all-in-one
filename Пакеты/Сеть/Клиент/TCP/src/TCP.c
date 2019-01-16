#include <system.h>
#include "TCP.h"


function Byte read_byte_from_TCP_Client(TCP_Client_Source* client_source)
{
    Byte data;
    N_32 bytes_readed;

    if(!client_source->is_end)
    {
        bytes_readed = read_from_TCP_client(&client_source->client, &data, 1);

        if(bytes_readed == -1 || !bytes_readed)
            client_source->is_end = 1;
    }

    return data;
}


function Boolean end_of_TCP_Client_data(TCP_Client_Source* client_source)
{
    return client_source->is_end;
}


export procedure initialize_TCP_client_input (Input* input, TCP_Client_Source* client_source)
{
    initialize_input(input, client_source, &read_byte_from_TCP_Client);
    input->end_of_data = &end_of_TCP_Client_data;
}


procedure write_byte_in_TCP_client (TCP_Client* client, Byte data)
{
    write_in_TCP_client(client, &data, 1);
}


export procedure initialize_TCP_client_output (Output* output, TCP_Client* client)
{
    initialize_output(output, client, &write_byte_in_TCP_client);
}


N_32 main()
{
    Address address;
    Byte    buffer[256];
    N_32    length;

    initialize_address(&address, "vk.com", "80", TCP_PROTOCOL);
/*
    TCP_CLIENT_INPUT(tt, &address)
        snprintf(buffer, 256,
            "GET / HTTP 1.1\r\n"
            "Connection: close\r\n\r\n");

        write_in_TCP_client(&_tt_source.client, buffer, strlen(buffer));

        while(!end_of_input(&tt))
        {
            printf("%c", input_data(&tt));
            read_input(&tt);
        }
    END_TCP_CLIENT_INPUT(tt)

    TCP_CLIENT_OUTPUT(tt, &address)
        write_null_terminated_byte_array(&tt,
            "GET / HTTP 1.1\r\n"
            "Connection: close\r\n\r\n");

        length = read_from_TCP_client(&_tt_source, buffer, 256);
        printf("%d bytes %s\n", length, buffer);
    END_TCP_CLIENT_OUTPUT(tt)
*/
    TCP_CLIENT_INPUT_OUTPUT(tcp, &address)
        write_null_terminated_byte_array(&tcp_output,
            "GET / HTTP 1.1\r\n"
            "Connection: close\r\n\r\n");

        while(!end_of_input(&tcp_input))
        {
            printf("%c", input_data(&tcp_input));
            read_input(&tcp_input);
        }
    END_TCP_CLIENT_INPUT_OUTPUT(tcp)

    return 0;
}
