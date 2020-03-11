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

    Graph * m_graph, *m_next_graph;
    GameState m_game_state;
private:
    int m_map[HEIGHT][WIDTH];
    Color m_color_map[HEIGHT][WIDTH];

    int m_score, m_level;
public:
    void init_map();
    void draw_map();
	void draw_next_graph();
	void draw_score();
	void draw_help_info();
	void draw_game_over();
    void draw_pause(bool clear=false);

	bool detect_collision();
    void modify_map();
	void eliminate_line();
};

#endif