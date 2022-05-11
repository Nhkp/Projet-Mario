#ifndef DYNOBJECT_IS_DEF
#define DYNOBJECT_IS_DEF

#include <SDL.h>
#include "constants.h"

void bomb_add(dynamic_object_t *obj);
void bomb_callback(dynamic_object_t *obj);

void landmine_add(dynamic_object_t *obj);
void animation_landmine_one_step(dynamic_object_t *obj);
void landmine_activation(dynamic_object_t *obj, int ok);
void landmine_callback(dynamic_object_t *obj);

void tank_destruction();
void tank_one_step(dynamic_object_t *obj);
void tank_callback(dynamic_object_t *obj);
int inside_tank(int x, int y, int w, int h);

extern dynamic_object_t tank;

#endif