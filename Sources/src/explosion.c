#include "object.h"
#include "explosion.h"

void animation_explosion(dynamic_object_t *obj)
{
    //Animation de l'explosion
    if (obj->anim_next_step < 25 && obj->anim_next_step != -1)
        obj->anim_next_step++;
    else if (obj->anim_next_step >=25 && obj->anim_next_step != -1)
        obj->anim_next_step = -1;
}
