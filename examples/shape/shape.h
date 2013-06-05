#ifndef SHAPE_H
#define SHAPE_H

typedef struct {
  int x;
  int y;
} point;

typedef struct {
  point lt; // { left, top }
  point rb; // { right, bottom }
} rectangle;

point shape_point_move(point from, point to);
int shape_point_equals(point p1, point p2);
int shape_rectangle_area(rectangle rect);

#endif  /* SHAPE_H */
