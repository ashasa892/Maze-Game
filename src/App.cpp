#include "App.h"





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

	// map.draw(renderer);
	TextureManager::renderer = renderer;
	player1 = &(manager.addEntity());
  	player1->addComponent<PositionComponent>();
  	player1->addComponent<PlayerComponent>("../res/cat.ico");
  	manager.render();
  	
  	// SDL_RenderPresent(renderer);
	// std:: cout << player1->getComponent<PositionComponent>().x() << " " << player1->getComponent<PositionComponent>().y() << std::endl;


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
	manager.refresh();
	manager.update();
	std:: cout << player1->getComponent<PositionComponent>()->x() << " " << player1->getComponent<PositionComponent>()->y() << std::endl;
}

void App::render() {
	// map.draw(renderer);
	manager.render();
	SDL_RenderPresent(renderer);
}


// constructor
App::App() {
	quit = false;
}

App::~App(void) {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "SDL systems shut down" << std::endl;
}