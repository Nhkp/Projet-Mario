#include <stdlib.h>
#include <SDL_image.h>
#include "map.h"
#include "graphics.h"
#include "constants.h"


map_object_t tab[6];
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
    tmp.nb_sprites = nb_sprites;
    tmp.type = type;
    tmp.anim_next_step = 0;
    if(nb_sprites == 1)
        tmp.tex = IMG_LoadTexture(ren, path);
    else
    {
        tmp.tex = IMG_LoadTexture(ren, path);
        for (int k = 0; k<16; k++){
            for (int i  = 0; i< 256; i +=64){
                for (int j  = 0; j< 256; j +=64){
                    tmp.tab[k].x = i; 
                    tmp.tab[k].y = j;
                }
            }
        }
    }
    

    tab[num] = tmp;
}

void map_new(int width, int height){
    map_allocate(width, height);
    map_object_add("../images/wall.png", 1, 0, 1);
    map_object_add("../images/ground.png", 1, 0, 2);
    map_object_add("../images/flower.png", 1, 2, 3);
    map_object_add("../images/flower2.png", 1, 2, 4);
    map_object_add("../images/coin.png", 16, 2, 5);


    for (int i = 0; i< height; i++){
        map_set(1, 0, i);
    }
    for (int i = 0; i< width; i++){
        map_set(2, i, 11);
    }

    map_set(3, 9, 10);
    map_set(4, 12, 10);
    map_set(5, 10, 6);
    
    map_set(1, 6, 9);

}

void map_display(){
    for (int i = 0; i< MAP_WIDTH; i++){
        for (int j = 0; j< MAP_HEIGHT; j++){
            if (map_get(i,j) && tab[map_get(i,j)].nb_sprites == 1)
            {
                tab[map_get(i,j)].dst.x = i*64;
                tab[map_get(i,j)].dst.y = j*64;
                tab[map_get(i,j)].dst.w = 64;
                tab[map_get(i,j)].dst.h = 64;

                SDL_RenderCopyEx(ren, tab[map_get(i,j)].tex, NULL, &tab[map_get(i,j)].dst,0,0,0);
            }
            else if (map_get(i,j)) //Pour les images animées
            {
                int ans = tab[map_get(i,j)].anim_next_step;

                tab[map_get(i,j)].dst.x = i*64;
                tab[map_get(i,j)].dst.x = j*64;
                tab[map_get(i,j)].dst.w = 64;
                tab[map_get(i,j)].dst.h = 64;


                SDL_RenderCopyEx(ren, tab[map_get(i,j)].tex, &tab[map_get(i,j)].tab[ans], &tab[map_get(i,j)].dst, 0, 0, 0);

                if (tab[map_get(i,j)].anim_next_step > tab[map_get(i,j)].nb_sprites){
                    tab[map_get(i,j)].anim_next_step = 0;
                }
                else
                {
                    tab[map_get(i,j)].anim_next_step ++;
                }
                
            }
        }
    }
}

    int x = 6;
    int y = 6;
    int i = 0;
int edit_mode(int up, int down, int left, int right, int ok, int shift, int q){

    printf("je suis dans l'edition");
    map_set(0, x, y);
    if (x > MAP_WIDTH-1 || x < 0)
        x=0;
    if (y > MAP_HEIGHT-1 || y < 0)
        y=0;
    if (up)
    {
        y--;
    }
    if (down)
    {
        y++;
    }
    if (left)
    {
        x--;
    }
    if (right)
    {
        x++;
    }
    if (shift)
    {
        i++;
        if (i > 3)
            i = 0;
    }

    //SDL_RenderCopyEx(ren, tab[i].tex, NULL, &tab[map_get(x, y)].dst, 0, 0, 0);

    //if (ok)
        map_set(i, x, y);

    if (q)
        return 0;
    return 0;
}

