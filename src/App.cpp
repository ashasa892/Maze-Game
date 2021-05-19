#include "App.h"

#include "Map.h"
#include "TextureManager.h"
#include "Components.h"


Map map;
Manager manager;
Entity* player1;
Entity* player2;
std::vector<CollisionComponent*> colliders;


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

	initMapTiles();
	
	player1 = &(manager.addEntity());
  	player1->addComponent<PositionComponent>();
  	player1->addComponent<PlayerComponent>("../res/player1.png");
  	player1->addComponent<KeyboardController1>();
  	player1->addComponent<CollisionComponent>("player1");
  	colliders.push_back(player1->getComponent<CollisionComponent>());
	
	player2 = &(manager.addEntity());
  	player2->addComponent<PositionComponent>(100,100);
  	player2->addComponent<PlayerComponent>("../res/player2.png");
  	player2->addComponent<KeyboardController2>();
  	player2->addComponent<CollisionComponent>("player2");
  	colliders.push_back(player2->getComponent<CollisionComponent>());
// 
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

bool App::AABB(const SDL_Rect& recA, const SDL_Rect& recB) {
	return (recA.x + recA.w > recB.x) &&
		   (recB.x + recB.w > recA.x) &&
		   (recA.y + recA.h > recB.y) &&
		   (recB.y + recB.h > recA.y);
}

void App::update() {
	manager.refresh();
	manager.update();
	int i=0;
	std::cout << colliders.size() << std::endl;
	for (auto cc : colliders) {
		std::cout << i++ << " " << cc->tag << std::endl;
		if (cc->tag == "player1" || cc->tag == "path") continue;
		
		SDL_Rect playerRect = player1->getComponent<CollisionComponent>()->collider;

		if (AABB(playerRect, cc->collider)) {
			// std::cout << cc->tag << std::endl;

			for (int i=1; i<=3; i++) {
				SDL_Rect tempRect = playerRect;
				tempRect.x = playerRect.x + i;
				if (!AABB(tempRect, cc->collider)) {
					playerRect = tempRect;
					break;
				}

				tempRect.x = playerRect.x - i;
				if (!AABB(tempRect, cc->collider)) {
					playerRect = tempRect;
					break;
				}

				tempRect.y = playerRect.y + i;
				if (!AABB(tempRect, cc->collider)) {
					playerRect = tempRect;
					break;
				}

				tempRect.y = playerRect.y - i;
				if (!AABB(tempRect, cc->collider)) {
					playerRect = tempRect;
					break;
				}
			}
			std::cout << "Player 1 hit " << cc->tag << std::endl;
			PositionComponent* pos = player1->getComponent<PositionComponent>();
			// pos->velocity = pos->velocity.scalerMul(-1);
			// pos->pos = pos->pos.add(pos->velocity.scalerMul(pos->speed));
			std::cout << "before collision "; pos->pos.print();
			pos->velocity = Point2D(0,0);
			pos->pos = Point2D(playerRect.x, playerRect.y);
			std::cout << "after collision "; pos->pos.print();
			break;
		}
	}

	player1->getComponent<PositionComponent>()->pos.print();
	player1->getComponent<PositionComponent>()->velocity.print();
	
}


void App::initMapTiles() {
	for (auto x=0; x<xsize; x++) {
		for (auto y=0; y<ysize; y++) {
			Entity* tile = &(manager.addEntity());
			tile->addComponent<PositionComponent>(x*RATIO, y*RATIO);
			std::string tileType;
			if (map.MAZE[x][y].block) {
				tileType = "path";
			}
			else {
				tileType = "wall";
			}
			std::string filePath = ("../res/"+tileType+".png");
			tile->addComponent<PlayerComponent>(filePath.c_str());
			tile->addComponent<CollisionComponent>(tileType);
			if (tileType == "wall") colliders.push_back(tile->getComponent<CollisionComponent>());
		}
	}
}

void App::render() {
	// map.render();	
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