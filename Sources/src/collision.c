#include "object.h"
#include "map.h"
#include "constants.h"
#include "string.h"
#include "collision.h"

int isInside(dynamic_object_t *obj1, map_object_t obj2 ) {
    if ((obj1->x < (obj2.dst.x + obj2.dst.w)) && ((obj1->x + obj1->sprite->dst.w) > obj2.dst.x) && (obj1->y < (obj2.dst.y + obj2.dst.h)) && ((obj1->sprite->dst.h + obj1->y )> obj2.dst.y)) {
        return 1;
    }
	else {
    	return 0;
	}
}

int collision(dynamic_object_t *obj, int direction){
    int test = map_get(obj->x / TILE, (obj->y / TILE)+2);
    int testb = map_get(obj->x / TILE, (obj->y / TILE));
    int test1 = map_get((obj->x / TILE), obj->y / TILE);
    int test1b = map_get((obj->x / TILE), (obj->y / TILE)+1);
    int test2 = map_get((obj->x / TILE)+1, obj->y / TILE);
    int test2b = map_get((obj->x / TILE)+1, (obj->y / TILE)+1);

    switch (direction)
    {
    case UP:
        if (tab[testb].type == MAP_OBJECT_AIR || !test)
            //map_set(1, obj->x / TILE, (obj->y / TILE));
            return 0;
        break;
    case DOWN:
        if (tab[test].type == MAP_OBJECT_AIR || !test)
            return 0;
        break;
    case LEFT:
        if((tab[test1].type == MAP_OBJECT_AIR || !test1) && (tab[test1b].type == MAP_OBJECT_AIR || !test1b))
            return 0;
        break;
    case RIGHT:
        if((tab[test2].type == MAP_OBJECT_AIR || !test2) && (tab[test2b].type == MAP_OBJECT_AIR || !test2b))
            return 0;
        break;
    default:
        break;
    }

    return 1;
}
