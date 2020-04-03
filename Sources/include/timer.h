
#ifndef TIMER_IS_DEF
#define TIMER_IS_DEF

#include "SDL.h"
#include <stdint.h>

typedef SDL_TimerID timer_id_t;

int check_laser();
int timer_init(void);
timer_id_t timer_set(Uint32 delay, void *param);
int timer_cancel(timer_id_t timer_id);

#endif