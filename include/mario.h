#ifndef MARIO_IS_DEF
#define MARIO_IS_DEF

#include "constants.h"
#include "object.h"

extern dynamic_object_t mario;

//extern int y_bird ;

//extern int x_speed;

void animation_mario_one_step(dynamic_object_t *obj);
void animation_mario_moves(dynamic_object_t *obj, int up, int down, int left, int right, int space);
//void animation_bird_timer_expired (dynamic_object_t *obj);

extern int offset;

#endif