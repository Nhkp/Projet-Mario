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

dynamic_object_t bird_shot;

void animation_missile_add(dynamic_object_t *obj, int x, int y, int dir)
{
    //Init du laser et ajout a la liste
    object_object_init(obj, &bird_shot_sprite, OBJECT_TYPE_MISSILE, x, y);
    obj->direction = dir;
    animation_mobile_object_add(obj);
    //printf("    ajout laser : %p\n",obj);
}

void animation_missile_one_step(dynamic_object_t *obj)
{
    obj->xs = 8;
    //Le missile avance
    if (obj->direction)
    {
        switch (collision(obj, LEFT))
        {
        case 0:
            obj->x -= obj->xs;
            break;

        case 1:
            obj->x -= obj->xs;
            add_explosion(obj);
            break;

        case 2:
            obj->x -= obj->xs;
            add_explosion(obj);
            break;

        case 6:
            obj->x -= obj->xs;
            tnt_explode((int)(obj->x) / TILE, (int)(obj->y) / TILE);
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
        switch (collision(obj, RIGHT))
        {
        case 0:
            obj->x += obj->xs;
            break;

        case 1:
            obj->x += obj->xs;
            add_explosion(obj);
            break;

        case 2:
            obj->x += obj->xs;
            add_explosion(obj);
            break;

        case 6:
            obj->x += obj->xs;
            tnt_explode((int)(obj->x / TILE) + 1, (int)(obj->y) / TILE);
            break;

        default:
            obj->x += obj->xs;
            break;
        }
    }
}