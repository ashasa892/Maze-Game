#include "App.h"

Manager manager;
auto& newPlayer(manager.addEntity());	


// init sdl
void App::init() {
	if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
		throw "Error while initializing SDL (SRC - init() in App.cpp)";
	}
	printf("SDL systems initialized\n");

	window = SDL_CreateWindow(GAME_NAME, SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	
	map.generate(1);
	map.draw(renderer);

  	newPlayer.addComponent<PositionComponent>();

  	SDL_RenderPresent(renderer);
	


}

void App::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch(event.type) {
		case SDL_QUIT:
			setQuit(true);
		default:
			break;
	}
}

void App::update() {
	manager.update();
	std:: cout << newPlayer.getComponent<PositionComponent>().x() << " " << newPlayer.getComponent<PositionComponent>().x() << std::endl;
}

void App::render() {

}


// constructor
App::App(): quit(false) {

}

App::~App(void) {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "SDL systems shut down" << std::endl;
}