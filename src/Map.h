#include <SDL2/SDL.h>
#include <iostream>


#define ysize 15
#define xsize 20
#define RATIO 32

// for maze generation
#define UP 0     //-y
#define DOWN 1   //+y
#define LEFT 2   //-x
#define RIGHT 3  //+x


struct cell{
	bool block;
};


class Map
{
public:
	Map();
	void generate(int); // take seed as input
	void init();	
	void draw(SDL_Renderer*); 

private:

	cell MAZE[xsize][ysize];
};