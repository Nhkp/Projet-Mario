#ifndef EXPLOSION_IS_DEF
#define EXPLOSION_IS_DEF

#include "object.h"

extern sprite_t explosion_sprite;

void animation_explosion(dynamic_object_t *obj);
void add_explosion(dynamic_object_t *obj);
#endif