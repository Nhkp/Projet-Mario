#include <SDL_image.h>

#include "graphics.h"
#include "error.h"
#include "debug.h"
#include "constants.h"
#include "sprite.h"
#include "missile.h"
#include "mario.h"

sprite_t bird_shot_sprite;
sprite_t mario_sprite;
sprite_t explosion_sprite;
sprite_t cursor_sprite;
sprite_t landmine_sprite;
sprite_t tank_sprite;
sprite_t missile_sprite;
sprite_t bomb_sprite;

void sprite_init(void)
{
    // Load bird image
    mario_sprite.tex = IMG_LoadTexture(ren, "../images/mario.png");
    if (mario_sprite.tex == NULL)
    {
        exit_with_error("IMG_LoadTexture");
    }

    SDL_QueryTexture(mario_sprite.tex, NULL, NULL, &mario_sprite.dst.w, &mario_sprite.dst.h);

    mario_sprite.nb_img = 11;
    mario_sprite.nb_step = 11;

    for (int i = 0; i < 11; i++)
    {
        mario_sprite.tab[i].w = TILE;
        mario_sprite.tab[i].h = 2*TILE;
        mario_sprite.tab[i].y = 0;
        mario_sprite.tab[i].x = i*TILE;
    }

    //Load shot image
    bird_shot_sprite.tex = IMG_LoadTexture(ren, "../images/shot.png");
    if (bird_shot_sprite.tex == NULL)
    {
        exit_with_error("IMG_LoadTexture");
    }

    bird_shot_sprite.nb_img = 1;

    missile_sprite.tex = IMG_LoadTexture(ren, "../images/missiled.png");
    if (missile_sprite.tex == NULL)
    {
        exit_with_error("IMG_LoadTexture");
    }

    missile_sprite.nb_img = 12;

    for(int i=0; i<12; i++){
        missile_sprite.tab[i].h = TILE;
        missile_sprite.tab[i].w = TILE;
        missile_sprite.tab[i].x = i*TILE;
        missile_sprite.tab[i].y = 0;
    }


    //Load explosion
    explosion_sprite.tex = IMG_LoadTexture(ren, "../images/explosion.png");
    if (explosion_sprite.tex == NULL)
    {
        exit_with_error("IMG_LoadTexture");
    }

    explosion_sprite.nb_img = 25;
    explosion_sprite.img_size = TILE;

    int tmp=0;
    int tmp2=0;
    for (int i = 0; i < 25; i++)
    {
        explosion_sprite.tab[i].w = TILE;
        explosion_sprite.tab[i].h = TILE;

        if(i%5 == 0 && i != 0) tmp2 += TILE;
        explosion_sprite.tab[i].x = tmp;
        explosion_sprite.tab[i].y = tmp2;
        tmp = ((i+1)%5 == 0) ? 0 : tmp + TILE;
    }

    //Landmine
    landmine_sprite.tex = IMG_LoadTexture(ren, "../images/mines.png");
    if (landmine_sprite.tex == NULL){
        exit_with_error("IMG_LoadTexture");
    }

    landmine_sprite.img_size = TILE;
    landmine_sprite.nb_img = 10;
    landmine_sprite.nb_step = 5;

    for(int i = 0; i<10; i++){
        landmine_sprite.tab[i].x = i * TILE;
        landmine_sprite.tab[i].y = 0;
        landmine_sprite.tab[i].w = TILE;
        landmine_sprite.tab[i].h = TILE;
    }

    //bomb
    bomb_sprite.tex = IMG_LoadTexture(ren, "../images/bomb.png");
    if (bomb_sprite.tex == NULL){
        exit_with_error("IMG_LoadTexture");
    }

    bomb_sprite.img_size = TILE;
    bomb_sprite.nb_img = 16;
    bomb_sprite.nb_step = 16;

    for(int i = 0; i<16; i++){
        bomb_sprite.tab[i].x = i * TILE;
        bomb_sprite.tab[i].y = 0;
        bomb_sprite.tab[i].h = TILE;
        bomb_sprite.tab[i].w = TILE;
    }

    //TANK
    tank_sprite.tex = IMG_LoadTexture(ren, "../images/tankd.png");
    if (tank_sprite.tex == NULL)
        exit_with_error("IMG_LoadTexture");

    tank_sprite.nb_img = 1;

}

void sprite_clean(void)
{
    if (mario_sprite.tex != NULL)
        SDL_DestroyTexture(mario_sprite.tex);

    if (bird_shot_sprite.tex != NULL)
        SDL_DestroyTexture(bird_shot_sprite.tex);
    if (landmine_sprite.tex != NULL)
        SDL_DestroyTexture(landmine_sprite.tex);
    if (bomb_sprite.tex != NULL)
        SDL_DestroyTexture(bomb_sprite.tex);

}