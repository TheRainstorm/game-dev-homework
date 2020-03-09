#include <iostream>
#include <string>
#include "Tetris.h"
#include "pthread.h"
using namespace std;

extern pthread_mutex_t g_game_state_mutex, g_draw_mutex, g_level_mutex;

Tetris::Tetris(){
	m_score = 0;
	m_level = 1;
	m_game_state = START;
}

void Tetris::init_map(){
	/*
	(HEIGHT+2) * (WIDTH+2) map
	leave one line on the top not use(to keep the graph touch the top when born)
	*/
	for (int i = 0; i < HEIGHT + 2; i++) { //fill all with 0
		for(int j=0;j<WIDTH+2;j++){
			m_map[i][j] = 0;
			m_map[i][j] = CLEAR;
		}
	}
	for(int i=1;i<HEIGHT+1;i++){ //left and right border
		m_map[i][0] = m_map[i][WIDTH+1] = 1;
		m_color_map[i][0] = m_color_map[i][WIDTH+1] = WHITE;
	}
	for(int j=0;j<WIDTH+2;j++){ //bottom border
		m_map[HEIGHT+1][j] = 1;
		m_color_map[HEIGHT+1][j] = WHITE;
	}
	//when game start, there is some block already
	for(int j=1;j<WIDTH+1;j++){
		m_map[HEIGHT][j] = 1;
		m_color_map[HEIGHT][j] = YELLOW;
	}
	m_map[HEIGHT][3] = 0;
	m_color_map[HEIGHT][3] = CLEAR;
}

void Tetris::draw_map(){
	for (int i = 1; i < HEIGHT + 2; i++) {
		m_cursor->move_to(0, i);
		for (int j = 0; j < WIDTH + 2; j++) {
			m_cursor->draw_block(m_color_map[i][j]);
		}
		m_cursor->resume();
	}
}

void Tetris::erase_prev_graph(Shape &graph){
	pthread_mutex_lock(&g_draw_mutex);
	int(*points)[4][4] = graph.m_points;
	int status = graph.m_prev_status;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(points[i][status][j]==1){
				m_cursor->move_to(graph.m_prev_x+j, graph.m_prev_y+i);
				m_cursor->draw_block(CLEAR);
				m_cursor->resume();
			}
		}
	}
	pthread_mutex_unlock(&g_draw_mutex);
}

void Tetris::draw_cur_graph(Shape &graph){
	pthread_mutex_lock(&g_draw_mutex);
	int (*points)[4][4] = graph.m_points;
	int status = graph.m_graph_status;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(points[i][status][j]==1){
				m_cursor->move_to(graph.m_x+j, graph.m_y+i);
				m_cursor->draw_block(graph.m_color);
				m_cursor->resume();
			}
		}
	}
	pthread_mutex_unlock(&g_draw_mutex);
}

bool Tetris::collision(Shape &graph){
	int (*points)[4][4] = graph.m_points;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(points[i][graph.m_graph_status][j]==1 && m_map[graph.m_y+i][graph.m_x+j]==1){
				return true;
			}
		}
	}
	return false;
}

void Tetris::modify_map(Shape &graph){
	int(*points)[4][4] = graph.m_points;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(points[i][graph.m_graph_status][j]==1){
				m_map[graph.m_y+i][graph.m_x+j] = 1;
				m_color_map[graph.m_y+i][graph.m_x+j] = graph.m_color;
			}
		}
	}
}

void Tetris::eliminate(){
	int coeff=1; //double when eliminate one line
	int sum;
	for(int i=HEIGHT;i>2;){
		sum=0;
		for(int j=1;j<WIDTH+1;j++){
			sum += m_map[i][j];
		}
		if(sum==WIDTH){
			for(int j=1;j<WIDTH+1;j++){
				m_map[i][j]=0;
				m_color_map[i][j] = CLEAR;
			}
			m_score += 10*coeff;coeff*=2;
			draw_map();
			for(int m=i;m>3;m--){
				for(int n=1;n<WIDTH+1;n++){
					m_map[m][n] = m_map[m-1][n];
					m_color_map[m][n] = m_color_map[m - 1][n];
				}
			}
			pthread_mutex_lock(&g_level_mutex);
			mySleep(1200 - 200 * m_level);
			pthread_mutex_unlock(&g_level_mutex);
			draw_map();
		}else{
			i--;
		}
	}
}

void Tetris::draw_help() {

	for (int i = 0; i < 5; i++) {
		m_cursor->move_to(WIDTH + 4, 2 + i);
		switch (i) {
		case 0:
			cout << "a: move left"; break;
		case 1:
			cout << "d: move right"; break;
		case 2:
			cout << "w: rotate clockwise"; break;
		case 3:
			cout << "s: move down quick"; break;
		case 4:
			cout << "p: pause"; break;
		default:break;
		}
		m_cursor->resume();
	}
}

void Tetris::draw_score() {
	m_cursor->move_to(WIDTH + 4, HEIGHT - 2);
	cout << "Level: " << m_level;
	m_cursor->resume();
	m_cursor->move_to(WIDTH + 4, HEIGHT - 1);
	cout << "Score: " << m_score;
	m_cursor->resume();
}

void Tetris::draw_game_over() {
	m_cursor->move_to(0, HEIGHT / 2);
	cout<<\
	"    //   ) )                                //   ) )                      \n"\
	"   //         ___      _   __      ___     //   / /        ___      __    \n"\
	"  //  ____  //   ) ) // ) )  ) ) //___) ) //   / /|  / / //___) ) //  ) ) \n"\
	" //    / / //   / / // / /  / / //       //   / /|| / / //       //       \n"\
	" ((____/ / ((___(( // / /  / / ((____   ((___/ / ||/ / ((____   //        \n";
	m_cursor->resume();
}

void Tetris::play(){
	system("cls");
	m_cursor->save();

	init_map();
	draw_map();
	draw_help();
	m_score = 0;
	m_level = 1;
	draw_score();

	m_game_state = START;
	while (m_game_state != END) {
		Shape graph;
		m_cur_graph = &graph;
		draw_cur_graph(graph);
		if (collision(graph)) {
			m_game_state = END;
			break;
		}
		while (!graph.m_graph_dead) {
			while (true){
				pthread_mutex_lock(&g_game_state_mutex);
				if (m_game_state != PAUSE) {
					pthread_mutex_unlock(&g_game_state_mutex);
					break;
				}
				pthread_mutex_unlock(&g_game_state_mutex);
			}
			pthread_mutex_lock(&g_level_mutex);
			mySleep(1200 - 200 * m_level);
			pthread_mutex_unlock(&g_level_mutex);

			graph.save_status();
			graph.down();
			if (collision(graph)) {
				graph.recover_status();
				graph.m_graph_dead = true;
			}
			else {
				erase_prev_graph(graph);
				draw_cur_graph(graph);
			}
		}
		modify_map(graph);
		eliminate();
		draw_score();
	}
	draw_game_over();
}