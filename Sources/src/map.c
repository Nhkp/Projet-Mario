#include <stdlib.h>
#include "map.h"
#include "graphics.h"

int **map;

map_object_t tab[2];

void map_allocate(int width, int height){
    **map = malloc(sizeof(*map) * height);
 
    for (int i = 0; i < height; i++)
        map[i] = malloc(sizeof(**map) * width);
}

void map_set(int map_object, int x, int y){
    map[x][y] = map_object;
}

int map_get(int x, int y){
    return map[x][y];
}

void map_object_add(const char* path, int nb_sprites, int type){
    static int x;

    map_object_t tmp;
    //tmp.path
    //tab[x] = 
    //SDL_RenderCopyEx(ren, IMG_LoadTexture(ren, path), NULL, &dst, 0, NULL, 0);

    x++;
}

void map_new(unsigned width, unsigned height){
    map_allocate(width, height);
    map_object_add("../images/wall.png", 1, 1);
    map_set(tab[0].type, 300, 300);
}