#include <SDL_image.h>

#include "graphics.h"
#include "error.h"
#include "debug.h"
#include "constants.h"
//#include "bird.h"
#include "sprite.h"
#include "missile.h"
#include "mario.h"

sprite_t bird_shot_sprite;
sprite_t mario_sprite;
sprite_t explosion_sprite;

sprite_t wall_sprite;
sprite_t ground_sprite;

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

    mario_sprite.original_dir = 1;

    for (int i = 0; i < 11; i++)
    {
        mario_sprite.tab[i].w = 64;
        mario_sprite.tab[i].h = 128;
    }

    mario_sprite.tab[0].x = 0;
    mario_sprite.tab[0].y = 0;
    mario_sprite.tab[1].x = 64;
    mario_sprite.tab[1].y = 0;
    mario_sprite.tab[2].x = 128;
    mario_sprite.tab[2].y = 0;
    mario_sprite.tab[3].x = 192;
    mario_sprite.tab[3].y = 0;
    mario_sprite.tab[4].x = 256;
    mario_sprite.tab[4].y = 0;
    mario_sprite.tab[5].x = 320;
    mario_sprite.tab[5].y = 0;
    mario_sprite.tab[6].x = 384;
    mario_sprite.tab[6].y = 0;
    mario_sprite.tab[7].x = 448;
    mario_sprite.tab[7].y = 0;
    mario_sprite.tab[8].x = 512;
    mario_sprite.tab[8].y = 0;
    mario_sprite.tab[9].x = 576;
    mario_sprite.tab[9].y = 0;
    mario_sprite.tab[10].x = 640;
    mario_sprite.tab[10].y = 0;

    //Load shot image
    bird_shot_sprite.tex = IMG_LoadTexture(ren, "../images/shot.png");
    if (bird_shot_sprite.tex == NULL)
    {
        exit_with_error("IMG_LoadTexture");
    }

    bird_shot_sprite.original_dir = 1;
    bird_shot_sprite.nb_img = 1;

    //Load explosion
    explosion_sprite.tex = IMG_LoadTexture(ren, "../images/explosion.png");
    if (explosion_sprite.tex == NULL)
    {
        exit_with_error("IMG_LoadTexture");
    }

    explosion_sprite.nb_img = 25;
    explosion_sprite.img_size = 64;

    for (int i = 0; i < 15; i++)
    {
        explosion_sprite.tab[i].w = 64;
        explosion_sprite.tab[i].h = 64;
    }

    explosion_sprite.tab[0].x = 0;
    explosion_sprite.tab[0].x = 0;
    explosion_sprite.tab[1].x = 64;
    explosion_sprite.tab[1].x = 0;
    explosion_sprite.tab[2].x = 128;
    explosion_sprite.tab[2].x = 0;
    explosion_sprite.tab[3].x = 192;
    explosion_sprite.tab[3].x = 0;
    explosion_sprite.tab[4].x = 256;
    explosion_sprite.tab[4].x = 0;
    explosion_sprite.tab[5].x = 0;
    explosion_sprite.tab[5].x = 64;
    explosion_sprite.tab[6].x = 64;
    explosion_sprite.tab[6].x = 64;
    explosion_sprite.tab[7].x = 128;
    explosion_sprite.tab[7].x = 64;
    explosion_sprite.tab[8].x = 192;
    explosion_sprite.tab[8].x = 64;
    explosion_sprite.tab[9].x = 256;
    explosion_sprite.tab[9].x = 64;
    explosion_sprite.tab[10].x = 0;
    explosion_sprite.tab[10].x = 128;
    explosion_sprite.tab[11].x = 64;
    explosion_sprite.tab[11].x = 128;
    explosion_sprite.tab[12].x = 128;
    explosion_sprite.tab[12].x = 128;
    explosion_sprite.tab[13].x = 192;
    explosion_sprite.tab[13].x = 128;
    explosion_sprite.tab[14].x = 256;
    explosion_sprite.tab[14].x = 128;
    explosion_sprite.tab[15].x = 0;
    explosion_sprite.tab[15].x = 192;
    explosion_sprite.tab[16].x = 64;
    explosion_sprite.tab[16].x = 192;
    explosion_sprite.tab[17].x = 128;
    explosion_sprite.tab[17].x = 192;
    explosion_sprite.tab[18].x = 192;
    explosion_sprite.tab[18].x = 192;
    explosion_sprite.tab[19].x = 256;
    explosion_sprite.tab[19].x = 192;
    explosion_sprite.tab[20].x = 0;
    explosion_sprite.tab[20].x = 256;
    explosion_sprite.tab[21].x = 64;
    explosion_sprite.tab[21].x = 256;
    explosion_sprite.tab[22].x = 128;
    explosion_sprite.tab[22].x = 256;
    explosion_sprite.tab[23].x = 192;
    explosion_sprite.tab[23].x = 256;
    explosion_sprite.tab[24].x = 256;
    explosion_sprite.tab[24].x = 256;
}

void sprite_clean(void)
{
    if (mario_sprite.tex != NULL)
    {
        SDL_DestroyTexture(mario_sprite.tex);
    }

    if (bird_shot_sprite.tex != NULL)
    {
        SDL_DestroyTexture(bird_shot_sprite.tex);
    }
}