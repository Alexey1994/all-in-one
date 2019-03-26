#ifndef GRAPHICS_2D_POLYGON_H_INCLUDED
#define GRAPHICS_2D_POLYGON_H_INCLUDED


#include <system/graphics3d.h>
#include <data-structures/buffer.h>


typedef struct
{
    N_16 x;
    N_16 y;
}
Point_2D;

typedef Buffer Polygon;


import procedure initialize_polygon   (Polygon *polygon);
import procedure deinitialize_polygon (Polygon *polygon);
import procedure add_point_in_polygon (Polygon *polygon, Point_2D point);
import procedure draw_polygon         (Graphics *graphics, Polygon *polygon, N_32 color);


#endif // GRAPHICS_2D_POLYGON_H_INCLUDED
