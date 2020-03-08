#ifndef DEFINE_H
#define DEFINE_H

#define WIDTH 10
#define HEIGHT 17
#define GRAPH_NUM 7
#define COLOR_NUM 6

enum enum_graph {O_graph, I_graph, T_graph, L_graph, J_graph, Z_graph, S_graph};
enum enum_move {Left=-1, Right=1};
enum enum_rotate {Clockwise=1, Anticlockwise=3};
enum enum_color {Red, Green, Blue, Cray, Pink, Yellow};
enum enum_game_state {START, PAUSE, END};

#endif