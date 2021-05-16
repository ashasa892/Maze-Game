#include "App.h"


// init sdl
void App::init() {
	if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
		throw "Error while initializing SDL (SRC - init() in App.cpp)";
	}
	printf("SDL systems initialized\n");

	window = SDL_CreateWindow("Jeu de la vie", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	Map map;
	map.generate(1);
	map.draw(renderer);

  	

  	SDL_RenderPresent(renderer);
	SDL_Delay(5000);


}


// constructor
App::App(): quit(false) {

}

App::~App(void) {

}