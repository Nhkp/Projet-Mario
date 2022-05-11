#include "animation.h"
#include "object.h"
#include "explosion.h"
#include "sound.h"
#include "map.h"

void animation_explosion(dynamic_object_t *obj){
    //Animation de l'explosion
    if (obj->anim_next_step < 25 && obj->anim_next_step != -1)
        obj->anim_next_step++;
    else if (obj->anim_next_step >= 25 && obj->anim_next_step != -1)
        obj->anim_next_step = -1;
}

void add_explosion(dynamic_object_t *obj){
    if (obj->type == OBJECT_TYPE_TNT || obj->type==OBJECT_TYPE_BOMB){
        obj->type = OBJECT_TYPE_EXPLOSION;
        animation_timer_add(obj, DELTA_CHAIN_REACTION, 0);
        animation_mobile_object_add(obj);
    }
    else{
        dynamic_object_t *tmp = malloc(sizeof(dynamic_object_t));
        object_object_init(tmp, &explosion_sprite, OBJECT_TYPE_EXPLOSION, obj->x, obj->y);
        animation_mobile_object_add(tmp); //Ajout de l'explosion dans la liste
        obj->state = OBJECT_STATE_DESTROYED;
        if(obj->type == OBJECT_TYPE_EXPLOSION)
            if((get_type(obj->x/TILE, obj->y/TILE,1) == MAP_OBJECT_SOLID && get_type(obj->x/TILE, obj->y/TILE, 2) == MAP_OBJECT_EXPLOSIVE)
            || (get_type(obj->x/TILE, obj->y/TILE, 2) != MAP_OBJECT_EXPLOSIVE && get_type(obj->x/TILE, obj->y/TILE, 2) != MAP_OBJECT_SOLID))
                map_set(0,obj->x/TILE, obj->y/TILE);

        play_sound(SOUND_BOUM);
    }
}
