#ifndef SPACE_H
#define SPACE_H
#include <vector>
#include <deque>
using namespace std;

class Space {
public:
	/*  Lifespan  */
	Space();
	~Space();
	Space(unsigned int height, unsigned int width); //Generate deep_field w/ size height * width 

	/*  Modifiers  */
	void 	create_star(char c);	//Generates single star in field
	void 	create_field();		//Generates star filled field
	void 	remove_front();
	void 	resize_field();
	void 	regenerate();

	/*  Getters  */
	char 	get_coord(int y, int x);	//Returns char at deep_field[y][x] for ncurses session.
	int 	get_height();
	int 	get_width();

private:
	/*  Functions  */
	int 	gen_coord(unsigned int x_limit, unsigned int y_limit);

	/*  Members  */
	deque<deque<char>>	deep_field;	//2D deque of Stars to rotate through  
	int 	MAX_Y;	//Highest available y coordinate
	int 	MAX_X;	//Highest available x coordinate
};

#endif
