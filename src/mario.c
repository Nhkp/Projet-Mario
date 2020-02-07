#include "mario.h"
#include "object.h"
#include "constants.h"
#include "missile.h"
#include "animation.h"
#include "map.h"
#include "explosion.h"

dynamic_object_t mario;

int tmp = -1;
void animation_mario_moves(dynamic_object_t *obj, int up, int down, int left, int right, int space)
{
  obj->xs = 4;
  obj->ys = 8;
  static int x;
  
  if (up && !obj->state) 
  {
    obj->y -= 24;

    if (obj->y < tmp - 128)
    obj->state = OBJECT_STATE_IN_AIR;
  }

  // gravité
  int test = map_get(obj->x / 64, (obj->y / 64)+2);
  printf("%d", test);
  if (!test)
  {
    obj->y += obj->ys;
  }
  else
  {
    switch (tab[test].type)
    {
    case 0:
      tmp = obj->y;
      obj->state = OBJECT_STATE_NORMAL;
      break;
    case 1:
      tmp = obj->y;
      obj->state = OBJECT_STATE_NORMAL;
      break;
    case 2:
      obj->y+= obj->ys;
    case 3:
      obj->y += obj->ys;
    case 4:
      obj->y += obj->ys;
    default:
      break;
    }
  }

  int test1 = map_get((obj->x / 64), obj->y / 64);

  if(left && !test1)
  {
    obj->moved = 1;
    obj->direction = 1;
    if (obj->x > 200)
      obj->x -= obj->xs;

    if (obj->anim_next_step < obj->sprite->nb_step-1)
      obj->anim_next_step++;
    else
      obj->anim_next_step = 0;
  }else if (left)
  {
    if (obj->anim_next_step < obj->sprite->nb_step-1)
      obj->anim_next_step++;
    else
      obj->anim_next_step = 0; 
  }

  int test2 = map_get((obj->x / 64)+1, obj->y / 64);
  if(right && !test2)
  {
    obj->moved = 1;
    obj->direction = 0;
    if (obj->x < 900)
      obj->x += obj->xs;

    if(obj->anim_next_step < obj->sprite->nb_step-1)
      obj->anim_next_step++;
    else
      obj->anim_next_step = 0;
  }else if (right)
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
