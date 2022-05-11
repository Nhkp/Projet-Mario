#ifndef CURSOR_IS_DEF
#define CURSOR_IS_DEF

#include "constants.h"
#include "object.h"

extern dynamic_object_t cursor;
extern int edition;

void cursor_init();
void edit_mode(int ok, int q);
void cursor_left();
void cursor_right();
void cursor_up();
void cursor_down();

#endif