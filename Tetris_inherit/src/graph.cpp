#include "graph.h"
#include "draw.h"
#include "Tetris.h"

void Graph::move_left() {
	m_column--;
}
void Graph::move_right() {
	m_column++;
}
void Graph::down() {
	m_row++;
}
void Graph::save() {
	m_prev_column = m_column;
	m_prev_row = m_row;
	m_prev_points = m_points;
}
void Graph::resume() {
	m_column = m_prev_column;
	m_row = m_prev_row;
	m_points = m_prev_points;
}
//
void Graph::draw() {
	int i, j;
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			if (get_point(m_points, i, j) == 1) {
				move_to(m_row + i, m_column + j);
				draw_block(m_color);
			}
		}
	}
}
void Graph::erase() {
	int i, j;
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			if (get_point(m_prev_points, i, j) == 1) {
				move_to(m_prev_row + i, m_prev_column + j);
				draw_block(Tetris::paper);
			}
		}
	}
}

int O_graph::all_points[1][2][2] = {
	{{1, 1},
	{1, 1}}
};

int T_graph::all_points[4][3][3] = {
	{{0, 0, 0},
	 {1, 1, 1},
	 {0, 1, 0}},
	{{0, 1, 0},
	 {1, 1, 0},
	 {0, 1, 0}},
	{{0, 1, 0},
	 {1, 1, 1},
	 {0, 0, 0}},
	{{0, 1, 0},
	 {0, 1, 1},
	 {0, 1, 0}}
};