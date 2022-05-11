#ifndef COLLISION_IS_DEF
#define COLLISION_IS_DEF

#include "object.h"
#include "map.h"

enum
{
    UP,
    DOWN2,
    LEFT,
    RIGHT,
    UP_RIGHT,
    UP_LEFT,
    DOWN_RIGHT,
    DOWN_LEFT,
    DOWN_RR
};

int collision(dynamic_object_t *obj, int direction);
int inside_square(int a, int b, int c, int d, int i, int j, int k, int l);
#endif