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

int update(int dt){
  return (int)(-(dt*dt/10)+10*dt);
}

int tmp = -1;
void animation_mario_moves(dynamic_object_t *obj, int up, int down, int left, int right, int space)
{
  obj->xs = 4;
  obj->ys = 8;
  
  //printf("%d\n", collision(&mario, UP));
  if (up && obj->y> 0 /*&& !collision(&mario, UP) && !obj->state */) 
    obj->y -= 24;
    obj->state = OBJECT_STATE_IN_AIR;

  // gravité
  if (!collision(&mario, DOWN))
    obj->y += obj->ys;
  //else
  //  obj->state = OBJECT_STATE_NORMAL;
  

  //LEFT
  if(left && !collision(&mario, LEFT))
  {
    obj->direction = 1;
    obj->x -= obj->xs;

    obj->anim_next_step = (obj->anim_next_step < obj->sprite->nb_step-1) ? obj->anim_next_step+1 : 0; 
  }
  else if (left)
    obj->anim_next_step = (obj->anim_next_step < obj->sprite->nb_step-1) ? obj->anim_next_step+1 : 0; 

  //RIGHT
  if(right && !collision(&mario, RIGHT))
  {
    obj->direction = 0;
    obj->x += obj->xs;
    
    obj->anim_next_step = (obj->anim_next_step < obj->sprite->nb_step-1) ? obj->anim_next_step+1 : 0; 
  }
  else if (right)
    obj->anim_next_step = (obj->anim_next_step < obj->sprite->nb_step-1) ? obj->anim_next_step+1 : 0; 

}

void animation_mario_one_step(dynamic_object_t *obj)
{
}
