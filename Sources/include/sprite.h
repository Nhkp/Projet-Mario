#ifndef SPRITE_IS_DEF
#define SPRITE_IS_DEF

#include <SDL.h>

typedef struct
{
    SDL_Texture *tex;
    SDL_Rect src, dst;
    int original_dir;
    int nb_img;
    int nb_step;
    int img_size;
    SDL_Rect tab[25];
} sprite_t;

extern sprite_t mario_sprite;
extern sprite_t bird_shot_sprite;
extern sprite_t explosion_sprite;
extern sprite_t cursor_sprite;

void sprite_init(void);

void sprite_clean(void);

#endif
