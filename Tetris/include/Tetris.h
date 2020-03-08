#ifndef TETRIS_H
#define TETRIS_H
#include "Shape.h"
#include "defines.h"

class Tetris{
public:
	Tetris();
	void play();
public:
	int m_map[HEIGHT+2][WIDTH+2]; //0:empty, 1:block, 2:dead block 3:boader
	int m_color_map[HEIGHT+1][WIDTH+2];
	int m_score;
	int m_level;
	Shape *m_p_cur_graph;
	enum_game_state m_game_state;

	void init_map(); //init boarder
	void erase_prev_graph(Shape &graph);
	void draw_cur_graph(Shape &graph);
	bool collision(Shape &graph); //detect collision
	void eliminate();
	void render(); //draw map
};

#endif