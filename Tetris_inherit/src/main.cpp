
#include "Tetris.h"
#include "graph.h"
#include "defines.h"

#include <stdio.h>	//fflush()
#include <stdlib.h> //rand(), system()
#include <time.h>
#include "pthread.h"

#ifdef _WIN32
    #define SO_WINDOWS
#else
    #ifdef __WIN32__
        #define SO_WINDOWS
    #else
        #ifdef __WINDOWS__
            #define SO_WINDOWS
        #else
            #define SO_UNIX
        #endif
    #endif
#endif

#ifdef SO_WINDOWS
#include <Windows.h> //Sleep()
#include <conio.h>  //_getch()
inline void my_sleep(int millisecond){
	Sleep(millisecond);
}
inline char my_getch(){
	return _getch();
	/*This don't work on git bash.
	however, codes below work
	``` 
	system("stty -icanon -echo");
	char key = getchar();
	system("stty icanon echo");
	```
	*/
}
#else
#include <unistd.h> //sleep()
#include <termios.h> //

inline void my_sleep(int millisecond){
	sleep(millisecond/1000);
}
char my_getch(){
	char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}
#endif


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
		key = my_getch();

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
		fflush(stdout);
		my_sleep(100);
	}
	pthread_exit(NULL);
    return 0;
}

int main(){
	#ifdef SO_WINDOWS
	system("cls");
	/*This bug took me a lot of my time. :-(
	If don't add this, the cmd/powershell won't support escape codes, 
	 and output messy code.
	*/
	#endif
	srand(time(0));

    pthread_mutex_init(&g_graph_mutex, NULL);
    pthread_t tid;

    pthread_create(&tid, NULL, listen_key, NULL);
	g_game.play();

	printf("Press any key to exit\n");
	my_getch();
    return 0;
}