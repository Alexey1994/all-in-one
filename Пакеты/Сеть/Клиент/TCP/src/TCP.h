#ifndef NETWORK_TCP_CLIENT
#define NETWORK_TCP_CLIENT


#include <system/network/client/TCP.h>
#include <input.h>
#include <output.h>


typedef struct
{
    TCP_Client client;
    Boolean    is_end;
}
TCP_Client_Source;


import procedure initialize_TCP_client_input (Input* input, TCP_Client_Source* client_source);
import procedure initialize_TCP_client_output (Output* output, TCP_Client* client);


#define TCP_CLIENT_INPUT(context, address)\
{\
    TCP_Client_Source _##context##_source;\
    Input (context);\
    initialize_TCP_client((&_##context##_source.client), (address));\
    initialize_TCP_client_input((&context), &_##context##_source);

#define END_TCP_CLIENT_INPUT(context)\
    deinitialize_TCP_client(&_##context##_source.client);\
    deinitialize_input((&context));\
}


#define TCP_CLIENT_OUTPUT(context, address)\
{\
    TCP_Client _##context##_source;\
    Output (context);\
    initialize_TCP_client((&_##context##_source), (address));\
    initialize_TCP_client_output((&context), &_##context##_source);

#define END_TCP_CLIENT_OUTPUT(context)\
    deinitialize_TCP_client(&_##context##_source);\
    deinitialize_output((&context));\
}


#define TCP_CLIENT_INPUT_OUTPUT(context, address)\
{\
    TCP_Client_Source _##context##_source;\
    Input (context##_input);\
    Output (context##_output);\
    initialize_TCP_client((&_##context##_source.client), (address));\
    initialize_TCP_client_input((&context##_input), &_##context##_source);\
    initialize_TCP_client_output((&context##_output), &_##context##_source.client);

#define END_TCP_CLIENT_INPUT_OUTPUT(context)\
    deinitialize_TCP_client(&_##context##_source.client);\
    deinitialize_input((&context##_input));\
    deinitialize_output((&context##_output));\
}


#endif //NETWORK_TCP_CLIENT
