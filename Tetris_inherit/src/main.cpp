#include "graph.h"
#include <Windows.h>
#include <stdlib.h>

int main(){
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

    return 0;
}