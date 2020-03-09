#ifndef SHAPE_H
#define SHAPE_H
#include "defines.h"

class Shape
{
public:
	Shape(); //random
	Shape(enum_graph, enum_color);
	~Shape();

	void move(enum_move); //move left or right
	void rotate(enum_rotate); //rotate clockwise or anticlockwise
	void down(int distance=1); //move down with given distance

	void save_status(); //save current status(position and graph status)
	void recover_status(); //recover status from prev status
public:
	enum_graph m_graph; 
	enum_color m_color;
	int (*m_points)[4][4]; //every graph is a 4*4 array and has 4 status
	int m_graph_status;
	int m_x, m_y; //the place of left top point of graph array

	int m_prev_status, m_prev_x, m_prev_y;
	bool m_graph_dead; //dead graph won't move any more
public:
	static int all_graph_points[7][4][4][4];
};

#endif