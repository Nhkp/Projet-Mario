
#ifndef GRAPHICS_IS_DEF
#define GRAPHICS_IS_DEF

#include <SDL.h>
#include "object.h"



#define GFX_NONE      0
#define GFX_BLINK     1
#define GFX_FADE      2
#define GFX_CENTER    4
#define GFX_SCALE     8
#define GFX_ROTATE   16


void graphics_init (Uint32 render_flags, char *background_skin);
void graphics_render (void);
void graphics_clean (void);
void move_trees(int sens);
void graphics_render_trees (SDL_Texture *tex, int factor);
void graphics_render_scrolling_trees(SDL_Texture *tex, int factor, int sens);


extern SDL_Renderer *ren;

#endif
