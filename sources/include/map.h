#ifndef MAP_IS_DEF
#define MAP_IS_DEF

#include <SDL.h>
#include "constants.h"
#include "map_objects.h"
#include "object.h"


extern int map[MAP_WIDTH][MAP_HEIGHT];
extern map_object_t tab[14];

void map_new(int width, int height);
void map_allocate(int width, int height);
void map_set(int map_object, int x, int y);
void map_object_add(const char *path, int nb_sprites, int type, int type2);
int map_get(int x, int y);
int map_width();
int map_height();

int get_map_object_type(int map_object, int type);
int get_type(int x, int y, int type);
int get_state(int x, int y);
void set_state(int x, int y, int state);

void save_map(char *map_path);
void load_map(char *map_path);

#endif