#include <system.h>
#include <system/graphics.h>
#include "UDP.h"


#ifdef __WIN32__
#include "Windows/Windows.c"
#endif

#ifdef __linux__
#include "Linux/Linux.c"
#endif

#ifdef __APPLE__
# include "Apple/Apple.c"
#endif

/*
internal procedure initialize_UDP_Connection_from_UDP_Server (UDP_Connection *connection, UDP_Server *server, Address *destination)
{
    connection->socket      = server->socket;
    connection->source      = server->source;
    connection->destination = destination;
}*/


function Boolean on_request (Address *client_address, Byte *data, N_32 data_length, Graphics *graphics)
{
    //printf("request %d bytes\n %s \n", data_length, data);

    cycle(0, data_length, 1)
        graphics->data[i] = data[i];
    end

    //draw_graphics(graphics);
    printf("frame\n");

    return 0;
}


N_32 main()
{
    GRAPHICS(1440, 900)


    UDP_Server server;
    Address    address;

    if(!initialize_address(&address, "192.168.100.26", "8092", UDP_PROTOCOL))
        return 1;

    if(!initialize_UDP_Server(&server, &address, &on_request, &graphics))
        return 10;

    for(;;)
    {
        //DRAW
    }

    END_GRAPHICS

    //loop
    //end

    return 0;
}
