#include <iostream>
#include <conio.h>
#include <windows.h>
#include "Tetris.h"
#include "Shape.h"
#include "defines.h"
#include "pthread.h"

using namespace std;

void* listen_key(void* ptr) {
	Tetris* game = (Tetris*)ptr;
	Shape* graph;
	char key;
	while (1) {
		key = _getch();
		graph = game->m_cur_graph;

		if (key == 'p') {
			game->m_game_state = (game->m_game_state != PAUSE) ? PAUSE : START;
		}
		if (graph->m_graph_dead || game->m_game_state == PAUSE) {
			continue;
		}
		graph->save_status();
		switch (key) {
		case 'a':
			graph->move(Left); break;
		case 'd':
			graph->move(Right); break;
		case 'w':
			graph->rotate(Clockwise); break;
		case 's':
			graph->down(2); break;
		default: break;
		}
		if (game->collision(*graph)) {
			graph->recover_status();
		}
		else {
			game->erase_prev_graph(*graph);
			game->draw_cur_graph(*graph);
		}
		Sleep(100);
	}
}

void *add_level(void *ptr){
	Tetris *game = (Tetris *)ptr;
	game->m_level = 1;
	do{
		Sleep(30 * 1000);
		game->m_level++;
	} while (game->m_level <= 4);
	return 0;
}

int main(){
	Tetris game;
	pthread_t tid1;
	pthread_t tid2;

    pthread_create(&tid1,NULL,listen_key,(void*)(&game));
    pthread_create(&tid2,NULL,add_level,(void*)(&game));
	game.play();

	return 0;
}