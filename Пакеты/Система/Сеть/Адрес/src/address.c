#include <system.h>
#include "address.h"


#ifdef __WIN32__
# include "Windows/Windows.c"
#endif

#ifdef __linux__
# include "Linux/Linux.c"
#endif

#ifdef __APPLE__
# include "Apple/Apple.c"
#endif

/*
function Boolean write_address (Output *output, Address *address)
{
    N_32 i;

    if(address->family == IPv4)
    {
        N_8 *address_data;

        address_data = &address->ip_v4;

        //host
        for(i=0; i<3; ++i)
        {
            write_N_32(output, address_data[i]);
            write_byte(output, '.');
        }
        write_N_32(output, address_data[i]);

        //port
        N_16 converted_port;

        converted_port = address->port;

        if(is_little_endian_bytes_order())
            convert_little_to_big_endian(&converted_port, 2);

        write_byte(output, ':');
        write_N_32(output, converted_port);
    }
    else if(address->family == IPv6)
    {

    }
    else
        goto error;

    return 1;

error:
    return 0;
}*/


N_32 main()
{
    Address address;

    if(!initialize_address(&address, "vk.com", "80", UDP_PROTOCOL))
        return 1;

    return 0;
}
