#include "Map.h"


void Map::init() {
	//Initialize the maze!
	for(int x=0;x<xsize;x++) {
		for(int y=0;y<ysize;y++){
			MAZE[x][y].block = 0;
		}
	}
	return;
}


void Map::generate(int seed){
	init();
	srand(seed);

	for (auto x=0; x < xsize; ++x) {
		for (auto y=0; y < ysize; ++y) {
			MAZE[x][y].block = rand()%2;
		}
	}
}

void Map::draw(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
	
	for (auto x = 0; x < xsize; ++x) {
		for (auto y = 0; y < ysize; ++y)
		{	
 			if (MAZE[x][y].block)
			{
				SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
				SDL_Rect rect{ x * RATIO, y * RATIO, RATIO, RATIO};
				SDL_RenderFillRect(renderer, &rect);
				
			}
			
		}
	}

}

Map::Map() {

}