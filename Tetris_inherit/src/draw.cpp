#include <stdio.h>
#include "draw.h"

#define SUPPORT_ESCAPE_CODE
#ifdef SUPPORT_ESCAPE_CODE

#define CSI "\033["

void cursor_show(bool see) {
	printf("%s?25%c", CSI, see ? 'h' : 'l');
}

void clear_screen() {
	printf("%s%s", CSI, "2J");
}

void move_to(int row, int column) {
	printf("%s%d;%dH", CSI, row + 1, column * 2 + 1);
}

void draw_block(Color color) {
	switch (color)
	{
	case BLACK:     printf("\033[40;30m  \033[0m"); break;
	case RED:       printf("\033[41;31m  \033[0m"); break;
	case GREEN:     printf("\033[42;32m  \033[0m"); break;
	case YELLOW:    printf("\033[43;33m  \033[0m"); break;
	case BLUE:      printf("\033[44;34m  \033[0m"); break;
	case MAGENTA:   printf("\033[45;35m  \033[0m"); break;
	case CRAY:      printf("\033[46;36m  \033[0m"); break;
	case WHITE:     printf("\033[47;37m  \033[0m"); break;
	case COLOR_NUM: printf("\033[8m  ");	//conceal	Not widely support
	default: break;
	}
}

#else

#include "../cscrutil/src/scrutil.h"

void cursor_show(bool see) {
	scrShowCursor(see);
}

void clear_screen() {
	scrClear();
}

void move_to(int row, int column) {
	scrMoveCursorTo(row, column*2);
}

void draw_block(Color color) {
	switch (color)
	{
	case BLACK:     scrSetColors(scrWhite, scrBlack); break;
	case RED:       scrSetColors(scrWhite, scrRed); break;
	case GREEN:     scrSetColors(scrWhite, scrGreen); break;
	case YELLOW:    scrSetColors(scrWhite, scrYellow); break;
	case BLUE:      scrSetColors(scrWhite, scrBlue); break;
	case MAGENTA:   scrSetColors(scrWhite, scrMagenta); break;
	case CRAY:      scrSetColors(scrWhite, scrCyan); break;
	case WHITE:     scrSetColors(scrWhite, scrWhite); break;
	case COLOR_NUM: scrSetColors(scrWhite, scrBlack);	//conceal	Not widely support
	default: break;
	}
    printf("  ");
    scrSetColors(scrWhite, scrBlack);
    // fflush(stdout);
}

#endif
