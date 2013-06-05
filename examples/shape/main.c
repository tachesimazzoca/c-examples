#include <stdio.h>
#include "shape.h"

int main(void)
{
  point p1 = { 10, 10 };
  point p2 = { 15, 35 };

  printf("p1 x:%d, y:%d\n", p1.x, p1.y);
  printf("p2 x:%d, y:%d\n", p2.x, p2.y);

  point p = shape_point_move(p1, p2);
  printf("p1 -> p2 x:%d, y:%d\n", p.x, p.y);

  printf("p1 == p1: %d\n", shape_point_equals(p1, p1));
  printf("p2 == p2: %d\n", shape_point_equals(p2, p2));
  printf("p1 == p2: %d\n", shape_point_equals(p1, p2));

  rectangle rect = { p1, p2 };
  printf("area: %d\n", shape_rectangle_area(rect));
}
