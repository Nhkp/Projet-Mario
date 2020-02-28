#ifndef MISSILE_IS_DEF
#define MISSILE_IS_DEF

#include "object.h"

void animation_missile_add(dynamic_object_t *obj, int x, int y, int dir);
void animation_missile_one_step(dynamic_object_t *obj);

extern int x_shot_speed;
extern int shot_offset;

extern dynamic_object_t bird_shot;

#endif