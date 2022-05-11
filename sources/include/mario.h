#ifndef MARIO_IS_DEF
#define MARIO_IS_DEF

#include "constants.h"
#include "object.h"

extern dynamic_object_t mario;

void animation_mario_one_step(dynamic_object_t *obj);
void animation_mario_moves(dynamic_object_t *obj, int up, int down, int left, int right, int space, int x);
void mario_callback();
int inside_mario(int x, int y, int w, int h);

extern int offset;

#endif