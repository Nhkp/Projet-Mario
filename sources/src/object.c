#include "object.h"
#include "sprite.h"
#include "graphics.h"
#include "missile.h"
#include "explosion.h"
#include "timer.h"
#include "mario.h"
#include "dynamic_objects.h"
#include "map_objects.h"

object_type_t object_class[10];

void object_init(void)
{
    object_type_t main_mario;
    main_mario.animate_func = (*animation_mario_one_step);
    main_mario.timer_func = (*mario_callback);
    object_class[OBJECT_TYPE_MARIO] = main_mario;

    object_type_t main_shot;
    main_shot.animate_func = (*animation_missile_one_step);
    object_class[OBJECT_TYPE_MISSILE] = main_shot;

    object_type_t explosion;
    explosion.animate_func = (*animation_explosion);
    explosion.timer_func = (*add_explosion);
    object_class[OBJECT_TYPE_EXPLOSION] = explosion;

    object_type_t bomb;
    bomb.animate_func = NULL;
    bomb.timer_func = (*bomb_callback);
    object_class[OBJECT_TYPE_BOMB] = bomb;

    object_type_t landmine;
    landmine.animate_func = (*animation_landmine_one_step);
    landmine.timer_func = (*landmine_callback);
    object_class[OBJECT_TYPE_LANDMINE] = landmine;

    object_type_t tnt;
    tnt.animate_func = NULL;
    tnt.timer_func = (*tnt_explode);
    object_class[OBJECT_TYPE_TNT] = tnt;

    object_type_t marble;
    marble.animate_func = NULL;
    marble.timer_func = (*marble_explode);
    object_class[OBJECT_TYPE_TMP2] = marble;

    object_type_t tank;
    tank.animate_func = (*tank_one_step);
    tank.timer_func = (*tank_callback);
    object_class[OBJECT_TYPE_TANK] = tank;
}

void object_object_init(dynamic_object_t *obj, sprite_t *sp, int type, int x, int y)
{
    obj->sprite = sp;
    obj->type = type;
    obj->x = x;
    obj->y = y;
    obj->direction = 0;

    obj->anim_next_step = 0;
    obj->i = 0;
    obj->state = OBJECT_STATE_NORMAL;
    obj->xs = 0;
    obj->ys = 0;
    obj->hp = 10;
    obj->timer = timer_init();
}