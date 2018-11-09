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

N_32 y = 0;
N_32 x = 0;

function Boolean on_request (Address *client_address, N_32 *data, N_32 data_length, Graphics *graphics)
{
    //printf("request %d bytes\n %s \n", data_length, data);

    //printf("%d\n", count);

    N_32 *display = graphics->data;
    data_length /= 4;

    cycle(0, data_length, 1)
        if(x == 200)
        {
            x = 0;
            ++y;

            if(y == 200)
                y = 0;
        }

        display[y * graphics->width + x] = data[i];

        ++x;
    end

    //draw_graphics(graphics);
    //printf("%d frame\n", y * 100 + x);

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
