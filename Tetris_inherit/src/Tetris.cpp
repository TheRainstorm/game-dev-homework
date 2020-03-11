#include "Tetris.h"
#include "draw.h"
#include "graph.h"
#include "defines.h"

#include <Windows.h>
#include <stdio.h>
#include "pthread.h"

Graph *graph_factory();

Color Tetris::ink = WHITE;
Color Tetris::paper = BLACK;

Tetris::Tetris(){
    m_score = 0;
	m_level = 0;
	m_game_state = START;
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

void Tetris::draw_next_graph() {
	int row, col;
	row = 2, col = WIDTH + 4;

	m_next_graph->save();
	m_next_graph->set_position(row, col);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			move_to(row + i, col + j);
			draw_block(Tetris::paper);
		}
	}

	m_next_graph->draw();
	m_next_graph->resume();
}

void Tetris::draw_score() {
	int row, col;
	row = HEIGHT - 2, col = WIDTH + 4;

	move_to(row, col);
	printf("Score: %d", m_score);
	move_to(row+1, col);
	printf("Level: %d (speed: %4dms/grid)", m_level, 1000-200*m_level);
}

void Tetris::draw_help_info() {
	move_to(HEIGHT / 2 - 3, WIDTH + 4);
	for (int i = 0; i < 5; i++) {
		move_to(HEIGHT / 2 -2 + i, WIDTH + 4);
		switch (i) {
		case 0:
			printf("a: move left"); break;
		case 1:
			printf("d: move right"); break;
		case 2:
			printf("w: rotate clockwise"); break;
		case 3:
			printf("s: move down quick"); break;
		case 4:
			printf("p: pause/resume"); break;
		default:break;
		}
	}
}

void Tetris::draw_pause(bool clear) {
	move_to(HEIGHT / 2 - 1, WIDTH / 2 - 1);
	if (!clear) {
		printf("PAUSE");
	}
	else {
		printf("     ");
	}
}

void Tetris::draw_game_over() {
	move_to(HEIGHT / 2 - 3, 0);
	printf(\
		"      ____                                    ___                         \n"\
		"    //   ) )                                //   ) )                      \n"\
		"   //         ___      _   __      ___     //   / /        ___      __    \n"\
		"  //  ____  //   ) ) // ) )  ) ) //___) ) //   / /|  / / //___) ) //  ) ) \n"\
		" //    / / //   / / // / /  / / //       //   / /|| / / //       //       \n"\
		" ((____/ / ((___(( // / /  / / ((____   ((___/ / ||/ / ((____   //        \n"
	);
	move_to(HEIGHT + 1, 0);
}


bool Tetris::detect_collision(){
	int i, j, row, col, *points;
	row = m_graph->m_row;
	col = m_graph->m_column;
	points = m_graph->m_points;
	for(i=0;i<m_graph->m_height;i++)
		for(j=0;j<m_graph->m_width;j++)
			if(m_graph->get_point(points, i, j) + m_map[row+i][col+j] == 2) //both equal 1
				return true;
	return false;
}

void Tetris::modify_map() {
	int i, j, row, col, * points;
	row = m_graph->m_row;
	col = m_graph->m_column;
	points = m_graph->m_points;
	for (i = 0; i < m_graph->m_height; i++)
		for (j = 0; j < m_graph->m_width; j++)
			if (m_graph->get_point(points, i, j)) {
				m_map[row + i][col + j] = 1;
				m_color_map[row + i][col + j] = m_graph->m_color;
			}
}

void Tetris::eliminate_line() {
	int row, col, sum, bouns;
	bouns = 10;
	for (row = HEIGHT - 2; row >= DEAD_LINE + 1;) {
		sum = 0;
		for (col = 0; col < WIDTH; col++) {
			sum += m_map[row][col];
		}
		if (sum == WIDTH) {
			for (int i = 1; i < WIDTH - 1; i++) {
				m_map[row][i] = 0;
				m_color_map[row][i] = Tetris::paper;
			}
			draw_map();
			m_score += bouns;
			bouns *= 2;
			draw_score();
			for (int i = row; i >= DEAD_LINE + 1; i--) {
				for (int j = 1; j < WIDTH - 1; j++) {
					m_map[i][j] = m_map[i - 1][j];
					m_color_map[i][j] = m_color_map[i - 1][j];
				}
			}
			Sleep(500);
			draw_map();
			Sleep(500);
		}
		else {
			row--;
		}
	}
}

extern pthread_mutex_t g_graph_mutex;
void Tetris::play(){
	cursor_show(false);
	clear_screen();

	//init screen
	init_map();
	draw_map();
	draw_score();
	draw_help_info();
	m_game_state = RUNNING;

	int cnt = 0; //total graph number
	m_graph = graph_factory();
	while (m_game_state != END) {
		m_next_graph = graph_factory();
		draw_next_graph();
		//draw a graph
		m_graph -> draw();

		//increase game level
		cnt++;
		m_level = (cnt / COUNTER < 5) ? cnt / COUNTER : 4;

		while(!(m_graph->m_dead)){ //Loop: down until graph dead
			Sleep(1000 - m_level*200);
			if (m_game_state == PAUSE) continue;
			pthread_mutex_lock(&g_graph_mutex);
			m_graph->save();
			m_graph->down();
			if(detect_collision()){
				m_graph->resume();
				m_graph->m_dead = true;
			}else{
				m_graph->erase();
				m_graph->draw();
			}
        	pthread_mutex_unlock(&g_graph_mutex);
		}
		//write dead graph to map
		modify_map();
		draw_map(); //test wheather the map have been modified
		//if the last graph touch the DEAD LINE, game over
		if(m_graph->m_row<=DEAD_LINE){
			m_game_state = END;
			break;
		}
		//try eliminate lines
		eliminate_line();

		delete m_graph;
		m_graph = m_next_graph;
	}
	delete m_graph;
	delete m_next_graph;

	draw_game_over();
	cursor_show(true);
}