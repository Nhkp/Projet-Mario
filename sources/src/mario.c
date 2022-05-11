#include <float.h>

#include "mario.h"
#include "object.h"
#include "constants.h"
#include "missile.h"
#include "animation.h"
#include "map.h"
#include "explosion.h"
#include "collision.h"
#include "sound.h"
#include "dynamic_objects.h"
#include "map_objects.h"

#define is_aligned(x)         (((x) & (TILE-1)) == 0)
#define dist_from_aligned(x)  ((TILE - (x)) & (TILE-1))

dynamic_object_t mario;

double limit = DBL_MAX;

void animation_mario_moves(dynamic_object_t *obj, int up, int down, int left, int right, int space, int x)
{
  //Vitesses de mouvement
  obj->xs = 4;
  obj->ys = 8;

  if(x)
    animation_mario_moves(obj, up, down, left, right, space, 0);

  //Saut
  if (up && !obj->state && (!collision(obj, UP) || get_map_object_type(collision(obj, UP),2) == MAP_OBJECT_TRANSPARENT)){
    limit = obj->y - 4*TILE;
    obj->state = OBJECT_STATE_IN_AIR;
  }
  if(obj-> y > limit + 2*TILE && (!collision(obj, UP) || get_map_object_type(collision(obj, UP),2) == MAP_OBJECT_TRANSPARENT)) obj->y -= 32;
  else if(obj-> y > limit + TILE && (!collision(obj, UP) || get_map_object_type(collision(obj, UP),2) == MAP_OBJECT_TRANSPARENT)) obj->y -= 24;
  else if(obj-> y > limit + TILE/2 && (!collision(obj, UP) || get_map_object_type(collision(obj, UP),2) == MAP_OBJECT_TRANSPARENT)) obj->y -= 12;
  else limit = DBL_MAX;

  // gravité
  int test = 1;
  if(!get_map_object_type(collision(obj, DOWN2), 1)){
    switch (get_map_object_type(collision(obj, DOWN2), 2)){
      case MAP_OBJECT_COLLECTIBLE:
        break;
      case MAP_OBJECT_EXPLOSIVE:
        break;
    }
  }
  else test = 0;
  if (test && !inside_tank(obj->x, obj->y+obj->ys, TILE, 2*TILE)) obj->y += obj->ys;
  else obj->state = OBJECT_STATE_NORMAL;

  //LEFT
  if (left && !collision(obj, LEFT) && !collision(obj, DOWN_LEFT))
  {
    obj->direction = 1;
    obj->anim_next_step = (obj->anim_next_step < obj->sprite->nb_step - 1) ? obj->anim_next_step + 1 : 0;
    if(!inside_tank(obj->x-obj->xs, obj->y, TILE, 2*TILE))
      obj->x -= obj->xs;
  }
  else if (left){
    obj->direction = 1;
    int test = 1;
    if (!get_map_object_type(collision(obj, LEFT), 1)){
      switch (get_map_object_type(collision(obj, LEFT), 2)){
        case MAP_OBJECT_COLLECTIBLE:
          break;
        case MAP_OBJECT_EXPLOSIVE:
          break;
        case MAP_OBJECT_TRANSPARENT:
          break;
      }
    }
    else test = 0;
    if (!get_map_object_type(collision(obj, DOWN_LEFT), 1)){
      switch (get_map_object_type(collision(obj, DOWN_LEFT), 2)){
        case MAP_OBJECT_COLLECTIBLE: //COLLECTIBLE
          break;
        case MAP_OBJECT_EXPLOSIVE:
          break;
        case MAP_OBJECT_TRANSPARENT:
          break;
      }
    }
    else test = 0;

    if(test)
      obj->x -= obj->xs;
    obj->anim_next_step = (obj->anim_next_step < obj->sprite->nb_step - 1) ? obj->anim_next_step + 1 : 0;
  }

  //RIGHT
  if (right && !collision(obj, RIGHT) && !collision(obj, DOWN_RIGHT))
  {
    obj->direction = 0;
    obj->anim_next_step = (obj->anim_next_step < obj->sprite->nb_step - 1) ? obj->anim_next_step + 1 : 0;
    if(!inside_tank(obj->x+obj->xs, obj->y, TILE, 2*TILE))
      obj->x += obj->xs;
  }
  else if (right){
    obj->direction = 0;
    int test = 1;
    if (!get_map_object_type(collision(obj, RIGHT), 1)){
      switch (get_map_object_type(collision(obj, RIGHT), 2)){
        case MAP_OBJECT_COLLECTIBLE: //COLLECTIBLE
          break;
        case MAP_OBJECT_EXPLOSIVE:
          break;
        case MAP_OBJECT_TRANSPARENT:
          break;
      }
    }
    else test = 0;
    if (!get_map_object_type(collision(obj, DOWN_RIGHT), 1)){
      switch (get_map_object_type(collision(obj, DOWN_RIGHT), 2)){
        case MAP_OBJECT_COLLECTIBLE: //COLLECTIBLE
          break;
        case MAP_OBJECT_EXPLOSIVE:
          break;
        case MAP_OBJECT_TRANSPARENT:
          break;
      }
    }
    else test = 0;

    if(test) obj->x += obj->xs;
    obj->anim_next_step = (obj->anim_next_step < obj->sprite->nb_step - 1) ? obj->anim_next_step + 1 : 0;
  }

  //COLLECTE
  switch(get_map_object_type(map_get(obj->x/TILE, obj->y/TILE), 2)){
    case MAP_OBJECT_COLLECTIBLE:
      map_set(0, obj->x/TILE, obj->y/TILE);
      play_sound(SOUND_YEEHA);
      break;
  }
  switch(get_map_object_type(map_get(obj->x/TILE, (obj->y/TILE)+1), 2)){
    case MAP_OBJECT_COLLECTIBLE:
      map_set(0, obj->x/TILE, (obj->y/TILE)+1);
      play_sound(SOUND_YEEHA);
      break;
  }
}

int inside_mario(int x, int y, int w, int h){
  return
  inside_square(mario.x, mario.x+TILE, mario.y, mario.y+2*TILE, x, x+w, y, y+h);
}
void animation_mario_one_step(dynamic_object_t *obj)
{
}

void mario_callback()
{
  // play_sound(SOUND_YEEHA);
}