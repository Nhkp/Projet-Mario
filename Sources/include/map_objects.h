#ifndef TNT_IS_DEF
#define TNT_IS_DEF

#include <SDL.h>
#include "constants.h"

enum
{
   MAP_OBJECT_AIR,
   MAP_OBJECT_SOLID,
   MAP_OBJECT_SEMI_SOLID,
   MAP_OBJECT_NUM,
   MAP_OBJECT_LIQUID,
   MAP_OBJECT_COLLECTIBLE,
   MAP_OBJECT_DESTRUCTIBLE,
   MAP_OBJECT_EXPLOSIVE,
   MAP_OBJECT_TRANSPARENT
};

typedef struct
{
   int type;
   int type2;
   SDL_Texture *tex;
   int nb_sprites;
   SDL_Rect dst;
   SDL_Rect tab[21];
   int anim_next_step;
} map_object_t;

void tnt_explode(int x, int y);

#endif