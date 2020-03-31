#include "object.h"
#include "map.h"
#include "constants.h"
#include "string.h"
#include "collision.h"
#include "map_objects.h"

int collision(dynamic_object_t *obj, int direction){
    int d2a = map_get((obj->x + 16) / TILE, (obj->y / TILE) + 2);
    int d2b = map_get((obj->x + TILE-16) / TILE, (obj->y / TILE) + 2);
    
    int ua = map_get((obj->x) / TILE, (obj->y / TILE));
    int ub = map_get((obj->x + TILE) / TILE, (obj->y / TILE));
    //int u = map_get((obj->x / TILE), (obj->y / TILE)-1);
    
    int l = map_get((obj->x / TILE), obj->y / TILE);
    //A retoucher
    int tmp = floor(((obj->x == TILE)? obj->x-1 : obj->x) / TILE);
    int dl = map_get(tmp, (obj->y / TILE) + 1);
    
    int ul = map_get((obj->x / TILE), (obj->y / TILE) - 1);
    int r = map_get((obj->x / TILE) + 1, obj->y / TILE);
    int dr = map_get((obj->x / TILE) + 1, (obj->y / TILE) + 1);
    int ur = map_get((obj->x / TILE) + 1, (obj->y / TILE) - 1);

    switch (direction)
    {
    case UP:
        if ((!tab[ua].type && !tab[ub].type) || (!ua && !ub)) return 0;
        else if (ua) return tab[ua].type;
        else return tab[ub].type;
        break;
    case DOWN2:
        if ((!tab[d2a].type && !tab[d2b].type) || (!d2a && !d2b)) return 0;
        else if (d2a) return tab[d2a].type;
        else return tab[d2b].type;
        break;
    case LEFT:
        if (!(tab[l].type || !l)) return 0;
        else return tab[l].type;
        break;
    case DOWN_LEFT:
        if ((!tab[dl].type || !dl)) return 0;
        else return tab[dl].type;
        break;
    case UP_LEFT:
        if ((!tab[ul].type || !ul)) return 0;
        else return tab[ul].type;
        break;
    case RIGHT:
        if (!tab[r].type || !r) return 0;
        else return tab[r].type;
        break;
    case DOWN_RIGHT:
        if ((!tab[dr].type || !dr)) return 0;
        else return tab[dr].type;
        break;
    case UP_RIGHT:
        if ((!tab[ur].type || !ur)) return 0;
        else return tab[ur].type;
        break;
    default:
        return 0;
        break;
    }

    return 0;
}
