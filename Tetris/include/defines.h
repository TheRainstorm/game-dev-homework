#ifndef DEFINE_H
#define DEFINE_H

#define WIDTH 10
#define HEIGHT 17
#define GRAPH_NUM 7
#define COLOR_NUM 6 //don't include CLEAR, BLACK, WHITE

enum enum_graph {O_graph, I_graph, T_graph, L_graph, J_graph, Z_graph, S_graph};
enum enum_move {Left=-1, Right=1};
enum enum_rotate {Clockwise=1, Anticlockwise=3};
enum enum_game_state {START, PAUSE, END};
enum enum_color {CLEAR, BLACK, RED, GREEN, YELLOW, BLUE, PURPLE, DEEP_GREEN, WHITE};

#endif