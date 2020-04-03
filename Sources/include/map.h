#ifndef MAP_IS_DEF
#define MAP_IS_DEF

#include <SDL.h>
#include "constants.h"
#include "map_objects.h"
#include "object.h"

extern dynamic_object_t cursor;
extern int edition;

extern int map[MAP_WIDTH][MAP_HEIGHT];
extern map_object_t tab[9];

void map_new(int width, int height);
void map_allocate(int width, int height);
void map_set(int map_object, int x, int y);
int map_get(int x, int y);
void map_object_add(const char *path, int nb_sprites, int type, int type2, int num);

void map_display();
void edit_mode(dynamic_object_t *obj, int up, int down, int left, int right, int ok, int tabulation, int q);

void save_map();
int map_width();
int map_heigth();
int map_objects();
char* map_get_name(int i);
int map_get_frames(int i);
int map_get_type(int i);
int map_get_type2(int i);

#endif