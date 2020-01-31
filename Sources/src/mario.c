#include "mario.h"
#include "object.h"
#include "constants.h"
#include "missile.h"
#include "animation.h"

dynamic_object_t mario;


void animation_mario_moves(dynamic_object_t *obj, int up, int down, int left, int right, int space)
{
  obj->xs = 4;
  
  if (up && obj->y > MARIO_INITIAL_POSY-128) 
  {
    obj->y -= 16; 
  }

  // gravité
  if (!up && obj->y < MARIO_INITIAL_POSY)
    obj->y += 8;

  if(left)
  {
    obj->direction = 1;
    obj->x -= obj->xs;

    if (obj->anim_next_step < obj->sprite->nb_step-1)
      obj->anim_next_step++;
    else
      obj->anim_next_step = 0;
  }

  if(right)
  {
    obj->direction = 0;
    obj->x += obj->xs;

    if(obj->anim_next_step < obj->sprite->nb_step-1)
      obj->anim_next_step++;
    else
      obj->anim_next_step = 0;
  }
}
  
  

void animation_mario_one_step(dynamic_object_t *obj)
{
  
}
