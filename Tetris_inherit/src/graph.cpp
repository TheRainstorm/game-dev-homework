#include "graph.h"
#include <stdio.h>
#define CSI "\033["

void cursor_show(bool see) {
	printf("%s?25%c", CSI, see ? 'h' : 'l');
}

void clear_screen() {
	printf("%s%s", CSI, "2J");
}

void move_to(int row, int column) {
	printf("%s%d;%dH", CSI, row + 1, column * 2 + 1);
}

void draw_block(Color color) {
	switch (color)
	{
	case BLACK:     printf("\033[40;30m  \033[0m"); break;
	case RED:       printf("\033[41;31m  \033[0m"); break;
	case GREEN:     printf("\033[42;32m  \033[0m"); break;
	case YELLOW:    printf("\033[43;33m  \033[0m"); break;
	case BLUE:      printf("\033[44;34m  \033[0m"); break;
	case MAGENTA:   printf("\033[45;35m  \033[0m"); break;
	case CRAY:      printf("\033[46;36m  \033[0m"); break;
	case WHITE:     printf("\033[47;37m  \033[0m"); break;
	case COLOR_NUM: printf("\033[8m  ");	//conceal	Not widely support
	default: break;
	}
}

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
				draw_block(BLACK);
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