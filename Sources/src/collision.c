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
    int d2 = map_get(obj->x / TILE, (obj->y / TILE)+2);
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
        if (!tab[u].type || !u)
            return 0;
        else return tab[u].type;
        break;
    case DOWN2:
        if (!tab[d2].type || !d2)
            return 0;
        else return tab[d2].type;
        break;
    case LEFT:
        if(!(tab[l].type || !l))
            return 0;
        else return tab[l].type;
        break;
    case DOWN_LEFT:
        if((!tab[dl].type || !dl))
            return 0;
        else return tab[dl].type;
        break;
    case UP_LEFT:
        if((!tab[ul].type || !ul))
            return 0;
        else return tab[ul].type;
        break;
    case RIGHT:
        if((!tab[r].type || !r))
            return 0;
        else return tab[r].type;
        break;
    case DOWN_RIGHT:
        if((!tab[dr].type || !dr))
            return 0;
        else return tab[dr].type;
        break;
    case UP_RIGHT:
        if((!tab[ur].type || !ur))
            return 0;
        else return tab[ur].type;
        break;
    default:
        return 0;
        break;
    }

    return 0;
}
