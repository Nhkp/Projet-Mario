#include "object.h"
#include "map.h"
#include "constants.h"
#include "string.h"
#include "collision.h"
#include "map_objects.h"

#define is_aligned(x)       (((x) & (TILE - 1)) == 0)
#define dist_from_aligned   (x)((TILE - (x)) & (TILE - 1))
#define modulo_tile(x)      (x%TILE)

int collision(dynamic_object_t *obj, int direction){

    int ul =    map_get(((obj->x + 8) / TILE), ((obj->y) / TILE));
    int d2l =   map_get(((obj->x + 8) / TILE), ((obj->y) / TILE) + 2);

    int dl =    map_get(((obj->x - 1) / TILE), ((obj->y) / TILE) + 1);
    int l =     map_get(((obj->x - 1) / TILE), ((obj->y) / TILE));


    int ur =    map_get(((obj->x - 8) / TILE) + 1, ((obj->y) / TILE));
    int d2r =   map_get(((obj->x - 8) / TILE) + 1, ((obj->y) / TILE) + 2);

    int dr =    map_get(((obj->x + 1) / TILE) + 1, ((obj->y) / TILE) + 1);
    int drr =    map_get(((obj->x + 1) / TILE) + 3, ((obj->y) / TILE) + 1);
    int r =     map_get(((obj->x + 1) / TILE) + 1, ((obj->y) / TILE));

    switch (direction){
    case UP:
        if(is_aligned(obj->x)) return ul;
        else{
            if(!ul && !ur) return 0;
            else if (ul) return ul;
            else return ur;
        }
    case DOWN2:
        if(is_aligned(obj->x)) return d2l;
        else{
            if(!d2l && !d2r) return 0;
            else if (d2l) return d2l;
            else return d2r;
        }
    case LEFT:
        return l;
    case DOWN_LEFT:
        return dl;
    case UP_LEFT:
        return ul;
    case RIGHT:
        return r;
    case DOWN_RIGHT:
        return dr;
    case DOWN_RR:
        return drr;
    case UP_RIGHT:
        return ur;
    default:
        return 0;
    }

    return 0;
}



int inside_square(int a, int b, int c, int d, int i, int j, int k, int l){
  if((a<i && i<b && c<k && k<d)
  || (a<j && j<b && c<k && k<d)
  || (a<j && j<b && c<l && l<d)
  || (a<i && i<b && c<l && l<d))
    return 1;
  else
    return 0;
}
