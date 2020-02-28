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
    int d = map_get(obj->x / TILE, (obj->y / TILE)+2);
    int u = map_get(obj->x / TILE, (obj->y / TILE));
    int l = map_get((obj->x / TILE), obj->y / TILE);
    int dl = map_get((obj->x / TILE), (obj->y / TILE)+1);
    int ul = map_get((obj->x / TILE), (obj->y / TILE)-1);
    int r = map_get((obj->x / TILE)+1, obj->y / TILE);
    int dr = map_get((obj->x / TILE)+1, (obj->y / TILE)+1);
    int ur = map_get((obj->x / TILE)+1, (obj->y / TILE)-1);

    switch (direction)
    {
    case UP:
        if (tab[u].type == MAP_OBJECT_AIR || !u)
            //map_set(1, obj->x / TILE, (obj->y / TILE));
            return 0;
        else return tab[u].type;
        break;
    case DOWN:
        if (tab[d].type == MAP_OBJECT_AIR || !d)
            return 0;
        else if (tab[d].type == 0 || tab[d].type == 1)
            return 1;
        break;
    case LEFT:
        if((tab[l].type == MAP_OBJECT_AIR || !l))
            return 0;
        else if (tab[l].type == 0 || tab[l].type == 1)
            return 1;
        break;
    case DOWN_LEFT:
        if((tab[dl].type == MAP_OBJECT_AIR || !dl))
            return 0;
        else if (tab[dl].type == 0 || tab[dl].type == 1)
            return 1;
        break;
    case UP_LEFT:
        if((tab[ul].type == MAP_OBJECT_AIR || !ul))
            return 0;
        else if (tab[ul].type == 0 || tab[ul].type == 1)
            return 1;
        break;
    case RIGHT:
        if((tab[r].type == MAP_OBJECT_AIR || !r))
            return 0;
        else if (tab[r].type == 0 || tab[r].type == 1)
            return 1;
        break;
    case DOWN_RIGHT:
        if((tab[dr].type == MAP_OBJECT_AIR || !dr))
            return 0;
        else if (tab[dr].type == 0 || tab[dr].type == 1)
            return 1;
        break;
    case UP_RIGHT:
        if((tab[ur].type == MAP_OBJECT_AIR || !ur))
            return 0;
        else if (tab[ur].type == 0 || tab[ur].type == 1)
            return 1;
        break;
    default:
        break;
    }

    return 0;
}
