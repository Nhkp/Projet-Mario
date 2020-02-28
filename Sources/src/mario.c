#include "mario.h"
#include "object.h"
#include "constants.h"
#include "missile.h"
#include "animation.h"
#include "map.h"
#include "explosion.h"
#include "collision.h"

dynamic_object_t mario;

void animation_mario_moves(dynamic_object_t *obj, int up, int down, int left, int right, int space)
{
  //Vitesses de mouvement
  obj->xs = 4;
  obj->ys = 16;
 
  //Saut
  static int dt;
  static int jumping;
  static int saving;
  int test = map_get(obj->x / TILE, (obj->y / TILE)+2);
  if (up && !obj->state && !collision(obj, UP)) 
  {
    obj->y -= obj->ys*1.5;
    obj->state = OBJECT_STATE_IN_AIR;
    dt = 0;
    saving = obj->y;
    jumping = 1;
  }
  else if(jumping == 1)
  {
    if(dt > TILE || test){
      dt = 0;
      jumping = 0;
    }else{
    obj->y = saving - update(dt);
    dt ++;}
  }
  if (test)
    obj->state = OBJECT_STATE_NORMAL;

  // gravité
  //printf("%d\n", collision(obj, DOWN));
  if (collision(obj, DOWN) == 0)
    obj->y += obj->ys/2;


  //LEFT
  if (left && !collision(obj, LEFT) && !collision(obj, DOWN_LEFT))
  {
    obj->direction = 1;
    if(jumping && !collision(obj, UP_LEFT))
      obj->x -= obj->xs;
    else if (!jumping)
      obj->x -= obj->xs;

    obj->anim_next_step = (obj->anim_next_step < obj->sprite->nb_step - 1) ? obj->anim_next_step + 1 : 0;
  }
  else if (left)
    obj->anim_next_step = (obj->anim_next_step < obj->sprite->nb_step - 1) ? obj->anim_next_step + 1 : 0;

  //RIGHT
  if (right && !collision(obj, RIGHT) && !collision(obj, DOWN_RIGHT))
  {
    obj->direction = 0;
    if(jumping && !collision(obj, UP_RIGHT))
      obj->x += obj->xs;
    else if (!jumping)
      obj->x += obj->xs;

    obj->anim_next_step = (obj->anim_next_step < obj->sprite->nb_step - 1) ? obj->anim_next_step + 1 : 0;
  }
  else if (right)
    obj->anim_next_step = (obj->anim_next_step < obj->sprite->nb_step - 1) ? obj->anim_next_step + 1 : 0;
}

void animation_mario_one_step(dynamic_object_t *obj)
{
}


int update(int dt)
{
  return (int)(-(dt * dt / 10) + 8 * dt);
}