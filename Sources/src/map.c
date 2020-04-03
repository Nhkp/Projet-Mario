#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <SDL_image.h>
#include <string.h>
#include "map.h"
#include "graphics.h"
#include "constants.h"
#include "animation.h"
#include "sprite.h"

dynamic_object_t cursor;
map_object_t tab[9];
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

int map_width(){
    return MAP_WIDTH;
}

int map_heigth(){
    return MAP_HEIGHT;
}

int map_objects(){
    int cmpt = 0;
    for (int i = 0; i < MAP_WIDTH; i++){
        for (int j = 0; j < MAP_HEIGHT; j++){
            if (map[i][j]) cmpt++;
        }
    }

    return cmpt;
}

char* map_get_name(int i){
    char name[25];
    char *p = name;

    switch(i){
        case 1:
            strcpy(name, "../images/wall.png");
            break;
        case 2:
            strcpy(name, "../images/ground.png");
            break;
        case 3:
            strcpy(name, "../images/flower.png");
            break;
        case 4:
            strcpy(name, "../images/flower2.png");
            break;
        case 5:
            strcpy(name, "../images/coin.png");
            break;
        case 6:
            strcpy(name, "../images/tnt.png");
            break;
        case 7:
            strcpy(name, "../images/peach1.png");
            break;
        case 8:
            strcpy(name, "../images/peach2.png");
            break;
        default:
            break;
    }

    return p;
}

int map_get_frames(int i){
    switch(i){
        case 5:
            return 21 ;
        default:
            return 1;
    }
}

int map_get_type(int i){
    switch(i){
        case 1:
            return 1 ;
        case 2:
            return 1 ;
        case 3:
            return 0 ;
        case 4:
            return 0 ;
        case 5:
            return 5 ;
        case 6:
            return 7 ;
        case 7:
            return 7 ;
        case 8:
            return 7 ;
        default:
            return 0;
    }
}

int map_get_type2(int i){
    switch(i){
        case 1:
            return 6 ;
        case 2:
            return 0 ;
        case 3:
            return 6 ;
        case 4:
            return 6 ;
        case 5:
            return 6 ;
        case 6:
            return 6 ;
        case 7:
            return 6 ;
        case 8:
            return 6 ;
        default:
            return 0;
    }
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
    map_object_add("../images/peach1.png", 1, 7, 6, 7);
    map_object_add("../images/peach2.png", 1, 7, 6, 8);

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
    map_set(3, 9, 15);
    map_set(4, 12, 15);

    //blocs libres
    map_set(1, 6, 14);
    map_set(1, 4, 15);
    map_set(1, 8, 13);

    //escalier
    map_set(1, 13, 12);
    map_set(1, 14, 11);
    map_set(1, 15, 10);

    map_set(5, 18, 14);

    //Peach
    map_set(7, 48, 14);
    map_set(8, 48, 15);

    //TNT
    map_set(6, 20, 14);

    map_set(1, 20, 13);
    map_set(1, 20, 15);
    map_set(1, 21, 13);
    map_set(1, 21, 14);
    map_set(1, 21, 15);
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

void edit_mode(dynamic_object_t *obj, int up, int down, int left, int right, int ok, int tabulation, int q){
    int x, y;

    if (!edition){
        x = 9;
        y = 9;
        edition = 1;
    }
    else
    {
        x = obj->x/TILE;
        y = obj->y/TILE;
    }

    //Test de sortie
    if (q) edition = 0;

    //Sélection de la texture
    if (tabulation) (obj->anim_next_step + 1 > 9)? obj->anim_next_step = 1 : obj->anim_next_step++;

    //Déplacement du curseur
    if (up) y--;
    if (down) y++;
    if (left) x--;
    if (right) x++;
    if (x > MAP_WIDTH - 1 || x < 0) x = 0;
    if (y > MAP_HEIGHT - 1 || y < 0) y = 0;
    obj->x = x*TILE;
    obj->y = y*TILE;

    //Synchro sprite
    cursor_sprite.nb_img = tab[obj->anim_next_step].nb_sprites;
    if (cursor_sprite.nb_img > 1)
        for (int i = 0; i < tab[obj->anim_next_step].nb_sprites; i++)
            cursor_sprite.tab[i] = tab[obj->anim_next_step].tab[i];
    else cursor_sprite.tex = tab[obj->anim_next_step].tex;

    //Application de la texture
    if(ok) map_set(obj->anim_next_step, x, y);

    SDL_Delay(50);
}

void save_map(){
    printf("save\n");
    int tmp;
    char tmpc;
    int fd = creat("../maps/test", 0666);

    tmp = map_width();
    write(fd, &tmp, 1);
    tmp = map_heigth();
    write(fd, &tmp, 1);
    tmp = map_objects();
    write(fd, &tmp, 1);

    for(int i = 1; i < map_objects()+1; i++){
        tmpc = *map_get_name(i);
        write(fd, &tmpc, 1);
        tmp = map_get_frames(i);
        write(fd, &tmp, 1);
        tmp = map_get_type(i);
        write(fd, &tmp, 1);
        tmp = map_get_type2(i);
        write(fd, &tmp, 1);
    }

    for (int i = 0; i < MAP_WIDTH; i++){
        for (int j = 0; j < MAP_HEIGHT; j++){
            tmp = map_get(i, j);
            write(fd, &tmp, 10);
        }
    }

    close(fd);
}
