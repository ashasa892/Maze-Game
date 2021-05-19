#include "Map.h"


void Map::init() {
	//Initialize the maze!
	for(int x=0;x<xsize;x++) {
		for(int y=0;y<ysize;y++){
			MAZE[x][y].block = 0;
		}
	}
	wall = TextureManager::loadTexture("../res/wall.png");
	path = TextureManager::loadTexture("../res/path.png");
	srcRect.x = srcRect.y = 0;
	srcRect.w = srcRect.h = destRect.w = destRect.h = RATIO;
	return;
}

void Map::generate(int seed){
	init();
	srand(seed);

	for (auto x=0; x < xsize; ++x) {
		for (auto y=0; y < ysize; ++y) {
			MAZE[x][y].block = (rand()%7)?1:0;
		}
	}
}

//deprecated (use initMapTiles in App)
void Map::render() {
	// SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
	// SDL_RenderPresent(renderer);
	std::cout << "ha" << std::endl;
	for (auto x = 0; x < xsize; ++x) {
		for (auto y = 0; y < ysize; ++y)
		{	
			destRect.x = x*RATIO, destRect.y = y*RATIO;
			// SDL_Rect rect{ x * RATIO, y * RATIO, RATIO, RATIO};
 			if (MAZE[x][y].block)
			{
				// path
				TextureManager::render(path, srcRect, destRect);
				// SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );

			}
			else
			{
				// wall
				TextureManager::render(wall, srcRect, destRect);
				// SDL_SetRenderDrawColor( renderer, 255, 255, 0, 255 );
			}
			// SDL_RenderFillRect(renderer, &rect);
		}
	}

}

Map::Map() {

}