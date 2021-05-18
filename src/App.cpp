#include "App.h"

#include "Map.h"
#include "TextureManager.h"
#include "Components.h"

Map map;
Manager manager;
Entity* player1;
Entity* player2;


SDL_Event App::event;


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

	TextureManager::renderer = renderer;
	map.generate(1);


	
	player1 = &(manager.addEntity());
  	player1->addComponent<PositionComponent>();
  	player1->addComponent<PlayerComponent>("../res/player1.png");
  	player1->addComponent<KeyboardController1>();
	
	player2 = &(manager.addEntity());
  	player2->addComponent<PositionComponent>();
  	player2->addComponent<PlayerComponent>("../res/player2.png");
  	player2->addComponent<KeyboardController2>();


}

void App::handleEvents() {
	// SDL_Event event;
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
	player1->getComponent<PositionComponent>()->pos.print();
	player2->getComponent<PositionComponent>()->pos.print();
	
}

void App::render() {
	map.render();
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