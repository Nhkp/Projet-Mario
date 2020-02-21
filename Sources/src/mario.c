#include "mario.h"
#include "object.h"
#include "constants.h"
#include "missile.h"
#include "animation.h"
#include "map.h"
#include "explosion.h"

extern int mv_background[];
dynamic_object_t mario;

int update(int dt){
  return (int)(-(dt*dt/10)+10*dt);
}

int tmp = -1;
void animation_mario_moves(dynamic_object_t *obj, int up, int down, int left, int right, int space)
{
  obj->xs = 4;
  obj->ys = 6;
 
  if (up) 
  {
    if (obj->y - 6 > 0)
    {
      obj->y -= 6;
      obj->ys -= 4;
    }
  }

  // gravité
  int test = map_get(obj->x / 64, (obj->y / 64)+2);
  if (tab[test].type == MAP_OBJECT_AIR || !test)
  {
    obj->y += obj->ys;
  }

  
  int test1 = map_get((obj->x / 64), obj->y / 64);
  int test1b = map_get((obj->x / 64), (obj->y / 64)+1);

  if(left && (tab[test1].type == MAP_OBJECT_AIR || !test1) && (tab[test1b].type == MAP_OBJECT_AIR || !test1b))
  {
    obj->direction = 1;
    obj->x -= obj->xs;
    
    if (obj->anim_next_step < obj->sprite->nb_step-1)
      obj->anim_next_step++;
    else
      obj->anim_next_step = 0;

  }
  else if (left)
  {
    if (obj->anim_next_step < obj->sprite->nb_step-1)
      obj->anim_next_step++;
    else
      obj->anim_next_step = 0; 
  }

  int test2 = map_get((obj->x / 64)+1, obj->y / 64);
  int test2b = map_get((obj->x / 64)+1, (obj->y / 64)+1);
  
  if(right &&   (tab[test2].type == MAP_OBJECT_AIR || !test2) && (tab[test2b].type == MAP_OBJECT_AIR || !test2b))
  {
    obj->direction = 0;
    obj->x += obj->xs;
    
    if(obj->anim_next_step < obj->sprite->nb_step-1)
      obj->anim_next_step++;
    else
      obj->anim_next_step = 0;
    }
    else if (right)
    {
    if (obj->anim_next_step < obj->sprite->nb_step-1)
      obj->anim_next_step++;
    else
      obj->anim_next_step = 0; 
  }
}
  
  

void animation_mario_one_step(dynamic_object_t *obj)
{
  
}
