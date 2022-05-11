#ifndef TNT_IS_DEF
#define TNT_IS_DEF

#include <SDL.h>
#include "constants.h"
#include "timer.h"
#include "object.h"

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

enum{
   MAP_OBJECT_STATE_NORMAL,
   MAP_OBJECT_STATE_DESTROYED,
   MAP_OBJECT_STATE_ACTIVE,
   MAP_OBJECT_STATE_INCTIVE,
};

typedef void (*timer_func_t1)(int x, int y);
typedef struct
{
   int type;
   int type2;
   int state;
   SDL_Texture *tex;
   int nb_sprites;
   SDL_Rect tab[21];
   int anim_next_step;
} map_object_t;


void coin_anim();
void tnt_explode(dynamic_object_t *obj);
void marble_explode(dynamic_object_t *obj);

extern int chain_reaction;


#endif