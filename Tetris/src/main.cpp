#include <iostream>
#include "Tetris.h"
#include "Shape.h"
#include "defines.h"

#include "pthread.h"
#include "OS.h"

using namespace std;

pthread_mutex_t g_game_state_mutex, g_draw_mutex, g_level_mutex;

void* listen_key(void* ptr) {
	Tetris* game = (Tetris*)ptr;
	Shape* graph;
	char key;
	while (1) {
		key = myGetch();
		graph = game->m_cur_graph;

		pthread_mutex_lock(&g_game_state_mutex);
		if (key == 'p') {
			game->m_game_state = (game->m_game_state != PAUSE) ? PAUSE : START;
		}
		pthread_mutex_unlock(&g_game_state_mutex);
		if (graph->m_graph_dead || game->m_game_state == PAUSE) {
			continue;
		}
		if (game->m_game_state == END) {
			break;
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
			graph->down(1); break;
		default: break;
		}
		if (game->collision(*graph)) {
			graph->recover_status();
		}
		else {
			game->erase_prev_graph(*graph);
			game->draw_cur_graph(*graph);
		}
		fflush(stdout);
		mySleep(100);
	}
	pthread_exit(NULL);
	return 0;
}

void *add_level(void *ptr){
	Tetris *game = (Tetris *)ptr;
	game->m_level = 1;
	do{
		mySleep(30 * 1000);
		pthread_mutex_lock(&g_level_mutex);
		game->m_level++;
		pthread_mutex_unlock(&g_level_mutex);
	} while (game->m_level <= 4);

	pthread_exit(NULL);
	return 0;
}

int main(){
	#ifdef _WIN32
	system("cls");
	#endif
	pthread_mutex_init(&g_game_state_mutex, NULL);
	pthread_mutex_init(&g_draw_mutex, NULL);
	pthread_mutex_init(&g_level_mutex, NULL);

	pthread_t tid1, tid2;

	Tetris game;

    pthread_create(&tid1,NULL,listen_key,(void*)(&game));
    pthread_create(&tid2,NULL,add_level,(void*)(&game));

	game.play();

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	return 0;
}