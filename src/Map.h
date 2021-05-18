#pragma once
#include <SDL2/SDL.h>
#include "TextureManager.h"
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
	int block;
};


class Map
{
public:
	Map();
	void generate(int); // take seed as input
	void init();	
	void render(); 

private:
	SDL_Texture *wall, *path;
	SDL_Rect srcRect, destRect;
	cell MAZE[xsize][ysize];
};