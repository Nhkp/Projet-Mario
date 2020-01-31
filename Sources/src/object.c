#include "object.h"
//#include "bird.h"
#include "sprite.h"
#include "graphics.h"
#include "missile.h"
#include "explosion.h"
#include "timer.h"
#include "mario.h"


object_type_t object_class [4];

object_type_t object_class2 [4];

void object_init (void)
{
    object_type_t main_mario;
    main_mario.animate_func = (*animation_mario_one_step);
    object_class [OBJECT_TYPE_MARIO] = main_mario;

    object_type_t main_shot;
    main_shot.animate_func = (*animation_missile_one_step);
    object_class [OBJECT_TYPE_MISSILE] = main_shot; 

    object_type_t explosion;
    explosion.animate_func = (*animation_explosion);
    object_class [OBJECT_TYPE_EXPLOSION] = explosion; 
    
    //object_class [OBJECT_TYPE_TEXT] = &texte_move;  
}

void object_object_init (dynamic_object_t *obj, sprite_t *sp, int type, int x, int y)
{
    obj->sprite = sp;
    obj->type = type;
    obj->x = x;
    obj->y = y;
    obj->direction = 1;

    obj->anim_next_step = 0;
    obj->i = 0;
    obj->state = 0;
    obj->xs = 0;
    obj->ys = 0;
    //obj->timer = timer_init();
}