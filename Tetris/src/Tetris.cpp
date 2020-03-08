#include <iostream>
#include <string>
#include <windows.h>
#include "Tetris.h"
using namespace std;

Tetris::Tetris(){
	m_score = 0;
	m_level = 1;
}

void Tetris::init_map(){ 
	for(int i=1;i<HEIGHT+1;i++){
		for(int j=1;j<WIDTH+1;j++){
			m_map[i][j] = 0;
		}
	}
	for(int i=1;i<HEIGHT+1;i++){
		m_map[i][0] = m_map[i][WIDTH+1] = 3;
	}
	for(int j=0;j<WIDTH+2;j++){
		m_map[HEIGHT][j] = 2;
		m_map[HEIGHT+1][j] = 3;
	}
	m_map[HEIGHT][3] = 0;
	m_map[HEIGHT][0] = 3;
	m_map[HEIGHT][WIDTH+1] = 3;
}

void Tetris::render(){
	system("cls");
	string frame;
	for(int i=1;i<HEIGHT+2;i++){
		for(int j=0;j<WIDTH+2;j++){
			switch(m_map[i][j]){
				case 0:
					frame.append("  ");break;
				case 1:
				case 2:
					frame.append("# ");break;
				case 3:
					frame.append("@ ");break;
				default:
					break;
			}
		}
		if(i==HEIGHT/2+2){
			frame.append("\t\tScore: ");
			frame.append(to_string(m_score));
		}
		if(i==HEIGHT/2){
			frame.append("\t\tLevel: ");
			frame.append(to_string(m_level));
		}
		frame.append("\n");
	}
	cout<<frame<<endl;
}

void Tetris::erase_prev_graph(Shape &graph){
	int (*points)[4][4] = graph.m_points;
	int status = graph.m_prev_status;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(points[i][status][j]==1){
				m_map[graph.m_prev_y+i][graph.m_prev_x+j] = 0;
			}
		}
	}
}

void Tetris::draw_cur_graph(Shape &graph){
	int (*points)[4][4] = graph.m_points;
	int status = graph.m_cur_status;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(points[i][status][j]==1){
				m_map[graph.m_y+i][graph.m_x+j] = (graph.m_graph_dead)?2:1;
				m_color_map[graph.m_y+i][graph.m_x+j] = graph.m_color;
			}
		}
	}
}

bool Tetris::collision(Shape &graph){
	int (*points)[4][4] = graph.m_points;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(points[i][graph.m_cur_status][j]==1 && (m_map[graph.m_y+i][graph.m_x+j]&2)==2){ //2 or 3
				return true;
			}
		}
	}
	return false;
}

void Tetris::eliminate(){
	int rank=1; //double when eliminate line
	for(int i=HEIGHT+1;i>2;){
		int sum=0;
		for(int j=1;j<WIDTH+1;j++){
			sum += m_map[i][j];
		}
		if(sum==WIDTH*2){
			for(int j=1;j<WIDTH+1;j++){
				m_map[i][j]=0;
			}
			m_score += 10*rank++;
			render();
			for(int k=i;k>2;k--){
				for(int m=1;m<WIDTH+1;m++){
					m_map[k][m] = m_map[k-1][m];
				}
			}
			Sleep(1000-m_level*200);
			render();
		}else{
			i--;
		}
	}
}

void Tetris::play(){
	init_map();
	m_game_state = START;
	while(m_game_state!=END){
		Shape graph;
		m_p_cur_graph = &graph;
		graph.down(-1); //the first line is empty line in 4*4 array
		if(collision(graph)){
			m_game_state = END;
			break;
		}
		draw_cur_graph(graph);
		render();

		while(!graph.m_graph_dead){
			Sleep(1000-m_level*200);
			graph.save_prev();
			graph.down();
			if(collision(graph)){
				graph.recover_prev();
				graph.m_graph_dead=true;
				draw_cur_graph(graph);
			}else{
				erase_prev_graph(graph);
				draw_cur_graph(graph);
				render();
			}
		}
		eliminate();
	}
}