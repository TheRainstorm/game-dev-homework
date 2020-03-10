#include "OS.h"

#include <iostream>
using namespace std;

/*	GUN/GCC: linux
	MinGW: _WIN32
	MSVC: _WIN32 _WINDOWS_
*/
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
#include <Windows.h>
#include <conio.h>

void mySleep(int time) {
	Sleep(time);
}

char myGetch() {
	return _getch();
}

#else
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void mySleep(int time) {
	sleep(time / 1000);
}

char myGetch() {
	system("stty -echo");
	char ch = getchar();
	system("stty echo");

	return ch;
}
#endif

void cursor_show(bool see) {
	printf("%s?25%c", "\033[", see ? 'h' : 'l');
}
void cursor_clear_screen() {
	printf("\033[2J"); //y row, x column
}

void cursor_move_to(int x, int y)
{
	const char* CSI = "\033[";
	printf("%s%d;%dH", CSI, y + 1, x * 2 + 1); //y row, x column
}

void cursor_draw_block(enum_color color) {
	switch (color)
	{
	case BLACK:printf("\033[40;30m  \033[0m"); break;
	case RED:printf("\033[41;31m  \033[0m"); break;
	case GREEN:printf("\033[42;32m  \033[0m"); break;
	case YELLOW:printf("\033[43;33m  \033[0m"); break;
	case BLUE:printf("\033[44;34m  \033[0m"); break;
	case PURPLE:printf("\033[45;35m  \033[0m"); break;
	case DEEP_GREEN:printf("\033[46;36m  \033[0m"); break;
	case WHITE:printf("\033[47;37m  \033[0m"); break;
	case CLEAR:printf("\033[8m  ");	//conceal	Not widely support
	default: break;
	}
}