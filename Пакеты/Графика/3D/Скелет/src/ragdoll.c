#include <system.h>
#include <system/graphics3D.h>
#include "ragdoll.h"


void gl_cube()
{
    gl_color(0.8, 0.8, 0.8);
    gl_begin();
        gl_vertex(0, 0, 0);
        gl_vertex(0, 0, 1);
        gl_vertex(1, 0, 1);

        gl_vertex(0, 0, 0);
        gl_vertex(1, 0, 1);
        gl_vertex(1, 0, 0);
        ///////////////////
        gl_vertex(0, 0, 0);
        gl_vertex(0, 1, 0);
        gl_vertex(0, 1, 1);

        gl_vertex(0, 0, 0);
        gl_vertex(0, 1, 1);
        gl_vertex(0, 0, 1);
        ///////////////////
        gl_vertex(0, 1, 0);
        gl_vertex(1, 1, 0);
        gl_vertex(1, 1, 1);

        gl_vertex(0, 1, 0);
        gl_vertex(1, 1, 1);
        gl_vertex(0, 1, 1);
        ///////////////////
        gl_vertex(1, 0, 0);
        gl_vertex(1, 0, 1);
        gl_vertex(1, 1, 1);

        gl_vertex(1, 0, 0);
        gl_vertex(1, 1, 1);
        gl_vertex(1, 1, 0);
        ///////////////////
        gl_vertex(0, 0, 1);
        gl_vertex(0, 1, 1);
        gl_vertex(1, 1, 1);

        gl_vertex(0, 0, 1);
        gl_vertex(1, 1, 1);
        gl_vertex(1, 0, 1);
        ///////////////////
        gl_vertex(0, 0, 0);
        gl_vertex(1, 0, 0);
        gl_vertex(1, 1, 0);

        gl_vertex(0, 0, 0);
        gl_vertex(1, 1, 0);
        gl_vertex(0, 1, 0);
    gl_end();
}


N_32 main()
{
    float angle = 0;

    GRAPHICS(1440, 900)
        loop
            gl_clear();

            //gl_scale(0.1, 0.1, 0.1);

            gl_rotate(angle, 1, 0, 0);
            gl_translate(0, 0.5, 0.4);
            angle += 10;
            gl_cube();

            DRAW
        end
    END_GRAPHICS

    return 0;
}
