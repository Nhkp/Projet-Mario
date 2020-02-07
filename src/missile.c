#include "object.h"
#include "animation.h"
#include "graphics.h"
#include "list.h"
#include "missile.h"
#include "sprite.h"
#include "explosion.h"
#include "mario.h"
#include "collision.h"


int x_shot_speed = 10;

dynamic_object_t bird_shot;

void animation_missile_add (dynamic_object_t *obj,int x, int y, int dir)
{
    //Init du laser et ajout a la liste
    object_object_init(obj, &bird_shot_sprite, OBJECT_TYPE_MISSILE, x, y);
    obj->direction = dir;
    animation_mobile_object_add(obj);
    printf("    ajout laser : %p\n",obj);
}

void animation_missile_one_step (dynamic_object_t *obj)
{
    int test = map_get((obj->x-x_shot_speed)/64,(obj->y)/64);
    //Le missile avance
    if(obj->direction && !test)
        obj->x -= x_shot_speed;
    else if (obj->direction)
    {
        switch(tab[test].type)
        {
            case 0:
                obj->x -= x_shot_speed;
                add_explosion(obj);
                break;

            default:
                break;
        }
    }

    int test2 = map_get((obj->x+x_shot_speed)/64,(obj->y)/64);
    //Le missile avance
    if(!obj->direction && !test2)
        obj->x += x_shot_speed;
    else if (!obj->direction)
    {
        switch(tab[test2].type)
        {
            case 0:
                //if (isInside(obj, tab[test2]))
                    obj->x += x_shot_speed;
                    add_explosion(obj);
                break;

            default:
                break;
        }
    }

    if (obj-> x > WIN_WIDTH - 64 || obj-> x < 1)//détection du bord de la fenêtre 
    {
        add_explosion(obj);
    }
}