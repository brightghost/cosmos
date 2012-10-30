/*
 * =====================================================================================
 *
 *       Filename:  cosmos.cc
 *
 *    Description:  Main file for cosmos 
 *
 *        Version:  1.0
 *        Created:  10/18/2012 16:23:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Tom Auty
 *   Organization:  N/A
 *
 * =====================================================================================
 */
#include <iostream>
#include <time.h>
#include <ncurses.h>
#include <stdlib.h>
#include "space.h"
using namespace std;

WINDOW* create_window(int height, int width, int starty, int startx); 
void shift_left(Space *space, int height); 
void print_next_col(Space *space, int height, int width); 

int main () { 

	/*  Start ncurses session  */
	initscr();	
	clear();
	noecho();
	cbreak();
	nonl();
	curs_set(0);
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);
	srand(time(0));

	/*  Allocate window size maxY * maxX  */
	int maxY, maxX;
	int HEIGHT, WIDTH;
	getmaxyx(stdscr, maxY, maxX);
	WINDOW* main_window = create_window(maxY, maxX, 0, 0);

	/*  Define furthest printable row/col  */
	HEIGHT = maxY - 1;
	WIDTH = maxX - 1;
	
	/*  Defines color pair if colors available for terminal  */
	if(has_colors()) {
		start_color();
		init_pair(1, COLOR_WHITE, COLOR_BLACK);
		attron(COLOR_PAIR(1));
	}

	/*  Create space and stars  */
	Space *space = new Space(HEIGHT, WIDTH);
	space->create_field();
	for(int i = 0; i < HEIGHT; ++i) {
		for(int j = 0; j < WIDTH; ++j) {
			move(i, j);
			addch(space->get_coord(i, j));
		}
	}
	/*  Help message  */
	mvprintw(HEIGHT, 0, "Press 'q' to quit. Press 'h' to hide this message.");
	refresh();
	
	/*  Quit handler and body generation  */
	int ch;
	int width_tracker = WIDTH;
	while(1) {
		timeout(80);
		if(width_tracker == (WIDTH * 10)-1) {
			space->resize_field();
			space->regenerate();
			width_tracker = WIDTH;
		}
		shift_left(space, HEIGHT);
		print_next_col(space, HEIGHT, WIDTH);
		ch = getch(); 
		if(ch == 'h') {		//Hide quit prompt
			move(HEIGHT, WIDTH);
			deleteln();
		}
		if(ch == 'q') break;
		width_tracker++;
	}
	/*  Delete stars  */

	/*  End ncurses session  */
	endwin();
	return 0;

}

/*  Subroutine for window creation (used only once)  */
WINDOW* create_window(int height, int width, int starty, int startx) {
	WINDOW* this_window;
	this_window = newwin(height, width, starty, startx);

	box(this_window, 0, 0);
	wrefresh(this_window);

	return this_window;
}

/*  Shift space one column left and pop column from structure  */
void shift_left(Space *space, int height) {
	for(int i = 0; i < height; ++i) {
		move(i, 0);
		delch();
	}	
	space->remove_front();
}

/*  Print new rightmost column after pop from shift_left  */
void print_next_col(Space *space, int height, int width) {
	for(int i = 0; i < height; i++) {
		move(i, width);
		char c = space->get_coord(i, width);
		addch(c);
	}
}
