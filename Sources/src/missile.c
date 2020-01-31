#include "object.h"
#include "animation.h"
#include "graphics.h"
#include "list.h"
#include "missile.h"
#include "sprite.h"
#include "explosion.h"
#include "mario.h"

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
    //Le missile avance
    if(obj->direction)
        obj->x -= x_shot_speed;
    else
        obj->x += x_shot_speed;
    


    if (obj-> x > WIN_WIDTH - 64 || obj-> x < 1)//détection du bord de la fenêtre 
    {
        dynamic_object_t *tmp = malloc(sizeof(dynamic_object_t));
        if (tmp == NULL) // Si l'allocation a échoué
        {
            exit(0); // On arrête immédiatement le programme
        }

        object_object_init(tmp, &explosion_sprite, OBJECT_TYPE_EXPLOSION, obj->x, obj->y);
        animation_mobile_object_add(tmp); //Ajout de l'explosion dans la liste
        printf("        ajout explo : %p\n",tmp);
        
        
        obj->state = OBJECT_STATE_DESTROYED; //Le missile passe à l'état détruit
    }
}
