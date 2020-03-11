#ifndef GRAPH_H
#define GRAPH_H

#include "defines.h"

class Graph {
public:
	int* m_points;         //use 2-d array to represent a graph
	Color m_color;
	int m_height, m_width;

	int m_row, m_column;    //place
	bool m_dead;
protected:
	int* m_prev_points;
	int m_prev_row, m_prev_column;
	int m_rotate_status;
public:
	Graph();
	void move_left();
	void move_right();
	virtual void rotate() = 0;  //every graph has different number of rotate status
	void down();

	virtual int get_point(int*, int, int) = 0;//get (i,j) from m_points 

	void save();
	void resume();
	void draw();
	void erase();
	void set_position(int, int);
};

class O_graph :public Graph {
public:
	static int all_points[1][2][2];
public:
	O_graph() {
		m_width = 2;
		m_height = 2;
		m_row = 1;
		m_column = WIDTH / 2 - 2;
		m_color = RED;
		m_rotate_status = 0;
		m_points = &(O_graph::all_points[0][0][0]);
	};
	void rotate() {};      //1 status

	int get_point(int* points, int i, int j) {
		return *(points + i * m_width + j);
	}
};

class T_graph :public Graph {
public:
	static int all_points[4][3][3];
public:
	T_graph() {
		m_width = 3;
		m_height = 3;
		m_row = 0;
		m_column = WIDTH / 2 - 2;
		m_color = GREEN;
		m_rotate_status = 0;
		m_points = &(T_graph::all_points[0][0][0]);
	};
	void rotate() {//4 status
		m_rotate_status = (m_rotate_status + 1) % 4;
		m_points = &(T_graph::all_points[m_rotate_status][0][0]);
	};

	int get_point(int* points, int i, int j) {
		return *(points + i * m_width + j);
	}
};

#endif
