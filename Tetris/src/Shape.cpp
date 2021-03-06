#include "Shape.h"
#include <stdlib.h>

int Shape::all_graph_points[7][4][4][4] ={ //[graph][i][status][j]
	{//O
		{{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0}},
		{{0, 1, 1, 0},{0, 1, 1, 0},{0, 1, 1, 0},{0, 1, 1, 0}},
		{{0, 1, 1, 0},{0, 1, 1, 0},{0, 1, 1, 0},{0, 1, 1, 0}},
		{{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0}}
	},
	{//I
		{{0, 0, 0, 0},{0, 1, 0, 0},{0, 0, 0, 0},{0, 1, 0, 0}},
		{{1, 1, 1, 1},{0, 1, 0, 0},{1, 1, 1, 1},{0, 1, 0, 0}},
		{{0, 0, 0, 0},{0, 1, 0, 0},{0, 0, 0, 0},{0, 1, 0, 0}},
		{{0, 0, 0, 0},{0, 1, 0, 0},{0, 0, 0, 0},{0, 1, 0, 0}}
	},
	{//T
		{{0, 0, 0, 0},{0, 1, 0, 0},{0, 1, 0, 0},{0, 1, 0, 0}},
		{{1, 1, 1, 0},{1, 1, 0, 0},{1, 1, 1, 0},{0, 1, 1, 0}},
		{{0, 1, 0, 0},{0, 1, 0, 0},{0, 0, 0, 0},{0, 1, 0, 0}},
		{{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0}}
	},
	{//L
		{{0, 0, 0, 0},{1, 1, 0, 0},{0, 0, 1, 0},{0, 1, 0, 0}},
		{{1, 1, 1, 0},{0, 1, 0, 0},{1, 1, 1, 0},{0, 1, 0, 0}},
		{{1, 0, 0, 0},{0, 1, 0, 0},{0, 0, 0, 0},{0, 1, 1, 0}},
		{{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0}}
	},
	{//J
		{{0, 0, 0, 0},{0, 1, 0, 0},{1, 0, 0, 0},{0, 1, 1, 0}},
		{{1, 1, 1, 0},{0, 1, 0, 0},{1, 1, 1, 0},{0, 1, 0, 0}},
		{{0, 0, 1, 0},{1, 1, 0, 0},{0, 0, 0, 0},{0, 1, 0, 0}},
		{{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0}}
	},
	{//Z
		{{0, 0, 0, 0},{0, 1, 0, 0},{1, 1, 0, 0},{0, 0, 1, 0}},
		{{1, 1, 0, 0},{1, 1, 0, 0},{0, 1, 1, 0},{0, 1, 1, 0}},
		{{0, 1, 1, 0},{1, 0, 0, 0},{0, 0, 0, 0},{0, 1, 0, 0}},
		{{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0}}
	},
	{//S
		{{0, 0, 0, 0},{1, 0, 0, 0},{0, 1, 1, 0},{0, 1, 0, 0}},
		{{0, 1, 1, 0},{1, 1, 0, 0},{1, 1, 0, 0},{0, 1, 1, 0}},
		{{1, 1, 0, 0},{0, 1, 0, 0},{0, 0, 0, 0},{0, 0, 1, 0}},
		{{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0}}
	}
};

Shape::Shape(){
	m_graph = enum_graph(rand()%GRAPH_NUM);
	m_color = enum_color(2+rand()%COLOR_NUM);
	m_points = Shape::all_graph_points[m_graph];
	m_graph_status = 0;
	m_x = WIDTH/2-2; //horizon center
	m_y = 0;
	m_graph_dead = false;
}

Shape::Shape(enum_graph graph, enum_color color){
	m_graph = graph;
	m_color = color;
	m_points = Shape::all_graph_points[m_graph];
	m_graph_status = 0;
	m_x = WIDTH/2-2; //horizon center
	m_y = 0;
	m_graph_dead = false;
}

Shape::~Shape(){
	;
}

void Shape::rotate(enum_rotate rotate){
	m_graph_status = (m_graph_status + rotate)%4;
}

void Shape::move(enum_move move){
	m_x += move;
}

void Shape::down(int distance){
	m_y += distance;
}

void Shape::save_status(){
	m_prev_x = m_x;
	m_prev_y = m_y;
	m_prev_status = m_graph_status;
}

void Shape::recover_status(){
	m_x = m_prev_x;
	m_y = m_prev_y;
	m_graph_status = m_prev_status;
}