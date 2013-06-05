#include "shape.h"

point shape_point_move(point from, point to)
{
    point p;
    p.x = from.x + to.x;
    p.y = from.y + to.y;
    return p;
}

int shape_point_equals(point p1, point p2)
{
    return (p1.x == p2.x && p1.y == p2.y);
}

int shape_rectangle_area(rectangle rect)
{
    int w = rect.rb.x - rect.lt.x;
    int h = rect.rb.y - rect.lt.y;
    return w * h;
}
