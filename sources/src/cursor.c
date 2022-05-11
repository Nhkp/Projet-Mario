#include "mario.h"
#include "object.h"
#include "constants.h"
#include "missile.h"
#include "animation.h"
#include "map.h"
#include "explosion.h"
#include "collision.h"
#include "sound.h"
#include "dynamic_objects.h"
#include "graphics.h"

dynamic_object_t cursor;
int edition = 0;

void cursor_init(){
    object_object_init(&cursor, &cursor_sprite, OBJECT_TYPE_CURSOR, 0, 0);
    cursor.anim_next_step = 2;
    SDL_SetTextureAlphaMod(cursor.sprite->tex, 50);
    animation_mobile_object_add(&cursor);
}

void edit_mode(int ok, int q){
    scrolling_screen(cursor.x, cursor.y);
    if (!edition)
        edition = 1;

    //Synchro sprite
    cursor_sprite.tex = tab[cursor.anim_next_step].tex;
    cursor_sprite.nb_img = tab[cursor.anim_next_step].nb_sprites;
    if (cursor_sprite.nb_img > 1)
        cursor_sprite.tab[5] = tab[cursor.anim_next_step].tab[1];

    //Application de la texture
    if (ok)
        map_set(cursor.anim_next_step, cursor.x/TILE, cursor.y/TILE);
}

void cursor_left(){
    int x = cursor.x/TILE;
    x = (x-1<0)?0: x-1;
    cursor.x = x*TILE;
}
void cursor_right(){
    int x = cursor.x/TILE;
    x = (x+1>MAP_WIDTH)?x: x+1;
    cursor.x = x*TILE;
}
void cursor_up(){
    int x = cursor.y/TILE;
    x = (x-1<0)?0: x-1;
    cursor.y = x*TILE;
}
void cursor_down(){
    int x = cursor.y/TILE;
    x = (x+1>MAP_HEIGHT)?x: x+1;
    cursor.y = x*TILE;
}

