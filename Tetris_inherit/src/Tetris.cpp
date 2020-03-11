#include "Tetris.h"
#include "draw.h"
#include "graph.h"
#include "defines.h"

#include <Windows.h>
#include <stdlib.h>

Color Tetris::ink = WHITE;
Color Tetris::paper = BLACK;

Tetris::Tetris(){
    m_score = 0;
	m_level = 0;
}

void Tetris::init_map(){
    for (int i = 0; i < HEIGHT; i++) { //fill all with 0
		for (int j = 0; j < WIDTH; j++) {
			m_map[i][j] = 0;
			m_map[i][j] = Tetris::paper;
		}
	}
	for (int i = 0; i < HEIGHT; i++) { //left and right border
		m_map[i][0] = m_map[i][WIDTH - 1] = 1;
		m_color_map[i][0] = m_color_map[i][WIDTH - 1] = WHITE;
	}
	for (int j = 1; j < WIDTH - 1; j++) { //bottom and top border
		m_map[0][j] = m_map[HEIGHT - 1][j] = 1;
		m_color_map[0][j] = m_color_map[HEIGHT - 1][j] = WHITE;
	}
	//when game start, there is some block already
	for (int j = 1; j < WIDTH - 1; j++) {
		m_map[HEIGHT - 2][j] = 1;
		m_color_map[HEIGHT - 2][j] = YELLOW;
	}
	m_map[HEIGHT - 2][3] = 0;
	m_color_map[HEIGHT - 2][3] = Tetris::paper;
}

void Tetris::draw_map() {
	for (int i = 0; i < HEIGHT; i++) {
		move_to(i, 0);
		for (int j = 0; j < WIDTH; j++) {
			draw_block(m_color_map[i][j]);
		}
	}
}

void Tetris::play(){
	cursor_show(false);
	init_map();
	draw_map();

	Graph *graph = new T_graph();

    // System("cls");
    graph->draw();

    int i;
    for (i = 0; i < 50; i++) {
		Sleep(200);

		graph->save();

        int rand_num = rand() % 5;
		switch (rand_num)
		{
		case 0:
		case 1: graph->down(); break;
		case 2: graph->move_right(); break;
		case 3: graph->move_left(); break;
		case 4: graph->rotate(); break;
		default:
			break;
		}

		graph->erase();
		graph->draw();
    }
	cursor_show(true);
}
