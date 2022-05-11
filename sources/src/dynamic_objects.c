#include "object.h"
#include "animation.h"
#include "graphics.h"
#include "list.h"
#include "sprite.h"
#include "explosion.h"
#include "mario.h"
#include "collision.h"
#include "timer.h"
#include "sound.h"
#include "cursor.h"
#include "missile.h"
#include "sound.h"
#include "dynamic_objects.h"

dynamic_object_t tank;

//BOMB
void bomb_add(dynamic_object_t *obj)
{
  int x, y;
  if (obj->direction){x = obj->x - TILE; y = obj->y + TILE;}
  else{x = obj->x + TILE; y = obj->y + TILE;}

  if(edition){x -= TILE; y -= TILE;}

  dynamic_object_t *bomb = malloc(sizeof(dynamic_object_t));
  object_object_init(bomb, &bomb_sprite, OBJECT_TYPE_BOMB, x, y);
  animation_mobile_object_add(bomb);
  animation_timer_add(bomb, 175, 1);
  play_sound(SOUND_PSCHH);
}

void bomb_callback(dynamic_object_t *obj){
  if(!(obj->anim_next_step > 15)) obj->anim_next_step++;
  else{tnt_explode(obj); animation_timer_cancel(obj);}
}

//LANDMINE

void landmine_add(dynamic_object_t *obj)
{
  int x, y;
  if (obj->direction){x = obj->x - TILE; y = obj->y + TILE;}
  else{x = obj->x + TILE; y = obj->y + TILE;}

  if(edition){x -= TILE; y -= TILE;}

  dynamic_object_t *landmine = malloc(sizeof(dynamic_object_t));
  object_object_init(landmine, &landmine_sprite, OBJECT_TYPE_LANDMINE, x, y);
  landmine->state = OBJECT_STATE_INACTIVE;
  landmine->anim_next_step =5;
  animation_timer_add(landmine, 50, 1);
  animation_mobile_object_add(landmine);
}

void landmine_callback(dynamic_object_t *obj){
  if(obj->state == OBJECT_STATE_INACTIVE && obj->anim_next_step < 9)
    obj->anim_next_step++;
  if(obj->state == OBJECT_STATE_ACTIVE && obj->anim_next_step < 4)
    obj->anim_next_step++;
  if(obj->state == OBJECT_STATE_DEAD){
    tnt_explode(obj);
    animation_timer_cancel(obj);
    obj->state = OBJECT_STATE_DESTROYED;
  }
}

void landmine_activation(dynamic_object_t *obj, int ok){
  if(ok && obj->state == OBJECT_STATE_INACTIVE){
    obj->state = OBJECT_STATE_ACTIVE;
    obj->anim_next_step = 0;
  }
}

void animation_landmine_one_step(dynamic_object_t *obj){
  if (obj->state == OBJECT_STATE_ACTIVE && obj->x - 3 / 2 * TILE <= mario.x && mario.x <= obj->x + TILE
  && obj->y - 2 * TILE <= mario.y && mario.y <= obj->y + TILE){
    animation_timer_cancel(obj);
    animation_timer_add(obj, 300, 0);
    obj->state = OBJECT_STATE_DEAD;
  }
  if(obj->state == OBJECT_STATE_DEAD)
    obj->anim_next_step = (obj->anim_next_step < 4) ? obj->anim_next_step+1: 0;
}


//TANK
void tank_destruction(){
  dynamic_object_t *tmp = malloc(sizeof(dynamic_object_t));
  object_object_init(tmp, &explosion_sprite, OBJECT_TYPE_EXPLOSION, tank.x+TILE, tank.y);
  tnt_explode(tmp);
  play_sound(SOUND_YEEHA);
  play_sound(SOUND_YEEHA);
  play_sound(SOUND_YEEHA);

  map_set(7, 48, 17);
  map_set(8, 48, 18);
  tank.state = OBJECT_STATE_DESTROYED;
}

void tank_one_step(dynamic_object_t *obj){
  if(obj->hp <= 0) tank_destruction();
  if(obj->direction && !collision(obj, DOWN_LEFT)) obj->x--;
  else if(obj->direction) obj->direction = 0;
  if(!obj->direction && !collision(obj, DOWN_RR)) obj->x++;
  else if(!obj->direction) obj->direction = 1;
}

void tank_callback(dynamic_object_t *obj){
  if(obj->x - mario.x < WIN_WIDTH && obj->y - mario.y < WIN_HEIGHT){
    if (obj->direction) animation_missile_add(missile_init(), obj->x - TILE, obj->y + 16, obj->direction);
    else animation_missile_add(missile_init(), obj->x + 3 * TILE, obj->y + 16, obj->direction);
  }
}

int inside_tank(int x, int y, int w, int h){
  if(tank.state != OBJECT_STATE_DESTROYED)
    return inside_square(tank.x,tank.x+(5/2*TILE),tank.y,tank.y+2*TILE,x,x+w,y,y+h);
  else return 0;
}

