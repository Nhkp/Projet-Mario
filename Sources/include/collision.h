#ifndef COLLISION_IS_DEF
#define COLLISION_IS_DEF

#include "object.h"
#include "map.h"


enum {
UP,
DOWN,
LEFT,
RIGHT
};

int collision(dynamic_object_t *obj, int direction);
int isInside(dynamic_object_t *obj1, map_object_t obj2);

#endif