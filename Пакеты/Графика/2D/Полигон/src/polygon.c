#include <system.h>
#include "polygon.h"


export procedure initialize_polygon (Polygon *polygon)
{
    initialize_buffer(polygon, 4);
}


export procedure add_point_in_polygon (Polygon *polygon, Point_2D point)
{
    N_32 i;

    for(i = 0; i < 4; ++i)
        write_in_buffer(polygon, ((Byte*)&point)[i]);
}


typedef struct
{
    N_16 min_x;
    N_16 min_y;
    N_16 max_x;
    N_16 max_y;
}
Bounding_Box;


procedure calculate_bounding_box(Polygon *polygon, Bounding_Box *bounding_box)
{
    Point_2D *point;
    N_32      i;

    point = polygon->data;
    bounding_box->min_x = bounding_box->max_x = point[0].x;
    bounding_box->min_y = bounding_box->max_y = point[0].y;

    for(i = 1; i < polygon->length / 4; ++i)
    {
        if(point[i].x < bounding_box->min_x)
            bounding_box->min_x = point[i].x;

        if(point[i].x > bounding_box->max_x)
            bounding_box->max_x = point[i].x;

        if(point[i].y < bounding_box->min_y)
            bounding_box->min_y = point[i].y;

        if(point[i].y > bounding_box->max_y)
            bounding_box->max_y = point[i].y;
    }
}


procedure add_intersect_point(Buffer *intersect_points, N_16 point)
{
    N_32 i;

    for(i = 0; i < 2; ++i)
        write_in_buffer(intersect_points, ((Byte*)&point)[i]);
}


function N_32 compare_points(N_16 *x1, N_16 *x2)
{
    return *x1 - *x2;
}


procedure calculate_intersect_points (Buffer *intersect_points, Polygon *polygon, N_16 min_x, N_16 max_x, N_16 y)
{
    N_32         i;
    Point_2D     A0;
    Point_2D     A1;
    Point_2D    *B0;
    Point_2D    *B1;
    float        t;
    Point_2D     P;

    clear_buffer(intersect_points);
    A0.x = min_x;
    A0.y = y;
    A1.x = max_x;
    A1.y = y;

    for(i = 0; i < polygon->length / 4; ++i)
    {
        B0 = polygon->data + i * 4;

        if(i != polygon->length / 4 - 1)
            B1 = polygon->data + (i + 1) * 4;
        else
            B1 = polygon->data;

        N_16 tt = B1->y - B0->y;

        if(!tt)
            continue;

        t = (float)(B1->y - A1.y) / (float)tt;

        if(t < 0 || t > 1)
            continue;

        P.x = (float)A0.x * t + (float)A1.x * (1.0f - t);
printf("%f\n", t);
        add_intersect_point(intersect_points, P.x);
    }
printf("\n");
    qsort(intersect_points->data, intersect_points->length / 2, 2, &compare_points);
}


export procedure draw_polygon (Graphics *graphics, Polygon *polygon, N_32 color)
{
    Bounding_Box bounding_box;
    N_32         i;
    N_16         x;
    N_16         y;
    Buffer       intersect_points;
    N_16        *current_intersect_point;
    N_16        *next_intersect_point;

    initialize_buffer(&intersect_points, 2);
    calculate_bounding_box(polygon, &bounding_box);

    for(y = bounding_box.min_y; y <= bounding_box.max_y; ++y)
    {
        calculate_intersect_points(&intersect_points, polygon, bounding_box.min_x - 1, bounding_box.max_x + 1, y);

        for(i = 0; i < intersect_points.length / 2; i += 2)
        {
            current_intersect_point = intersect_points.data + i * 2;
            next_intersect_point = intersect_points.data + (i + 1) * 2;

            for(x = *current_intersect_point; x < *next_intersect_point; ++x)
                ((N_32*)graphics->data)[graphics->width * y + x] = color;
        }
    }

    deinitialize_buffer(&intersect_points);
}


export procedure deinitialize_polygon (Polygon *polygon)
{
    deinitialize_buffer(polygon);
}


function N_32 main()
{
    Graphics graphics;
    Polygon  polygon;
    Point_2D point;

    initialize_graphics(&graphics, 1440, 900);

    initialize_polygon(&polygon);
        point.x = 110;
        point.y = 20;
        add_point_in_polygon(&polygon, point);

        point.x = 200;
        point.y = 200;
        add_point_in_polygon(&polygon, point);

        point.x = 100;
        point.y = 200;
        add_point_in_polygon(&polygon, point);

    draw_polygon(&graphics, &polygon, 255);

    for(;;)
        draw_graphics(&graphics);

    return 0;
}
