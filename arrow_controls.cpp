#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define xmax 100
#define ymax 100

int mxmax = 0, mymax = 0;
char maze[xmax][ymax];

void initialize() {
	initscr();
	raw();
	noecho();
	nonl();
	intrflush( stdscr, FALSE );
	keypad( stdscr, TRUE );
}

void finalize() { 
	endwin();
}

void loadMaze(const char *mazeFileName) {
    int X = 0;
    int Y = 0;
    FILE *fp = NULL;
   
    for (Y = 0; Y <= ymax; Y++) {
        for (X = 0; X <= xmax; X++) {
            maze[X][Y] = ' ';
        }
}
	X = 0;
	Y = 0;
    if ((fp = fopen(mazeFileName, "r")) == NULL) {
        fprintf(stderr, "\n\tERROR ");
        perror(mazeFileName);
        fprintf(stderr, "\n");
        exit(EXIT_FAILURE);
    }
    else {
        while ((!feof(fp)) && (Y <= ymax)) {
            X = 0;
            while ((!feof(fp)) && (X <= xmax)) {
                char temp;
                fscanf(fp, "%c", &temp);
                if (temp != '\n') {
                    maze[Y][X++] = temp;
                }
                else break;
            }
	mxmax = X;
	mymax = Y;
            Y++;
        }
        fclose(fp);
    }
}

void printMaze(){
	for(int i = 0; i < xmax; i++){
		for(int j = 0; j < ymax; j++){
			mvprintw( i, j, "%c", maze[i][j]);
		}
	}
	refresh();
}

int x = 10, y= 20, x2 = 15, y2 = 25;

bool a = true;


int main() {
	int ch;
	initialize();
	loadMaze("hello.txt");
	while (a) {
		curs_set(0);
		wclear( stdscr );
		printMaze();
		wmove( stdscr, x, y );
		waddch( stdscr, ACS_DIAMOND );
		wmove( stdscr, x2, y2 );
		waddch( stdscr, ACS_BULLET );
		

		wrefresh( stdscr );

		ch = wgetch( stdscr);
		switch (ch) {
			case KEY_UP: 
				wrefresh( stdscr );
				mvaddch( y, x-1, ACS_DIAMOND );
				x -= 1;
				break;
			case KEY_DOWN:
				wrefresh( stdscr );
				mvaddch( y, x+1, ACS_DIAMOND );
				x += 1;
				break;
			case KEY_LEFT:
				wrefresh( stdscr );
				mvaddch( y-1, x, ACS_DIAMOND );
				y -= 1;
				break;			
			case KEY_RIGHT:
				wrefresh( stdscr );
				mvaddch( y+1, x, ACS_DIAMOND );
				y += 1;
				break;
			case 'w': 
				wrefresh( stdscr );
				mvaddch( y, x-1, ACS_DIAMOND );
				x2 -= 1;
				break;
			case 's':
				wrefresh( stdscr );
				mvaddch( y, x+1, ACS_DIAMOND );
				x2 += 1;
				break;
			case 'a':
				wrefresh( stdscr );
				mvaddch( y-1, x, ACS_DIAMOND );
				y2 -= 1;
				break;			
			case 'd':
				wrefresh( stdscr );
				mvaddch( y+1, x, ACS_DIAMOND );
				y2 += 1;
				break;
			case KEY_BACKSPACE:
				a = false;
				wrefresh( stdscr );
				finalize();
				break;
			default:
				break;
				
		}
		if(!a) {
			endwin();
			break;
		}
	}
	
	finalize();
	return 0;
}


