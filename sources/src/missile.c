#include "object.h"
#include "animation.h"
#include "graphics.h"
#include "list.h"
#include "missile.h"
#include "sprite.h"
#include "explosion.h"
#include "mario.h"
#include "collision.h"
#include "constants.h"
#include "map_objects.h"
#include "timer.h"
#include "sound.h"
#include "dynamic_objects.h"

dynamic_object_t bird_shot;

dynamic_object_t* missile_init(){
    return malloc(sizeof(dynamic_object_t));
}

void animation_laser_add(dynamic_object_t *obj, int x, int y, int dir){
    //Init du laser et ajout a la liste
    object_object_init(obj, &bird_shot_sprite, OBJECT_TYPE_MISSILE, x, y);
    obj->direction = dir;
    animation_mobile_object_add(obj);
    play_sound(SOUND_SHOT);
}

void animation_missile_add(dynamic_object_t *obj, int x, int y, int dir){
    //Init du laser et ajout a la liste
    object_object_init(obj, &missile_sprite, OBJECT_TYPE_MISSILE, x, y);
    obj->direction = dir;
    animation_mobile_object_add(obj);
    play_sound(SOUND_BOUM);
}

void animation_missile_one_step(dynamic_object_t *obj){
    obj->xs = 8;
    obj->anim_next_step = (obj->anim_next_step + 1 > obj->sprite->nb_img-1)?0:obj->anim_next_step+1;
    //Le missile avance
    if (obj->direction)
    {
        switch (map_get((obj->x + TILE/8) / TILE, (obj->y / TILE)))
        {
        case 0:
            if (!inside_tank(obj->x-obj->xs, obj->y+TILE/2, TILE, 2)
            && !inside_mario(obj->x-obj->xs, obj->y+TILE/2, TILE, 2))
                obj->x -= obj->xs;
            else{
                obj->x -= obj->xs;
                obj->state = OBJECT_STATE_DESTROYED;
                dynamic_object_t *tmp = malloc(sizeof(dynamic_object_t));
                object_object_init(tmp, NULL, OBJECT_TYPE_EXPLOSION, obj->x, obj->y);
                tnt_explode(tmp);
                if(inside_tank(obj->x-obj->xs, obj->y+TILE/2, TILE, 2)) tank.hp-=2;
                if(inside_mario(obj->x-obj->xs, obj->y+TILE/2, TILE, 2)) mario.hp-=5;
            }
            break;
        case 3:
            obj->x -= obj->xs;
            break;
        case 4:
            obj->x -= obj->xs;
            break;

        case 5:
            obj->x -= obj->xs;
            obj->state = OBJECT_STATE_DESTROYED;
            map_set(0, (int)(obj->x) / TILE, (int)(obj->y) / TILE);
            break;

        case 6:
            obj->x -= obj->xs;
            obj->state = OBJECT_STATE_DESTROYED;
            dynamic_object_t *tmp = malloc(sizeof(dynamic_object_t));
            object_object_init(tmp, NULL, OBJECT_TYPE_EXPLOSION, obj->x, obj->y);
            tnt_explode(tmp);
            break;

        default:
            obj->x -= obj->xs;
            add_explosion(obj);
            break;
        }
    }

    //Le missile avance
    if (!obj->direction)
    {
        switch (map_get((obj->x + TILE*7/8) / TILE, (obj->y / TILE)))
        {
        case 0:
            if (!inside_tank(obj->x+obj->xs, obj->y+TILE/2, TILE, 2)
            && !inside_mario(obj->x+obj->xs, obj->y+TILE/2, TILE, 2))
                obj->x += obj->xs;
            else{
                obj->x += obj->xs;
                obj->state = OBJECT_STATE_DESTROYED;
                dynamic_object_t *tmp = malloc(sizeof(dynamic_object_t));
                object_object_init(tmp, NULL, OBJECT_TYPE_EXPLOSION, obj->x + TILE, obj->y);
                tnt_explode(tmp);
                if(inside_tank(obj->x+obj->xs, obj->y+TILE/2, TILE, 2)) tank.hp-=2;
                if(inside_mario(obj->x+obj->xs, obj->y+TILE/2, TILE, 2)) mario.hp-=5;
            }
            break;
        case 3:
            obj->x += obj->xs;
            break;
        case 4:
            obj->x += obj->xs;
            break;
        case 5:
            obj->x += obj->xs;
            obj->state = OBJECT_STATE_DESTROYED;
            map_set(0, (int)(obj->x / TILE) + 1, (int)(obj->y) / TILE);
            break;

        case 6:
            obj->x += obj->xs;
            obj->state = OBJECT_STATE_DESTROYED;
            dynamic_object_t *tmp = malloc(sizeof(dynamic_object_t));
            object_object_init(tmp, NULL, OBJECT_TYPE_EXPLOSION, obj->x+TILE, obj->y);
            tnt_explode(tmp);
            break;

        default:
            obj->x += obj->xs;
            add_explosion(obj);
            break;
        }
    }
}