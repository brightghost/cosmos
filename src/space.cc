#include "space.h"
#include <iostream> //TESTING ONLY
#include <vector>
#include <deque>
#include <stdlib.h>
using namespace std;
/*  Lifespan  */
Space::Space() {}
Space::~Space() {}
Space::Space(unsigned int height, unsigned int width) {

	MAX_Y = height;
	MAX_X = width*10;
	
	for(int i = 0; i < MAX_Y; ++i) {
		deep_field.push_back(deque< char >(MAX_X, ' '));
	}
}

/*  Modifiers  */
void Space::create_star(char c) {
	int x_coord = gen_coord(0, MAX_X);
	int y_coord = gen_coord(0, MAX_Y);
	deep_field[y_coord][x_coord] = c;
}

void Space::create_field() {
	for(int i = 0; i < MAX_Y + MAX_X; ++i) {
		if((i % 3 != 0))
		       	create_star('.');
		else
		       	create_star('*');	
	}
}

int Space::gen_coord(unsigned int low_limit, unsigned int high_limit) {
	return (rand() % (high_limit - low_limit)) + low_limit;
}

void Space::remove_front() {
	for(int i = 0; i < MAX_Y; ++i) {
		deep_field[i].pop_front();
	}
}

void Space::resize_field() {
	int cur = get_width();
	for(int i = 0; i < MAX_Y; ++i) {
		deep_field[i].resize(MAX_X);
	}
	for(int i = cur; i < MAX_X; ++i) {
		for(int j = 0; j < MAX_Y; ++j) {
			deep_field[j][i] = ' ';
		}
	}
}
void Space::regenerate() {
	create_field();
}

/*  Getters  */
char Space::get_coord(int y, int x) {
	return deep_field[y][x];
}

int Space::get_height() {
	return MAX_Y;
}

int Space::get_width() {
	return deep_field[0].size();
}
