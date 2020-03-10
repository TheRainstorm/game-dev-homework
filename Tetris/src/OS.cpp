#include "OS.h"
#include <iostream>
/*
GUN/GCC: linux
MinGW: _WIN32
MSVC: _WIN32 _WINDOWS_
*/
#ifdef _WIN32
#include <Windows.h>
#include <conio.h>
#endif
#ifdef linux
#include <unistd.h>
#include <stdlib.h>
#endif

void mySleep(int time) {
#ifdef _WIN32
	Sleep(time);
#endif
#ifdef linux
	sleep(time / 1000);
#endif
}

void clearScreen() {
	std::cout << "\33[2J";
}

char myGetch() {
#ifdef _WIN32
	return _getch();
#endif
#ifdef linux
	system("stty -echo");
	char ch = getchar();
	system("stty echo");

	return ch;
#endif
}