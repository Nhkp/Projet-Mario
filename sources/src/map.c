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
#include "mario.h"

#define save write(fd, &buf, sizeof(int));
#define load read(fd, &buf, sizeof(int));

map_object_t tab[MAP_OBJECTS_NB];
int map[MAP_WIDTH][MAP_HEIGHT];
//int **map;

void map_allocate(int width, int height){
    /*map = malloc(width * sizeof(*map));
    for (int i = 0; i < width ; i++){
        map[i] = malloc(height * sizeof(**map));
    }*/

    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            map[i][j] = 0;
}

void map_set(int map_object, int x, int y){
    map[x][y] = map_object;
}

int map_get(int x, int y){
    return map[x][y];
}

int get_map_object_type(int map_object, int type){
    if(!type || type == 1) return tab[map_object].type;
    if(type == 2) return tab[map_object].type2;

    return -1;
}
int get_type(int x, int y, int type){
    if(!type || type == 1) return tab[map_get(x,y)].type;
    if(type == 2) return tab[map_get(x,y)].type2;

    return -1;
}

int get_state(int x, int y){
    return tab[map_get(x, y)].state;
}


void set_state(int x, int y, int state){
    tab[map_get(x, y)].state = state;
}

int map_width(){
    return MAP_WIDTH;
}

int map_height(){
    return MAP_HEIGHT;
}

void map_object_add(const char *path, int nb_sprites, int type, int type2){
    static int cnt = 1;
    map_object_t tmp;
    tmp.nb_sprites = nb_sprites;
    tmp.type = type;
    tmp.type2 = type2;
    tmp.anim_next_step = 0;
    tmp.state = MAP_OBJECT_STATE_NORMAL;
    tmp.tex = IMG_LoadTexture(ren, path);
    if (nb_sprites > 1){
        for (int i = 0; i < 21; i++){
            tmp.tab[i].w = TILE;
            tmp.tab[i].h = TILE;

            if(i<16){
                tmp.tab[i].x = i * TILE;
                tmp.tab[i].y = 0;
            }
            else{
                tmp.tab[i].x = (i-16) * TILE;
                tmp.tab[i].y = TILE;
            }
        }
    }
    tab[cnt] = tmp;
    cnt++;
}

void map_new(int width, int height){
    map_allocate(width, height);

    /* 1 */map_object_add("../images/wall.png", 1, MAP_OBJECT_SOLID, MAP_OBJECT_DESTRUCTIBLE);
    /* 2 */map_object_add("../images/ground.png", 1, MAP_OBJECT_SOLID, MAP_OBJECT_SOLID);
    /* 3 */map_object_add("../images/flower.png", 1, MAP_OBJECT_AIR, MAP_OBJECT_DESTRUCTIBLE);
    /* 4 */map_object_add("../images/flower2.png", 1, MAP_OBJECT_AIR, MAP_OBJECT_DESTRUCTIBLE);
    /* 5 */map_object_add("../images/coin.png", 21, MAP_OBJECT_AIR, MAP_OBJECT_COLLECTIBLE);
    /* 6 */map_object_add("../images/tnt.png", 1, MAP_OBJECT_SOLID, MAP_OBJECT_EXPLOSIVE);
    /* 7 */map_object_add("../images/peach1.png", 1, MAP_OBJECT_AIR, MAP_OBJECT_TRANSPARENT);
    /* 8 */map_object_add("../images/peach2.png", 1, MAP_OBJECT_AIR, MAP_OBJECT_TRANSPARENT);
    /* 9 */map_object_add("../images/floor.png", 1, MAP_OBJECT_SEMI_SOLID, MAP_OBJECT_TRANSPARENT);
    /* 10 */map_object_add("../images/herb.png", 1, MAP_OBJECT_AIR, MAP_OBJECT_DESTRUCTIBLE);
    /* 11 */map_object_add("../images/grass.png", 1, MAP_OBJECT_SOLID, MAP_OBJECT_DESTRUCTIBLE);
    /* 12 */map_object_add("../images/marble.png", 1, MAP_OBJECT_SEMI_SOLID, MAP_OBJECT_EXPLOSIVE);
    /* 13 */map_object_add("../images/marble2.png", 1, MAP_OBJECT_SEMI_SOLID, MAP_OBJECT_SOLID);

    //Murs
    for (int i = 0; i < height; i++){
        map_set(1, 0, i);
        map_set(1, MAP_WIDTH - 1, i);
    }

    //Sol
    for (int i = 0; i < width; i++)
        map_set(2, i, MAP_HEIGHT - 1);
}

//Affichage des map_objects


void save_map(char *map_path){
    write(1, "save\n", 6);

    u_int32_t buf;
    // char path[18] = {"../maps/"};
    // if (map_path == NULL)
    //     strcat(path, "new_map");
    // else
    //     strcat(path, map_path);

    int fd = creat((map_path == NULL)?"maps/new_map":map_path, 0666);
    printf("Map '%s' saved\n",(map_path == NULL)?"maps/new_map":map_path);

    buf = map_width(); save;
    buf = map_height(); save;

    write(fd, map, MAP_WIDTH * MAP_HEIGHT * sizeof(int));

    close(fd);
}

void load_map(char *map_path){
    write(1, "load\n", 6);

    int buf, fd;

    if(map_path == NULL)
        printf("Map inexistante\n");
    fd = open(map_path, O_RDONLY);

    load; int width = buf;
    load; int height = buf;

    /* 1 */map_object_add("../images/wall.png", 1, MAP_OBJECT_SOLID, MAP_OBJECT_DESTRUCTIBLE);
    /* 2 */map_object_add("../images/ground.png", 1, MAP_OBJECT_SOLID, MAP_OBJECT_SOLID);
    /* 3 */map_object_add("../images/flower.png", 1, MAP_OBJECT_AIR, MAP_OBJECT_DESTRUCTIBLE);
    /* 4 */map_object_add("../images/flower2.png", 1, MAP_OBJECT_AIR, MAP_OBJECT_DESTRUCTIBLE);
    /* 5 */map_object_add("../images/coin.png", 21, MAP_OBJECT_AIR, MAP_OBJECT_COLLECTIBLE);
    /* 6 */map_object_add("../images/tnt.png", 1, MAP_OBJECT_SOLID, MAP_OBJECT_EXPLOSIVE);
    /* 7 */map_object_add("../images/peach1.png", 1, MAP_OBJECT_AIR, MAP_OBJECT_TRANSPARENT);
    /* 8 */map_object_add("../images/peach2.png", 1, MAP_OBJECT_AIR, MAP_OBJECT_TRANSPARENT);
    /* 9 */map_object_add("../images/floor.png", 1, MAP_OBJECT_SEMI_SOLID, MAP_OBJECT_TRANSPARENT);
    /* 10 */map_object_add("../images/herb.png", 1, MAP_OBJECT_AIR, MAP_OBJECT_DESTRUCTIBLE);
    /* 11 */map_object_add("../images/grass.png", 1, MAP_OBJECT_SOLID, MAP_OBJECT_DESTRUCTIBLE);
    /* 12 */map_object_add("../images/marble.png", 1, MAP_OBJECT_SEMI_SOLID, MAP_OBJECT_EXPLOSIVE);
    /* 13 */map_object_add("../images/marble2.png", 1, MAP_OBJECT_SEMI_SOLID, MAP_OBJECT_SOLID);

    read(fd, map, width * height * sizeof(int));

    close(fd);
}