
#include "Tetris.h"
#include "graph.h"
#include "defines.h"

#include <stdlib.h> //rand()
#include <Windows.h>
#include "pthread.h"
#include <conio.h>  //_getch()

Tetris g_game;
pthread_mutex_t g_graph_mutex;

Graph *graph_factory(){
	int r = rand()%7;
	Graph * graph;
	switch(r){
		case 0: graph = new O_graph(); break;
		case 1: graph = new I_graph(); break;
		case 2: graph = new T_graph(); break;
		case 3: graph = new L_graph();break;
		case 4: graph = new J_graph(); break;
		case 5: graph = new Z_graph(); break;
		case 6: graph = new T_graph();break;
		default: graph = new T_graph(); break;
	}
	return graph;
}

void * listen_key(void *) {
	char key;
	while (1) {
		if(g_game.m_game_state == END) break;
		key = _getch();

		if (key == 'p') {
			g_game.m_game_state = (g_game.m_game_state != PAUSE) ? PAUSE : RUNNING;
			g_game.draw_pause(g_game.m_game_state != PAUSE);
		}
		if (g_game.m_graph->m_dead || g_game.m_game_state != RUNNING) {
			continue;
		}

		pthread_mutex_lock(&g_graph_mutex);
		g_game.m_graph->save();
		switch (key) {
		case 'a':
			g_game.m_graph->move_left(); break;
		case 'd':
			g_game.m_graph->move_right(); break;
		case 'w':
			g_game.m_graph->rotate(); break;
		case 's':
			g_game.m_graph->down(); break;
		default: break;
		}
		if (g_game.detect_collision()) {
			g_game.m_graph->resume();
		}
		else {
			g_game.m_graph->erase();
			g_game.m_graph->draw();
		}
        pthread_mutex_unlock(&g_graph_mutex);
		Sleep(100);
	}
	pthread_exit(NULL);
    return 0;
}

int main(){
    pthread_mutex_init(&g_graph_mutex, NULL);
    pthread_t tid;

    pthread_create(&tid, NULL, listen_key, NULL);
	g_game.play();
    return 0;
}