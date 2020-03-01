#include <unistd.h>
#include "map_objects.h"
#include "explosion.h"
#include "map.h"
#include "constants.h"
#include "timer.h"

void tnt_explode(int x, int y)
{
    add_explosion2(x * TILE, y * TILE);
    map_set(0, x, y);

    //int id = timer_set(500, &add_explosion2);
    add_explosion2(x * TILE - TILE, y * TILE - TILE);
    switch(map_get(x - 1, y - 1))
    {
        case 6:
            tnt_explode(x - 1, y - 1);
            map_set(0, x - 1, y - 1);
            break;
        default:
            map_set(0, x - 1, y - 1);
            break;
    }
    add_explosion2(x * TILE, y * TILE - TILE);
    switch(map_get(x , y - 1))
    {
        case 6:
            tnt_explode(x, y - 1);
            map_set(0, x, y - 1);
            break;
        default:
            map_set(0, x, y - 1);
            break;
    }
    add_explosion2(x * TILE + TILE, y * TILE - TILE);
    switch(map_get(x + 1, y - 1))
    {
        case 6:
            tnt_explode(x + 1, y - 1);
            map_set(0, x + 1, y - 1);
            break;
        default:
            map_set(0, x + 1, y - 1);
            break;
    }
    add_explosion2(x * TILE + TILE, y * TILE);
    switch(map_get(x + 1, y))
    {
        case 6:
            tnt_explode(x + 1, y);
            map_set(0, x + 1, y);
            break;
        default:
            map_set(0, x + 1, y);
            break;
    }
    add_explosion2(x * TILE + TILE, y * TILE + TILE);
    switch(map_get(x + 1, y + 1))
    {
        case 6:
            tnt_explode(x + 1, y + 1);
            map_set(0, x + 1, y + 1);
            break;
        default:
            map_set(0, x + 1, y + 1);
            break;
    }
    add_explosion2(x * TILE, y * TILE + TILE);
    switch(map_get(x, y + 1))
    {
        case 6:
            tnt_explode(x, y + 1);
            map_set(0, x, y + 1);
            break;
        default:
            map_set(0, x, y + 1);
            break;
    }
    add_explosion2(x * TILE - TILE, y * TILE + TILE);
    switch(map_get(x - 1, y + 1))
    {
        case 6:
            tnt_explode(x - 1, y + 1);
            map_set(0, x - 1, y + 1);
            break;
        default:
            map_set(0, x - 1, y + 1);
            break;
    }
    add_explosion2(x * TILE - TILE, y * TILE);
    switch(map_get(x - 1, y))
    {
        case 6:
            tnt_explode(x - 1, y);
            map_set(0, x - 1, y);
            break;
        default:
            map_set(0, x - 1, y);
            break;
    }
}