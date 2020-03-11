#ifndef DEFINE_H
#define DEFINE_H

#define HEIGHT 19   //17 + 2
#define WIDTH 12    //10 + 2
#define DEAD_LINE 3 //1 + 2   row <= DEAD_LINE will lose
#define COUNTER 5

enum Color { BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CRAY, WHITE, COLOR_NUM };
enum GameState {START, RUNNING, PAUSE, END};

#endif
