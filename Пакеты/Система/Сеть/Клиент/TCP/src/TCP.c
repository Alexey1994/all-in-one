#include <system.h>
#include "TCP.h"

#ifdef __WIN32__
# include "Windows/Windows.c"
#endif

#ifdef __linux__
# include "Linux/Linux.c"
#endif

N_32 main()
{
    Address address;
    Byte    buffer[256];
    N_32    length;

    initialize_address(&address, "vk.com", "80", TCP_PROTOCOL);

    TCP_CLIENT(tcp, &address)
        snprintf(buffer, 256,
            "GET / HTTP 1.1\r\n"
            "Connection: close\r\n\r\n");

        write_in_TCP_client(&tcp, buffer, strlen(buffer));
        length = read_from_TCP_client(&tcp, buffer, 256);
        printf("%d bytes: %s", length, buffer);

        length = read_from_TCP_client(&tcp, buffer, 256);
        printf("%d bytes: %s", length, buffer);
    END_TCP_CLIENT(tcp)

    return 0;
}
