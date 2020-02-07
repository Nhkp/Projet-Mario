
#include "object.h"
#include "map.h"

int isInside(dynamic_object_t *obj1, map_object_t obj2 ) {
    if ((obj1->x < (obj2.dst.x + obj2.dst.w)) && ((obj1->x + obj1->sprite->dst.w) > obj2.dst.x) && (obj1->y < (obj2.dst.y + obj2.dst.h)) && ((obj1->sprite->dst.h + obj1->y )> obj2.dst.y)) {
        return 1;
    }
	else {
    	return 0;
	}
}