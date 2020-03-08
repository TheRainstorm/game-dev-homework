#include <pthread.h>
#include <conio.h>
#include <windows.h>
#include "Tetris.h"
#include "defines.h"

void *listen_key(void *ptr){
	Tetris *game = (Tetris *)ptr;
	char key;
	while(1){
		key = getch();
		game->m_p_cur_graph->save_prev();
		switch(key){
			case 'a':
				game->m_p_cur_graph->move(Left);break;
			case 'd':
				game->m_p_cur_graph->move(Right);break;
			case 'w':
				game->m_p_cur_graph->rotate(Clockwise);break;
			case 's':
				game->m_p_cur_graph->down(2);break;
			default: break;
		}
		if(game->collision(*(game->m_p_cur_graph))){
			game->m_p_cur_graph->recover_prev();
		}else{
			game->erase_prev_graph(*(game->m_p_cur_graph));
			game->draw_cur_graph(*(game->m_p_cur_graph));
			game->render();
		}
	}
}

void *add_level(void *ptr){
	Tetris *game = (Tetris *)ptr;
	while(game->m_level<=4){
		Sleep(30*1000);
		game->m_level++;
	}
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