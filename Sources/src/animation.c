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

static LIST_HEAD(obj_list); //Initialisation de la file d'objets

int k = -1; //Initialisation de ma variable de bidouillage (voir animation_one_step)

#define for_all_objects(var) \
    list_for_each_entry_safe(dynamic_object_t, var, &obj_list, chain)

//Affichage
static void graphics_render_object(dynamic_object_t *obj)
{
    SDL_Rect dst;

    if (obj->sprite->nb_img > 1) //Pour les images animées
    {
        int i = obj->anim_next_step;

        dst.x = obj->x - x_screen;
        dst.y = obj->y - y_screen;
        dst.w = obj->sprite->tab[i].w;
        dst.h = obj->sprite->tab[i].h;

        SDL_RenderCopyEx(ren, obj->sprite->tex, &obj->sprite->tab[i], &dst, 0, NULL, obj->direction);
    }
    else //Pour les images fixes
    {
        SDL_QueryTexture(obj->sprite->tex, NULL, NULL, &dst.w, &dst.h);

        dst.x = obj->x - x_screen;
        dst.y = obj->y - y_screen;

        SDL_RenderCopyEx(ren, obj->sprite->tex, NULL, &dst, 0, NULL, obj->direction);
    }
}

//Ajout d'objets en bout de file
void animation_mobile_object_add(dynamic_object_t *obj)
{
    list_add_tail(&obj->chain, &obj_list);
}

//Suppression d'objets
void animation_mobile_object_del(dynamic_object_t *obj)
{
    list_del(&obj->chain);
}

void animation_init(void)
{
    INIT_LIST_HEAD(&obj_list);

    object_object_init(&cursor, &cursor_sprite, OBJECT_TYPE_TEXT, WIN_WIDTH/2, WIN_HEIGHT/2);
    cursor.anim_next_step = 1;
    animation_mobile_object_add(&cursor);

    object_object_init(&mario, &mario_sprite, OBJECT_TYPE_MARIO, MARIO_INITIAL_POSX, MARIO_INITIAL_POSY);
    animation_mobile_object_add(&mario);

    map_new(MAP_WIDTH, MAP_HEIGHT);

    object_init();
}

int save = -1;
void animation_one_step(int space, int up, int down, int left, int right, int ok, int tab, int q, int e)
{
    if (e || edition){
        edit_mode(&cursor, up, down, left, right, ok, tab, q);
    }
    else
    {
        animation_mario_moves(&mario, up, down, left, right, space);
        //Bidouillage artisanale pour la fréquence de tir de l'oiseau
        if (space && mario.state != OBJECT_STATE_DEAD)
            k++;

        if (k % 6 == 0)
        {
            dynamic_object_t *tmp = malloc(sizeof(dynamic_object_t));
            if (tmp == NULL) // Si l'allocation a échoué
                exit(0); // On arrête immédiatement le programme

            if (mario.direction)
                animation_missile_add(tmp, mario.x - 32, mario.y, mario.direction);
            else
                animation_missile_add(tmp, mario.x + 32, mario.y, mario.direction);
            k++;
        }

        for_all_objects(obj)
        {
            animate_func_t func = object_class[obj->type].animate_func;
            if (func != NULL)
                func(obj);
        }
    }
}

void animation_render_objects(void)
{
    if (edition) graphics_render_object(&cursor);
    for_all_objects(obj) 
        if (obj != &cursor) graphics_render_object(obj);
}

void animation_clean(void)
{
    for_all_objects(obj)
        if (/*(obj != &mario && obj->x > MAP_WIDTH*TILE) ||*/ obj->state == OBJECT_STATE_DESTROYED || obj->anim_next_step == -1)
            animation_mobile_object_del(obj);
}

/*void animation_timer_add(dynamic_object_t *obj, Uint32 delay)
{
    //obj->timer = SDL_AddTimer(delay, timer_set(delay, ));
}
void animation_timer_cancel(dynamic_object_t *obj)
{
    timer_cancel(obj->timer);
}
void animation_timer_expired(void *arg1, void *arg2)
{   
   void (*p)  (void *) = arg1;
   p(arg2);
}*/