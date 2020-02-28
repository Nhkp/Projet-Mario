#include <stdlib.h>
#include <SDL_image.h>
#include "map.h"
#include "graphics.h"
#include "constants.h"

map_object_t tab[7];
int map[MAP_WIDTH][MAP_HEIGHT];

int edition = 0;

void map_allocate(int width, int height){
    /***map = malloc(width * sizeof(int*));
    for (int i = 0; i < width ; i++){
        map[i] = malloc(height * sizeof(int));
    }*/

    for (int i = 0; i<width; i++){
        for ( int j = 0; j< height; j++){
            map[i][j] = 0;
        }
    }

    return; 
}

void map_set(int map_object, int x, int y){
    map[x][y] = map_object;
}

int map_get(int x, int y){
    return map[x][y];
}

void map_object_add(const char* path, int nb_sprites, int type, int type2, int num){
    map_object_t tmp;
    tmp.nb_sprites = nb_sprites;
    tmp.type = type;
    tmp.type2 = type2;
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
    map_object_add("../images/wall.png", 1, 0, 6, 1);
    map_object_add("../images/ground.png", 1, 0, 0, 2);
    map_object_add("../images/flower.png", 1, 2, 6, 3);
    map_object_add("../images/flower2.png", 1, 2, 6, 4);
    map_object_add("../images/coin.png", 16, 2, 0, 5);
    map_object_add("../images/tnt.png", 1, 6, 7, 6);

    //Murs
    for (int i = 0; i< height; i++){
        map_set(1, 0, i);
        map_set(1, MAP_WIDTH-1, i);
    }

    //Sol
    for (int i = 0; i< width; i++){
        map_set(2, i, MAP_HEIGHT-1);
    }

    //fleurs
    map_set(3, 9, 14);
    map_set(4, 12, 14);
    
    //blocs libres
    map_set(1, 6, 13);
    map_set(1, 4, 14);
    map_set(1, 8, 12);

    //escalier
    map_set(1, 13, 11);
    map_set(1, 14, 10);
    map_set(1, 15, 9);
    
    //TNT
    map_set(6, 20, 13);

    map_set(1, 20, 12);
    map_set(1, 20, 14);
    map_set(1, 21, 12);
    map_set(1, 21, 13);
    map_set(1, 21, 14);

}

void map_display(){

    for (int i = ((x_screen/TILE)-1 >= 0)?(x_screen/TILE)-1 : 0; i< /*(((x_screen+WIN_WIDTH)/TILE)+1 < MAP_WIDTH) ? ((x_screen+WIN_WIDTH)/TILE)+1 :*/ MAP_WIDTH; i++){
        for (int j = ((y_screen/TILE)-1 >= 0)?(y_screen/TILE)-1 : 0; j< /*(((y_screen+WIN_HEIGHT)/TILE)+1 < MAP_HEIGHT) ? ((y_screen+WIN_HEIGHT)/TILE)+1 : */MAP_HEIGHT; j++){
            if (map_get(i,j) && tab[map_get(i,j)].nb_sprites == 1)
            {
                //cette ligne
                tab[map_get(i,j)].dst.x = i*TILE - x_screen;
                tab[map_get(i,j)].dst.y = j*TILE - y_screen;
                tab[map_get(i,j)].dst.w = TILE;
                tab[map_get(i,j)].dst.h = TILE;

                SDL_RenderCopyEx(ren, tab[map_get(i,j)].tex, NULL, &tab[map_get(i,j)].dst,0,0,0);
            }
            /*else if (map_get(i,j)) //Pour les images animées
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
                
            }*/
        }
    }
}

    
/*int edit_mode(int up, int down, int left, int right, int ok, int shift, int q){
    
    int x = 6;
    int y = 6;
    int i = 1;
    
    if (up) y--;
    if (down) y++;
    if (left) x--;
    if (right) x++;
    if (shift)
    {
        i++;
        if (i > 3) i = 0;
    }
    if (q)
        edition = 0;
    if (ok)
        map_set(i, x, y);
    if (x > MAP_WIDTH-1 || x < 0)
        x=0;
    if (y > MAP_HEIGHT-1 || y < 0)
        y=0;

    tab[map_get(x,y)].dst.x = x-(x_screen/TILE);
    tab[map_get(x,y)].dst.y = y-(y_screen/TILE);
    tab[map_get(x,y)].dst.w = TILE;
    tab[map_get(x,y)].dst.h = TILE;
    
    SDL_RenderCopyEx(ren, tab[i].tex, NULL, &tab[map_get(x, y)].dst, 0, 0, 0);

    return 0;
}*/
