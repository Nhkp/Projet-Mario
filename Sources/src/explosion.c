
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

void add_explosion(dynamic_object_t *obj){
    dynamic_object_t *tmp = malloc(sizeof(dynamic_object_t));
    object_object_init(tmp, &explosion_sprite, OBJECT_TYPE_EXPLOSION, obj->x, obj->y);
    animation_mobile_object_add(tmp); //Ajout de l'explosion dans la liste
    //printf("        ajout explo : %p\n",tmp);
    obj->state = OBJECT_STATE_DESTROYED;
}