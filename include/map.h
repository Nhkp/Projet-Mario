#ifndef MAP_IS_DEF
#define MAP_IS_DEF

#include <SDL.h>
#include "constants.h"

enum {
MAP_OBJECT_SOLID,
MAP_OBJECT_SEMI_SOLID,
MAP_OBJECT_AIR,
MAP_OBJECT_NUM
};

typedef struct {
   int type;
   SDL_Texture *tex;
   int nb_sprites;
   SDL_Rect dst;
   SDL_Rect tab[16];
   int anim_next_step;
} map_object_t;

extern int map[MAP_WIDTH][MAP_HEIGHT];
extern map_object_t tab[6];

void map_new(int width, int height);
void* map_allocate(int width, int height);
void map_set(int map_object, int x, int y);
int map_get(int x, int y);
void map_object_add(const char* path, int nb_sprites, int type, int num);

void map_display();
int edit_mode(int up, int down, int left, int right, int ok, int shift, int q);


#endif