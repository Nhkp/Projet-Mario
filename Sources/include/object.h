#ifndef OBJECT_IS_DEF
#define OBJECT_IS_DEF

#include <SDL.h>
#include "sprite.h"
#include "list.h"
#include "timer.h"

enum {
    OBJECT_TYPE_MARIO,
    OBJECT_TYPE_MISSILE,
    OBJECT_TYPE_EXPLOSION,
    OBJECT_TYPE_TEXT,
    __OBJECT_TYPE_NUM
};

enum {
    OBJECT_STATE_NORMAL,
    OBJECT_STATE_IN_AIR,
    OBJECT_STATE_DESTROYED,
    OBJECT_STATE_DEAD
};

typedef struct _dyn_obj {
    int type;// can ne OBJECT_TYPE_BIRD, ...
    int state;// can be OBJECT_STATE_NORMAL, ...
    int x, y; //position
    int xs, ys; //speed
    int direction; //0=left 1=right
    int anim_next_step;
    int i;
    sprite_t *sprite;
    struct list_head chain;
    timer_id_t timer;

} dynamic_object_t;

typedef void (*animate_func_t)(dynamic_object_t *obj);
typedef void (*timer_func_t)(dynamic_object_t *obj);

typedef struct {
    animate_func_t animate_func;
    timer_func_t timer_func;
} object_type_t;

extern object_type_t object_class [];
extern object_type_t object_class2 [];

//Initialize the object_class array
void object_init (void);

//Initialize fields of object obj
void object_object_init (dynamic_object_t *obj, sprite_t *sp, int type, int x, int y);

#endif