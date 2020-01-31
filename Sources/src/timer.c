#include "timer.h"
#include "object.h"
#include "animation.h"

/*int timer_init(void)
{
    Uint32 delay = 0;
    SDL_TimerCallback callback = timer_set;
    void *param = NULL;
    SDL_TimerID my_timer_id = SDL_AddTimer(delay, callback, param);

    return my_timer_id;
}*/

/*timer_id_t timer_set(Uint32 delay, void *param)
{
    SDL_TimerID my_timer_id = SDL_AddTimer(delay, my_callbackfunc, param)
    return my_timer_id;
}*/

/*Uint32 my_callbackfunc(Uint32 interval, void *param)
{
    SDL_Event event;
    SDL_UserEvent userevent;*/

    /* In this example, our callback pushes an SDL_USEREVENT event
    into the queue, and causes our callback to be called again at the
    same interval: */

    /*userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = param;
    userevent.data2 = NULL;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return(delay);
}

int timer_cancel (timer_id_t timer_id)
{
    int res = SDL_RemoveTimer(timer_id);
    return res;
}*/