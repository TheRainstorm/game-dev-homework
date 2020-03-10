#ifndef OS_H
#define OS_H
#include "defines.h"

void mySleep(int time); //millisecond
char myGetch();

//cursor
void cursor_show(bool );
void cursor_clear_screen();
void cursor_move_to(int, int); //x, y
void cursor_draw_block(enum_color); //draw a block with color in current place

#endif