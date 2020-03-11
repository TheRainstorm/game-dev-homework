
#include "Tetris.h"
#include "graph.h"
#include "defines.h"

#include <stdlib.h> //rand()

Graph *graph_factory(){
	int r = rand()%7;
	Graph * graph;
	switch(r){
		case 0:
		case 1:
		case 2:
		case 3: graph = new O_graph();break;
		case 4:
		case 5: 
		case 6: graph = new T_graph();break;
		default: graph = new T_graph(); break;
	}
	return graph;
}

int main(){
    Tetris game;

	game.play();
    return 0;
}