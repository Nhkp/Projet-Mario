#include <unistd.h>
#include "map_objects.h"
#include "explosion.h"
#include "map.h"
#include "constants.h"
#include "timer.h"
#include "animation.h"
#include "graphics.h"

int chain_reaction = 0;

void coin_anim(){
    tab[5].anim_next_step = (tab[5].anim_next_step < tab[5].nb_sprites - 1) ? tab[5].anim_next_step + 1 : 0;
}

void tnt_explode(dynamic_object_t *obj){

    int x = (int)(obj->x)/TILE;
    int y = (int)(obj->y)/TILE;
    dynamic_object_t *tmp = malloc(sizeof(dynamic_object_t));
    object_object_init(tmp, NULL, OBJECT_TYPE_EXPLOSION, x * TILE, y * TILE);

    add_explosion(tmp);


    dynamic_object_t *tmp1 = malloc(sizeof(dynamic_object_t));
    object_object_init(tmp1, NULL, OBJECT_TYPE_TNT, x * TILE - TILE, y * TILE - TILE);
    add_explosion(tmp1);
    dynamic_object_t *tmpa = malloc(sizeof(dynamic_object_t));
    switch(tab[map_get(x - 1, y - 1)].type2)
    {
        case MAP_OBJECT_EXPLOSIVE:
            if(tab[map_get(x - 1, y - 1)].type == MAP_OBJECT_SEMI_SOLID)
                object_object_init(tmpa, NULL, OBJECT_TYPE_TMP2, x*TILE-TILE, y*TILE-TILE);
            else
                object_object_init(tmpa, NULL, OBJECT_TYPE_TNT, x*TILE-TILE, y*TILE-TILE);
            animation_timer_add(tmpa, DELTA_CHAIN_REACTION, 0);
            break;
        default:
            free(tmpa);
            break;
    }
    dynamic_object_t *tmp2 = malloc(sizeof(dynamic_object_t));
    object_object_init(tmp2, NULL, OBJECT_TYPE_TNT, x * TILE, y * TILE - TILE);
    add_explosion(tmp2);
    dynamic_object_t *tmpb = malloc(sizeof(dynamic_object_t));
    switch(tab[map_get(x , y - 1)].type2)
    {
        case MAP_OBJECT_EXPLOSIVE:
            if(tab[map_get(x, y - 1)].type == MAP_OBJECT_SEMI_SOLID)
                object_object_init(tmpb, NULL, OBJECT_TYPE_TMP2, x*TILE, y*TILE-TILE);
            else
                object_object_init(tmpb, NULL, OBJECT_TYPE_TNT, x*TILE, y*TILE-TILE);
            animation_timer_add(tmpb, DELTA_CHAIN_REACTION, 0);
            break;
        default:
            free(tmpb);
            break;
    }
    dynamic_object_t *tmp3 = malloc(sizeof(dynamic_object_t));
    object_object_init(tmp3, NULL, OBJECT_TYPE_TNT, x * TILE + TILE, y * TILE - TILE);
    add_explosion(tmp3);
    dynamic_object_t *tmpc = malloc(sizeof(dynamic_object_t));
    switch(tab[map_get(x + 1, y - 1)].type2)
    {
        case MAP_OBJECT_EXPLOSIVE:
            if(tab[map_get(x + 1, y - 1)].type == MAP_OBJECT_SEMI_SOLID)
                object_object_init(tmpc, NULL, OBJECT_TYPE_TMP2, x*TILE+TILE, y*TILE-TILE);
            else
                object_object_init(tmpc, NULL, OBJECT_TYPE_TNT, x*TILE+TILE, y*TILE-TILE);
            animation_timer_add(tmpc, DELTA_CHAIN_REACTION, 0);
            break;
        default:
            free(tmpc);
            break;
    }
    dynamic_object_t *tmp4 = malloc(sizeof(dynamic_object_t));
    object_object_init(tmp4, NULL, OBJECT_TYPE_TNT, x * TILE + TILE, y * TILE);
    add_explosion(tmp4);
    dynamic_object_t *tmpd = malloc(sizeof(dynamic_object_t));
    switch(tab[map_get(x + 1, y)].type2)
    {
        case MAP_OBJECT_EXPLOSIVE:
            if(tab[map_get(x + 1, y)].type == MAP_OBJECT_SEMI_SOLID)
                object_object_init(tmpd, NULL, OBJECT_TYPE_TMP2, x*TILE+TILE, y*TILE);
            else
                object_object_init(tmpd, NULL, OBJECT_TYPE_TNT, x*TILE+TILE, y*TILE);
            animation_timer_add(tmpd, DELTA_CHAIN_REACTION, 0);
            break;
        default:
            free(tmpd);
            break;
    }
    dynamic_object_t *tmp5 = malloc(sizeof(dynamic_object_t));
    object_object_init(tmp5, NULL, OBJECT_TYPE_TNT, x * TILE + TILE, y * TILE + TILE);
    add_explosion(tmp5);
    dynamic_object_t *tmpe = malloc(sizeof(dynamic_object_t));
    switch(tab[map_get(x + 1, y + 1)].type2)
    {
        case MAP_OBJECT_EXPLOSIVE:
            if(tab[map_get(x + 1, y + 1)].type == MAP_OBJECT_SEMI_SOLID)
                object_object_init(tmpe, NULL, OBJECT_TYPE_TMP2, x*TILE+TILE, y*TILE+TILE);
            else
                object_object_init(tmpe, NULL, OBJECT_TYPE_TNT, x*TILE+TILE, y*TILE+TILE);
            animation_timer_add(tmpe, DELTA_CHAIN_REACTION, 0);
            break;
        default:
            free(tmpe);
            break;
    }
    dynamic_object_t *tmp6 = malloc(sizeof(dynamic_object_t));
    object_object_init(tmp6, NULL, OBJECT_TYPE_TNT, x * TILE, y * TILE + TILE);
    add_explosion(tmp6);
    dynamic_object_t *tmpf = malloc(sizeof(dynamic_object_t));
    switch(tab[map_get(x, y + 1)].type2)
    {
        case MAP_OBJECT_EXPLOSIVE:
            if(tab[map_get(x, y + 1)].type == MAP_OBJECT_SEMI_SOLID)
                object_object_init(tmpf, NULL, OBJECT_TYPE_TMP2, x*TILE, y*TILE+TILE);
            else
                object_object_init(tmpf, NULL, OBJECT_TYPE_TNT, x*TILE, y*TILE+TILE);
            animation_timer_add(tmpf, DELTA_CHAIN_REACTION, 0);
            break;
        default:
            free(tmpf);
            break;
    }
    dynamic_object_t *tmp7 = malloc(sizeof(dynamic_object_t));
    object_object_init(tmp7, NULL, OBJECT_TYPE_TNT, x * TILE - TILE, y * TILE + TILE);
    add_explosion(tmp7);
    dynamic_object_t *tmpg = malloc(sizeof(dynamic_object_t));
    switch(tab[map_get(x - 1, y + 1)].type2)
    {
        case MAP_OBJECT_EXPLOSIVE:
            if(tab[map_get(x - 1, y + 1)].type == MAP_OBJECT_SEMI_SOLID)
                object_object_init(tmpg, NULL, OBJECT_TYPE_TMP2, x*TILE-TILE, y*TILE+TILE);
            else
                object_object_init(tmpg, NULL, OBJECT_TYPE_TNT, x*TILE-TILE, y*TILE+TILE);
            animation_timer_add(tmpg, DELTA_CHAIN_REACTION, 0);
            break;
        default:
            free(tmpg);
            break;
    }
    dynamic_object_t *tmp8 = malloc(sizeof(dynamic_object_t));
    object_object_init(tmp8, NULL, OBJECT_TYPE_TNT, x * TILE - TILE, y * TILE);
    add_explosion(tmp8);
    dynamic_object_t *tmph = malloc(sizeof(dynamic_object_t));
    switch(tab[map_get(x - 1, y)].type2)
    {
        case MAP_OBJECT_EXPLOSIVE:
            if(tab[map_get(x - 1, y)].type == MAP_OBJECT_SEMI_SOLID)
                object_object_init(tmph, NULL, OBJECT_TYPE_TMP2, x*TILE-TILE, y*TILE);
            else
                object_object_init(tmph, NULL, OBJECT_TYPE_TNT, x*TILE-TILE, y*TILE);
            animation_timer_add(tmph, DELTA_CHAIN_REACTION, 0);
            break;
        default:
            free(tmph);
            break;
    }
}

void marble_explode(dynamic_object_t *obj){
    int x = (int)(obj->x)/TILE;
    int y = (int)(obj->y)/TILE;

    scrolling_screen(x, y);

    if(!chain_reaction)
        chain_reaction = 1;

    map_set(13, x, y);

    dynamic_object_t *tmpb = malloc(sizeof(dynamic_object_t));
    switch(tab[map_get(x, y - 1)].type2)
    {
        case MAP_OBJECT_EXPLOSIVE:
            if(get_type(x, y - 1, 1) == MAP_OBJECT_SEMI_SOLID){
                object_object_init(tmpb, NULL, OBJECT_TYPE_TMP2, x*TILE, y*TILE-TILE);
                animation_timer_add(tmpb, DELTA_CHAIN_REACTION, 0);
            }
            else if(get_type(x, y - 1, 1) == MAP_OBJECT_SOLID){
                object_object_init(tmpb, NULL, OBJECT_TYPE_TNT, x * TILE, y * TILE - TILE);
                animation_timer_add(tmpb, DELTA_CHAIN_REACTION, 0);
            }else free(tmpb);
            break;
        default:
            free(tmpb);
            break;
    }
    dynamic_object_t *tmpd = malloc(sizeof(dynamic_object_t));
    switch(tab[map_get(x + 1, y)].type2)
    {
        case MAP_OBJECT_EXPLOSIVE:
            if(get_type(x + 1, y, 1) == MAP_OBJECT_SEMI_SOLID){
                object_object_init(tmpd, NULL, OBJECT_TYPE_TMP2, x*TILE+TILE, y*TILE);
                animation_timer_add(tmpd, DELTA_CHAIN_REACTION, 0);
            }
            else if(get_type(x + 1, y, 1) == MAP_OBJECT_SOLID){
                object_object_init(tmpd, NULL, OBJECT_TYPE_TNT, x * TILE+TILE, y * TILE);
                animation_timer_add(tmpd, DELTA_CHAIN_REACTION, 0);
            } else free(tmpd);
            break;
        default:
            free(tmpd);
            break;
    }
    dynamic_object_t *tmpf = malloc(sizeof(dynamic_object_t));
    switch(tab[map_get(x, y + 1)].type2)
    {
        case MAP_OBJECT_EXPLOSIVE:
            if(get_type(x, y + 1,1) == MAP_OBJECT_SEMI_SOLID){
                object_object_init(tmpf, NULL, OBJECT_TYPE_TMP2, x*TILE, y*TILE+TILE);
                animation_timer_add(tmpf, DELTA_CHAIN_REACTION, 0);
            }
            else if(get_type(x, y + 1,1) == MAP_OBJECT_SOLID){
                object_object_init(tmpf, NULL, OBJECT_TYPE_TNT, x * TILE, y * TILE + TILE);
                animation_timer_add(tmpf, DELTA_CHAIN_REACTION, 0);
            } else free(tmpf);
            break;
        default:
            free(tmpf);
            break;
    }
    dynamic_object_t *tmph = malloc(sizeof(dynamic_object_t));
    switch(tab[map_get(x - 1, y)].type2)
    {
        case MAP_OBJECT_EXPLOSIVE:
            if(get_type(x - 1, y, 1) == MAP_OBJECT_SEMI_SOLID){
               object_object_init(tmph, NULL, OBJECT_TYPE_TMP2, x*TILE-TILE, y*TILE);
               animation_timer_add(tmph, DELTA_CHAIN_REACTION, 0);
            }
            else if(get_type(x - 1, y, 1) == MAP_OBJECT_SOLID){
                object_object_init(tmph, NULL, OBJECT_TYPE_TNT, x * TILE-TILE, y * TILE);
                animation_timer_add(tmph, DELTA_CHAIN_REACTION, 0);
            }else free(tmph);
            break;
        default:
            free(tmph);
            break;
    }
}
