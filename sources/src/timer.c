#include "timer.h"
#include "object.h"
#include "animation.h"
#include "mario.h"

int timer_init(void){
    return 0;
}

timer_id_t timer_set(Uint32 delay, void *param){
    return SDL_AddTimer(delay, callback, param);
}

timer_id_t timer_loop_set(Uint32 delay, void *param){
    return SDL_AddTimer(delay, callback_loop, param);
}

Uint32 callback(Uint32 interval, void* param){
    SDL_Event event;
    SDL_UserEvent userevent;

    /* In this example, our callback pushes an SDL_USEREVENT event
    into the queue, and causes our callback to be called again at the
    same interval: */

    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = param;
    userevent.data2 = NULL;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return 0;
}

Uint32 callback_loop(Uint32 interval, void* param){
    SDL_Event event;
    SDL_UserEvent userevent;

    /* In this example, our callback pushes an SDL_USEREVENT event
    into the queue, and causes our callback to be called again at the
    same interval: */

    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = param;
    userevent.data2 = NULL;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return interval;
}

int timer_cancel(timer_id_t timer_id){
    return SDL_RemoveTimer(timer_id);
}