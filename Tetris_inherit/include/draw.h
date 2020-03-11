#ifndef DRAW_H
#define DRAW_H
#include "graph.h"

void cursor_show(bool see);
void clear_screen();
void move_to(int row, int column);
void draw_block(Color color);

#endif