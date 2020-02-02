#include <stdlib.h>
#include <SDL_image.h>
#include "map.h"
#include "graphics.h"
#include "constants.h"


map_object_t tab[5];
int map[MAP_WIDTH][MAP_HEIGHT];

void* map_allocate(int width, int height){
    /**map = malloc(width * sizeof(int*));
    for (int i = 0; i < width ; i++){
        map[i] = malloc(height * sizeof(int));
    }*/

    for (int i = 0; i<width; i++){
        for ( int j = 0; j< height; j++){
            map[i][j] = 0;
        }
    }

    return (void*)map; 
}

void map_set(int map_object, int x, int y){
    map[x][y] = map_object;
}

int map_get(int x, int y){
    return map[x][y];
}

void map_object_add(const char* path, int nb_sprites, int type, int num){
    map_object_t tmp;
    tmp.tex = IMG_LoadTexture(ren, path);
    tmp.nb_sprites = nb_sprites;
    tmp.type = type;

    tab[num] = tmp;
}

void map_new(int width, int height){
    map_allocate(width, height);
    map_object_add("../images/wall.png", 1, 0, 1);
    map_object_add("../images/ground.png", 1, 0, 2);
    map_object_add("../images/flower.png", 1, 0, 3);
    map_object_add("../images/flower2.png", 1, 0, 4);


    for (int i = 0; i< height; i++){
        map_set(1, 0, i);
    }
    for (int i = 0; i< width; i++){
        map_set(2, i, 11);
    }

    map_set(3, 11, 10);
    map_set(4, 12, 10);
    
    map_set(1, 10, 9);

}

void map_display(){
    for (int i = 0; i< MAP_WIDTH; i++){
        for (int j = 0; j< MAP_HEIGHT; j++){
            if (map_get(i,j))
            {
                tab[map_get(i,j)].dst.x = i*64;
                tab[map_get(i,j)].dst.y = j*64;
                tab[map_get(i,j)].dst.w = 64;
                tab[map_get(i,j)].dst.h = 64;

                SDL_RenderCopyEx(ren, tab[map_get(i,j)].tex, NULL, &tab[map_get(i,j)].dst,0,0,0);
            }
        }
    }
}

/*void edit_mode(int up, int down, int left, int right, int ok, int shift, int q){
    int x = MAP_WIDTH/2;
    int y = MAP_HEIGHT/2;
    int i = 0;
    while (!q)
    {
        while(!ok)
        {
            map_set(0, x, y);
            if(up){
                y--;
            }
            if(down){
                y++;
            }
            if(left){
                x--;
            }
            if(right){
                x++;
            }
            if(shift){
                i++;
                if (i<5)
                    i=0;
            }
            map_set(i, x, y);
    }
}*/

