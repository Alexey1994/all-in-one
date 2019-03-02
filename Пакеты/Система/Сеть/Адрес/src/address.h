#ifndef NETWORK_ADDRESS_H_INCLUDED
#define NETWORK_ADDRESS_H_INCLUDED


#define ANY_INTERNET_PROTOCOL     0
#define IPv4                      2
#define IPv6                      23

#define SOCKET_STREAM             1
#define SOCKET_DATAGRAMS          2

typedef enum
{
    TCP_PROTOCOL = 6,
    UDP_PROTOCOL = 17
}
Network_Protocol;


typedef struct
{
    Bit8  family;
    Bit8  zero;
    Bit16 port;

    union
    {
        Bit32 ip_v4;
        Bit32 ip_v6_flow_info;
    };

    Bit8 ip_v6[16];

    union
    {
        Bit32 ip_v6_scope_id;

        union
        {
            struct
            {
                Bit32 zone: 28;
                Bit32 level: 4;
            };

            Bit32 value;
        };
    };
}
Address;


import Boolean initialize_address (Address* address, Bit8* host, Bit8* port, Network_Protocol protocol);
//internal function Boolean write_address      (Output *output, Address *address);


#endif // NETWORK_ADDRESS_H_INCLUDED
