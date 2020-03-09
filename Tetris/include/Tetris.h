#ifndef TETRIS_H
#define TETRIS_H
#include "Shape.h"
#include "defines.h"
#include "cursor.h"

class Tetris{
public:
	Tetris(); //init some variable. (e.x score, level)
	void play();
public:
	int m_map[HEIGHT+2][WIDTH+2]; //0:empty, 1:dead block
	enum_color m_color_map[HEIGHT+1][WIDTH+2];
	int m_score;
	int m_level;
	Shape *m_cur_graph;
	Cursor *m_cursor;
	enum_game_state m_game_state;

	void init_map(); //init boarder and some prepared blocks
	void modify_map(Shape &graph); //when a graph dead, write to map

	bool collision(Shape &graph); //detect collision
	void eliminate(); //eliminate filled line
	void draw_cur_graph(Shape &graph);
	void erase_prev_graph(Shape &graph);
	void draw_map(); //draw the total map. may cover the graph
	void draw_score();
	void draw_help();
};

#endif