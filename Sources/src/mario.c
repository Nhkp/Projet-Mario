#include "mario.h"
#include "object.h"
#include "constants.h"
#include "missile.h"
#include "animation.h"
#include "map.h"
#include "explosion.h"
#include "collision.h"

extern int mv_background[];
dynamic_object_t mario;

int update(int dt)
{
  return (int)(-(dt * dt / 10) + 8 * dt);
}

int tmp = -1;
void animation_mario_moves(dynamic_object_t *obj, int up, int down, int left, int right, int space)
{

  obj->xs = 4;
  obj->ys = 16;
  int test = map_get(obj->x / 64, (obj->y / 64)+2);
 
  static int dt;
  static int jumping;
  static int saving;
  if (up && !obj->state) 
  {
    obj->y -= obj->ys;
    dt = 0;

    saving = obj->y;
    obj->state = OBJECT_STATE_IN_AIR;
    jumping = 1;
  }else if(jumping == 1)
  {
    if(dt >100 || test){
      dt = 0;
      jumping = 0;
    }else{
    obj->y = saving - update(dt);
    dt ++;}
  }
  
  if (test)
    obj->state = OBJECT_STATE_NORMAL;

  // gravité
  if (!collision(obj, DOWN))
    obj->y += obj->ys;


  //LEFT
  if (left && !collision(obj, LEFT))
  {
    obj->direction = 1;
    obj->x -= obj->xs;

    obj->anim_next_step = (obj->anim_next_step < obj->sprite->nb_step - 1) ? obj->anim_next_step + 1 : 0;
  }
  else if (left)
    obj->anim_next_step = (obj->anim_next_step < obj->sprite->nb_step - 1) ? obj->anim_next_step + 1 : 0;

  //RIGHT
  if (right && !collision(obj, RIGHT))
  {
    obj->direction = 0;
    obj->x += obj->xs;

    obj->anim_next_step = (obj->anim_next_step < obj->sprite->nb_step - 1) ? obj->anim_next_step + 1 : 0;
  }
  else if (right)
    obj->anim_next_step = (obj->anim_next_step < obj->sprite->nb_step - 1) ? obj->anim_next_step + 1 : 0;
}

void animation_mario_one_step(dynamic_object_t *obj)
{
}
