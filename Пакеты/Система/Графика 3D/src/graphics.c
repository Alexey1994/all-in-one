#include <system.h>
#include "graphics.h"


#ifdef __WIN32__
# include "Windows/Windows.c"
#endif

#ifdef __x86_32_bit__
# include "x86 32 bit/x86 32 bit.h"
#endif


Bit32 main()
{
    Bit32 data[128 * 128];

    cycle(0, 128 * 128, 1)
        data[i] = 128 << 24;
    end

    GRAPHICS(1440, 900)
        loop
            glClearColor(0, 0, 0, 0);
            glClear(GL_COLOR_BUFFER_BIT);

            glColor3f(1, 0, 0);
            glBegin(GL_TRIANGLES);
                glVertex3f(0, 0, 0);
                glVertex3f(1, 0, 0);
                glVertex3f(0, 1, 0);
            glEnd();

            glRasterPos2f(0, 0);
            glDrawPixels(128, 128, GL_RGBA, GL_UNSIGNED_BYTE, data);

            DRAW
        end
    END_GRAPHICS

    return 0;
}
