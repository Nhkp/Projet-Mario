#ifndef ANIM_IS_DEF
#define ANIM_IS_DEF

#include "object.h"

void animation_init(void);

void animation_one_step(int space, int up, int down, int left, int right, int ok, int shift, int q, int e);

//void animation_render_objects (void);

void animation_mobile_object_del(dynamic_object_t *obj);
void animation_mobile_object_add(dynamic_object_t *obj);
void animation_clean(void);

void animation_timer_add(dynamic_object_t *obj, Uint32 delay);
void animation_timer_cancel(dynamic_object_t *obj);
void animation_timer_expired(void *arg1, void *arg2);

#endif