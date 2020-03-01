#include <stdlib.h>
#include <SDL_image.h>
#include "map.h"
#include "graphics.h"
#include "constants.h"

map_object_t tab[7];
int map[MAP_WIDTH][MAP_HEIGHT];

int edition = 0;

void map_allocate(int width, int height)
{
    /***map = malloc(width * sizeof(int*));
    for (int i = 0; i < width ; i++){
        map[i] = malloc(height * sizeof(int));
    }*/

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            map[i][j] = 0;
        }
    }

    return;
}

void map_set(int map_object, int x, int y)
{
    map[x][y] = map_object;
}

int map_get(int x, int y)
{
    return map[x][y];
}

void map_object_add(const char *path, int nb_sprites, int type, int type2, int num)
{
    map_object_t tmp;
    tmp.nb_sprites = nb_sprites;
    tmp.type = type;
    tmp.type2 = type2;
    tmp.anim_next_step = 0;
    if (nb_sprites == 1)
        tmp.tex = IMG_LoadTexture(ren, path);
    else if (nb_sprites > 1)
    {
        tmp.tex = IMG_LoadTexture(ren, path);
        for (int i = 0; i < 21; i++)
        {
            tmp.tab[i].w = TILE;
            tmp.tab[i].h = TILE;
        }
        tmp.tab[0].x = 0; tmp.tab[0].y = 0;
        tmp.tab[1].x = 1 * TILE; tmp.tab[1].y = 0;
        tmp.tab[2].x = 2 * TILE; tmp.tab[2].y = 0;
        tmp.tab[3].x = 3 * TILE; tmp.tab[3].y = 0;
        tmp.tab[4].x = 4 * TILE; tmp.tab[4].y = 0;
        tmp.tab[5].x = 5 * TILE; tmp.tab[5].y = 0;
        tmp.tab[6].x = 6 * TILE; tmp.tab[6].y = 0;
        tmp.tab[7].x = 7 * TILE; tmp.tab[7].y = 0;
        tmp.tab[8].x = 8 * TILE; tmp.tab[8].y = 0;
        tmp.tab[9].x = 9 * TILE; tmp.tab[9].y = 0;
        tmp.tab[10].x = 10 * TILE; tmp.tab[10].y = 0;
        tmp.tab[11].x = 11 * TILE; tmp.tab[11].y = 0;
        tmp.tab[12].x = 12 * TILE; tmp.tab[12].y = 0;
        tmp.tab[13].x = 13 * TILE; tmp.tab[13].y = 0;
        tmp.tab[14].x = 14 * TILE; tmp.tab[14].y = 0;
        tmp.tab[15].x = 15 * TILE; tmp.tab[15].y = 0;
        tmp.tab[16].x = 0; tmp.tab[16].y = TILE;
        tmp.tab[17].x = 1 * TILE; tmp.tab[17].y = TILE;
        tmp.tab[18].x = 2 * TILE; tmp.tab[18].y = TILE;
        tmp.tab[19].x = 3 * TILE; tmp.tab[19].y = TILE;
        tmp.tab[20].x = 4 * TILE; tmp.tab[20].y = TILE;
       
    }

    tab[num] = tmp;
}

void map_new(int width, int height)
{
    map_allocate(width, height);
    map_object_add("../images/wall.png", 1, 1, 6, 1);
    map_object_add("../images/ground.png", 1, 1, 0, 2);
    map_object_add("../images/flower.png", 1, 0, 6, 3);
    map_object_add("../images/flower2.png", 1, 0, 6, 4);
    map_object_add("../images/coin.png", 21, 5, 6, 5);
    map_object_add("../images/tnt.png", 1, 7, 6, 6);

    //Murs
    for (int i = 0; i < height; i++)
    {
        map_set(1, 0, i);
        map_set(1, MAP_WIDTH - 1, i);
    }

    //Sol
    for (int i = 0; i < width; i++)
    {
        map_set(2, i, MAP_HEIGHT - 1);
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

    map_set(5, 18, 13);

    //TNT
    map_set(6, 20, 13);

    map_set(1, 20, 12);
    map_set(1, 20, 14);
    map_set(1, 21, 12);
    map_set(1, 21, 13);
    map_set(1, 21, 14);
}

void map_display()
{

    for (int i = ((x_screen / TILE) - 1 >= 0) ? (x_screen / TILE) - 1 : 0; i < /*(((x_screen+WIN_WIDTH)/TILE)+1 < MAP_WIDTH) ? ((x_screen+WIN_WIDTH)/TILE)+1 :*/ MAP_WIDTH; i++)
    {
        for (int j = ((y_screen / TILE) - 1 >= 0) ? (y_screen / TILE) - 1 : 0; j < /*(((y_screen+WIN_HEIGHT)/TILE)+1 < MAP_HEIGHT) ? ((y_screen+WIN_HEIGHT)/TILE)+1 : */ MAP_HEIGHT; j++)
        {
            if (map_get(i, j) && tab[map_get(i, j)].nb_sprites == 1)
            {
                tab[map_get(i, j)].dst.x = i * TILE - x_screen;
                tab[map_get(i, j)].dst.y = j * TILE - y_screen;
                tab[map_get(i, j)].dst.w = TILE;
                tab[map_get(i, j)].dst.h = TILE;

                SDL_RenderCopyEx(ren, tab[map_get(i, j)].tex, NULL, &tab[map_get(i, j)].dst, 0, 0, 0);
            }
            else if (map_get(i,j) && tab[map_get(i, j)].nb_sprites > 1) //Pour les images animées
            {
                int ans = tab[map_get(i,j)].anim_next_step;

                tab[map_get(i,j)].dst.x = i * TILE - x_screen;
                tab[map_get(i,j)].dst.y = j * TILE - y_screen;
                tab[map_get(i,j)].dst.w = TILE;
                tab[map_get(i,j)].dst.h = TILE;


                SDL_RenderCopyEx(ren, tab[map_get(i,j)].tex, &tab[map_get(i,j)].tab[ans], &tab[map_get(i,j)].dst, 0, 0, 0);
                tab[map_get(i,j)].anim_next_step = (tab[map_get(i,j)].anim_next_step < tab[map_get(i,j)].nb_sprites - 1) ? tab[map_get(i,j)].anim_next_step + 1 : 0;
            }
        }
    }
}


int j = -1;
int x = 10;
int y = 6;
int i = 1;

int edit_mode(int save, int up, int down, int left, int right, int ok, int tab, int q){
    
    map_set(i, x, y);

    if (!edition){
        j = -1;
        x = 10;
        y = 6;
        i = 1;
        edition = 1;
    }

    if (q || ok)
        edition = 0;


    if (j%13){
        if (tab)
        {
            i++;
            if (i>7) i = 1;
            map_set(i, x, y);
        }
        if (up){
            map_set(save, x, y);
            save = map_get(x, y-1);
            y--;
            map_set(i, x, y);
        }
        if (down){
            map_set(save, x, y);
            save = map_get(x, y+1);
            y++;
            map_set(i, x, y);
        }
        if (left){
            map_set(save, x, y);
            save = map_get(x-1, y);
            x--;
            map_set(i, x, y);
        }
        if (right){
            map_set(save, x, y);
            save = map_get(x+1, y);
            x++;
            map_set(i, x, y);
        }
    }
    j++;
    if (x > MAP_WIDTH-1 || x < 0)
        x=0;
    if (y > MAP_HEIGHT-1 || y < 0)
        y=0;

    SDL_Delay(50);
    return save;
}
