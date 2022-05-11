#include "animation.h"
#include "bird.h"
#include "mario.h"
#include "graphics.h"
#include "object.h"
#include "list.h"
#include "missile.h"
#include "map.h"
#include "constants.h"
#include "sprite.h"
#include "cursor.h"
#include "dynamic_objects.h"

static LIST_HEAD(obj_list); //Initialisation de la file d'objets

#define for_all_objects(var) \
    list_for_each_entry_safe(dynamic_object_t, var, &obj_list, chain)

//Affichage
static void graphics_render_object(dynamic_object_t *obj){
    SDL_Rect dst;
    if(obj->sprite != NULL){
    if (obj->sprite->nb_img > 1){ //Pour les images animées
        int i = obj->anim_next_step;

        dst.x = obj->x - x_screen;
        dst.y = obj->y - y_screen;
        dst.w = obj->sprite->tab[i].w;
        dst.h = obj->sprite->tab[i].h;

        SDL_RenderCopyEx(ren, obj->sprite->tex, &obj->sprite->tab[i], &dst, 0, NULL, obj->direction);
    }
    else{ //Pour les images fixes
        SDL_QueryTexture(obj->sprite->tex, NULL, NULL, &dst.w, &dst.h);

        dst.x = obj->x - x_screen;
        dst.y = obj->y - y_screen;

        SDL_RenderCopyEx(ren, obj->sprite->tex, NULL, &dst, 0, NULL, obj->direction);
    }}
}


void animation_init(char *map_path){
    INIT_LIST_HEAD(&obj_list);

    if (map_path != NULL) load_map(map_path);
    else map_new(MAP_WIDTH, MAP_HEIGHT);

    cursor_init();

    dynamic_object_t *landmine = malloc(sizeof(dynamic_object_t));
    object_object_init(landmine, &landmine_sprite, OBJECT_TYPE_LANDMINE, 16*TILE, 16*TILE);
    landmine->state = OBJECT_STATE_ACTIVE;
    animation_timer_add(landmine, 500, 1);
    animation_mobile_object_add(landmine);
    dynamic_object_t *landmine1 = malloc(sizeof(dynamic_object_t));
    object_object_init(landmine1, &landmine_sprite, OBJECT_TYPE_LANDMINE, 41*TILE, 2*TILE);
    landmine1->state = OBJECT_STATE_ACTIVE;
    animation_timer_add(landmine1, 500, 1);
    animation_mobile_object_add(landmine1);


    object_object_init(&tank, &tank_sprite, OBJECT_TYPE_TANK, 44*TILE, 17*TILE);
    tank.direction = 1;
    animation_timer_add(&tank, TANK_HZ, 1);
    animation_mobile_object_add(&tank);

    object_object_init(&mario, &mario_sprite, OBJECT_TYPE_MARIO, MARIO_INITIAL_POSX, MARIO_INITIAL_POSY);
    animation_mobile_object_add(&mario);

    object_init();
}

void animation_one_step(int space, int up, int down, int left, int right, int ok, int q, int e, int x, int c){
    if (e || edition){
        if(e) {
            cursor.x = mario.x;
            cursor.y = mario.y;
        }
        edit_mode(ok, q);
        // SDL_SetTextureAlphaMod(mario.sprite->tex, 50);
    }
    else{
        animation_mario_moves(&mario, up, down, left, right, space, x);

        for_all_objects(obj){
            if(obj->type == OBJECT_TYPE_LANDMINE) landmine_activation(obj, c);
            animate_func_t func = object_class[obj->type].animate_func;
            if (func != NULL)
                func(obj);
        }

        coin_anim();
    }
}

void animation_render_objects(void){
    if (edition) graphics_render_object(&cursor);
    for_all_objects(obj)
        if (obj != &cursor) graphics_render_object(obj);
}

void animation_clean(void){
    for_all_objects(obj)
        if (obj->state == OBJECT_STATE_DESTROYED || obj->anim_next_step == -1){
            timer_cancel(obj->timer);
            animation_mobile_object_del(obj);
        }
}

//Ajout d'objets en bout de file
void animation_mobile_object_add(dynamic_object_t *obj){
    list_add_tail(&obj->chain, &obj_list);
}

//Suppression d'objets
void animation_mobile_object_del(dynamic_object_t *obj){
    list_del(&obj->chain);
}

void animation_timer_add(dynamic_object_t *obj, Uint32 delay, int loop){
    if(loop)
        obj->timer = timer_loop_set(delay, (void*)obj);
    else
        obj->timer = timer_set(delay, (void*)obj);
}
void animation_timer_cancel(dynamic_object_t *obj){
    timer_cancel(obj->timer);
}
void animation_timer_expired(void *arg1, void *arg2){
    timer_func_t func = object_class[((dynamic_object_t*)arg1)->type].timer_func;
    if (func != NULL)
        func((dynamic_object_t*)arg1);
}