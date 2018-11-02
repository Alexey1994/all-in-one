#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


typedef struct
{
    N_8  length;
    N_8  family;
    N_16 port;

    union
    {
        N_32 ip_v4;
        N_32 ip_v6_flow_info;
    };

    Byte ip_v6[16];

    union
    {
        N_32 ip_v6_scope_id;

        union
        {
            struct
            {
                N_32 zone: 28;
                N_32 level: 4;
            };

            N_32 value;
        };
    };
}
Apple_Address;


typedef struct
{
    int                  flags;
    int                  family;
    int                  socket_type;
    int                  protocol;
    socklen_t            address_length;
    char                *name;
    Apple_Address       *address;
    struct Address_Info *next;
}
Address_Info;


internal procedure initialize_Apple_Address_from_Address (Apple_Address *apple_address, Address *address);
internal procedure initialize_Address_from_Apple_Address (Address *address, Apple_Address *apple_address);


#include "Apple.c"