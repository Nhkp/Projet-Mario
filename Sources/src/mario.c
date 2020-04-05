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
  obj->ys = 10;
 
  static int jumping = 0; // No jumping = 0, Jumping = 1
  static int Y_velocity = 0;
  static int gravity = 1;
  double deltaT = 0.03; // discretisation, 30 image par secndes 1/30 = 0.03
  static int t = 0;


  int testBlockBas = map_get(obj->x / TILE, (obj->y / TILE) + 2); //BlocGauche
  testBlockBas += map_get((obj->x / TILE) +1, (obj->y / TILE) + 2);//BlocDroit

  int testBlockHaut = map_get(obj->x / TILE, (obj->y / TILE) ); //BlocGauche
  testBlockHaut += map_get((obj->x / TILE)+1, (obj->y / TILE) ); //BlocDroit

  if (up && !obj->state && !collision(obj, UP) && jumping ==0) //appuis du boutton
  { // initialisation des variables
    obj->y -= Y_velocity;
    jumping = 1;
    Y_velocity = 14;
    gravity = 14;
    t++;
  }else if(jumping == 1 && testBlockHaut) //si on est bloqué au dessus
  {
    t = 40;
    obj->y -= Y_velocity - t * deltaT*gravity;

  }else if(jumping == 1 && testBlockBas) //si on tombe sur un bloc en dessous
  { //réinitialisation des variables
    t = 0;
    jumping = 0;
    gravity = 1;
  }
  else if(jumping == 1)
  {
      obj->y -= Y_velocity - t * deltaT*gravity;
      t++;
  }

  //Saut

  // gravité
  if (!collision(obj, DOWN2) && jumping!=1){
    gravity = (gravity > obj->ys)? obj->ys:gravity+1;
    obj->y += gravity;
  }

  //LEFT
  if (left && !collision(obj, LEFT) && !collision(obj, DOWN_LEFT))
  {
    obj->direction = 1;
    if (jumping && !collision(obj, UP_LEFT))
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
    if (jumping && !collision(obj, UP_RIGHT))
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