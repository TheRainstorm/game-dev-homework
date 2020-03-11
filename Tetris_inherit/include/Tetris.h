#ifndef TETRIS_H
#define TETRIS_H

#include "graph.h"
#include "defines.h"

class Tetris{
public:
    static Color ink;
    static Color paper;    //foreground and background

    Tetris();
    void play();
private:
    int m_map[HEIGHT][WIDTH];
    Color m_color_map[HEIGHT][WIDTH];

    Graph *m_current_graph, *m_next_graph;

    int m_score, m_level;
private:
    void init_map();
    void draw_map();
	/*void draw_next_graph();
	void draw_score();
	void draw_help_info();
	void draw_game_over();

	void detect_collision();
	void eliminate_line();*/
};

#endif