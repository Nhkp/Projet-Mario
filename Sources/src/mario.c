#include "mario.h"
#include "object.h"
#include "constants.h"
#include "missile.h"
#include "animation.h"
#include "map.h"
#include "explosion.h"

dynamic_object_t mario;

int update(int dt){
  return (int)(-(dt*dt/10)+10*dt);
}

int tmp = -1;
void animation_mario_moves(dynamic_object_t *obj, int up, int down, int left, int right, int space)
{
  obj->xs = 4;
  obj->ys = 6;
  static int dt;
  static int jumping;
  static int saving;

  /*if (up && !obj->state){
    saving = obj->y;
    obj->y-=obj->ys;
    obj->state = OBJECT_STATE_IN_AIR;
  }*/
  if (up) 
  {
    if (obj->y - 6 > 0)
    {
      obj->y -= 6;
      obj->ys -= 4;
    }
  }

  /*if (up && !obj->state) 
  {
    dt = 0;
    saving = obj->y;
    //printf("test\n");
    jumping = 1;
  }else if(jumping == 1)
  {
    if(dt >100){
      dt = 0;
      jumping = 0;
    }else{
    obj->y = saving - update(dt);
    dt ++;}
  }*/
  int test = map_get(obj->x / 64, (obj->y / 64)+2);
  if (!test)
  {
    obj->y += obj->ys;
  }

  // gravité
  
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
