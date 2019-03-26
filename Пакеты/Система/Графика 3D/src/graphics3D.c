#include <system.h>
#include "graphics3D.h"


#ifdef __WIN32__
# include "Windows/Windows.c"
#endif

#ifdef __x86_32_bit__
# include "x86 32 bit/x86 32 bit.h"
#endif


void test_2D()
{
    GRAPHICS(1440, 900)
        loop
            gl_clear();

            cycle(0, graphics.width * graphics.height, 1)
                graphics.data[i] = (128 << 24) + 128;
            end

            DRAW
        end
    END_GRAPHICS
}


void test_3D()
{
    GRAPHICS_3D(1440, 900)
        loop
            gl_clear();

            gl_rotate(1, 1, 1, 1);

            gl_color(1, 0, 0);
            gl_begin();
                gl_vertex(0, 0, 0);
                gl_vertex(1, 0, 0);
                gl_vertex(0, 1, 0);
            gl_end();

            DRAW
        end
    END_GRAPHICS
}


Bit32 main()
{
    test_2D();
    //test_3D();

    return 0;
}
