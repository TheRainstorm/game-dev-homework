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

    Graph * m_graph, *m_next_graph;

    int m_score, m_level;
    GameState m_game_state;
private:
    void init_map();
    void draw_map();
	void draw_next_graph();
	void draw_score();
	void draw_help_info();
	void draw_game_over();

	bool detect_collision();
    void modify_map();
	void eliminate_line();
};

#endif