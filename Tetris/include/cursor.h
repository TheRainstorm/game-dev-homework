#ifndef CURSOR_H
#define CURSOR_H
#include "defines.h"

class Cursor
{
public:
    void save(); //save current place
    void resume(); //resume place
    void move_to(int, int);

    void draw_block(enum_color); //draw a block with color in current place
};

void mySleep(int time); //millisecond

#endif