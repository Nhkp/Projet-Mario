
#ifndef GRAPHICS_IS_DEF
#define GRAPHICS_IS_DEF

#include <SDL.h>
#include "object.h"

#define GFX_NONE 0
#define GFX_BLINK 1
#define GFX_FADE 2
#define GFX_CENTER 4
#define GFX_SCALE 8
#define GFX_ROTATE 16

void graphics_init(Uint32 render_flags, char *background_skin);
void graphics_render(void);
void graphics_clean(void);
void graphics_render_trees(SDL_Texture *tex, int factor);
void animation_render_objects(void);
void scrolling_screen(int x, int y);
void map_display();


extern int x_screen;
extern int y_screen;

extern SDL_Renderer *ren;

#endif
