#include "App.h"
#include "Map.h"
#include "TextureManager.h"
#include "Components.h"


Map map;
Manager manager;
Entity* player1;
Entity* player2;
Entity* target1_1;
Entity* target1_2;
Entity* target2_1;
Entity* target2_2;
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
	
	target1_1 = &(manager.addEntity());
	target1_1->addComponent<PositionComponent>(576,32);
	target1_1->addComponent<Target>("../res/target1.png");
	
	target1_2 = &(manager.addEntity());
	target1_2->addComponent<PositionComponent>(576,416);
	target1_2->addComponent<Target>("../res/target1.png");
	
	target2_1 = &(manager.addEntity());
	target2_1->addComponent<PositionComponent>(32,32);
	target2_1->addComponent<Target>("../res/target2.png");
	
	target2_2 = &(manager.addEntity());
	target2_2->addComponent<PositionComponent>(32,416);
	target2_2->addComponent<Target>("../res/target2.png");
	
	player1 = &(manager.addEntity());
  	player1->addComponent<PositionComponent>(544,384);
  	player1->addComponent<PlayerComponent>("../res/player1.png");
	player1->addComponent<Fireball>("../res/Fireball.png", &(manager.addEntity()));
  	player1->addComponent<KeyboardController1>();
  	player1->addComponent<CollisionComponent>("player1");
	player1->getComponent<Fireball>()->ent->addComponent<CollisionComponent>("Fireball1");
  	colliders.push_back(player1->getComponent<CollisionComponent>());
	colliders.push_back(player1->getComponent<Fireball>()->ent->getComponent<CollisionComponent>());
	
	player2 = &(manager.addEntity());
  	player2->addComponent<PositionComponent>(64,64);
  	player2->addComponent<PlayerComponent>("../res/player2.png");
	player2->addComponent<Fireball>("../res/Fireball.png", &(manager.addEntity()));
  	player2->addComponent<KeyboardController2>();
  	player2->addComponent<CollisionComponent>("player2");
	player2->getComponent<Fireball>()->ent->addComponent<CollisionComponent>("Fireball2");
  	colliders.push_back(player2->getComponent<CollisionComponent>());
	colliders.push_back(player2->getComponent<Fireball>()->ent->getComponent<CollisionComponent>());
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
	// check collisions
	return (recA.x + recA.w > recB.x) &&
		   (recB.x + recB.w > recA.x) &&
		   (recA.y + recA.h > recB.y) &&
		   (recB.y + recB.h > recA.y);
}

void App::update() {
	manager.refresh();
	manager.update();
	CollisionCheck();
	TargetCheck();
}

void App::initMapTiles() {
	// initialize wall and path tiles
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
	manager.render();
	SDL_RenderPresent(renderer);
}

App::App() {
	// constructor
	quit = false;
}

App::~App(void) {
	//destructor
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "SDL systems shut down" << std::endl;
}

void App::CollisionCheck(){
	int i=0;
	for (auto cc : colliders) {
		//loop through all colliding components to handle collisions
		if (cc->tag == "path") continue;
		SDL_Rect player1Rect = player1->getComponent<CollisionComponent>()->collider;
		if (AABB(player1Rect, cc->collider)) {
			if(cc->tag == "wall" || cc->tag == "player2"){
				for (int i=1; i<=3; i++) {
					SDL_Rect tempRect = player1Rect;
					tempRect.x = player1Rect.x + i;
					if (!AABB(tempRect, cc->collider)) {
						player1Rect = tempRect;
						break;
					}
					tempRect.x = player1Rect.x - i;
					if (!AABB(tempRect, cc->collider)) {
						player1Rect = tempRect;
						break;
					}
					tempRect.y = player1Rect.y + i;
					if (!AABB(tempRect, cc->collider)) {
						player1Rect = tempRect;
						break;
					}
					tempRect.y = player1Rect.y - i;
					if (!AABB(tempRect, cc->collider)) {
						player1Rect = tempRect;
						break;
					}
				}
				PositionComponent* pos = player1->getComponent<PositionComponent>();
				pos->velocity = Point2D(0,0);
				pos->pos = Point2D(player1Rect.x, player1Rect.y);
			}
			else if(cc->tag == "Fireball2"){
				if(player2->getComponent<Fireball>()->visible){
					player1->getComponent<PlayerComponent>()->health = std::max(0, player1->getComponent<PlayerComponent>()->health - 20);
					player2->getComponent<Fireball>()->visible = false;
				}
			}
		}
		SDL_Rect player2Rect = player2->getComponent<CollisionComponent>()->collider;
		if (AABB(player2Rect, cc->collider)) {
			if(cc->tag == "wall" || cc->tag == "player1"){
				for (int i=1; i<=3; i++) {
					SDL_Rect tempRect = player2Rect;
					tempRect.x = player2Rect.x + i;
					if (!AABB(tempRect, cc->collider)) {
						player2Rect = tempRect;
						break;
					}
					tempRect.x = player2Rect.x - i;
					if (!AABB(tempRect, cc->collider)) {
						player2Rect = tempRect;
						break;
					}
					tempRect.y = player2Rect.y + i;
					if (!AABB(tempRect, cc->collider)) {
						player2Rect = tempRect;
						break;
					}
					tempRect.y = player2Rect.y - i;
					if (!AABB(tempRect, cc->collider)) {
						player2Rect = tempRect;
						break;
					}
				}
				PositionComponent* pos = player2->getComponent<PositionComponent>();
				pos->velocity = Point2D(0,0);
				pos->pos = Point2D(player2Rect.x, player2Rect.y);
			}
			else if(cc->tag == "Fireball1"){
				if(player1->getComponent<Fireball>()->visible){
					player2->getComponent<PlayerComponent>()->health = std::max(0, player2->getComponent<PlayerComponent>()->health - 20);
					player1->getComponent<Fireball>()->visible = false;
				}
			}
		}
		SDL_Rect fire1 = player1->getComponent<Fireball>()->ent->getComponent<CollisionComponent>()->collider;
		if (AABB(fire1, cc->collider)) {
			if(cc->tag == "wall"){
				if(player1->getComponent<Fireball>()->visible){
					player1->getComponent<Fireball>()->visible = false;
				}
			}
		}
		SDL_Rect fire2 = player2->getComponent<Fireball>()->ent->getComponent<CollisionComponent>()->collider;
		if (AABB(fire2, cc->collider)) {
			if(cc->tag == "wall"){
				if(player2->getComponent<Fireball>()->visible){
					player2->getComponent<Fireball>()->visible = false;
				}
			}
		}
	}
}

void App::TargetCheck(){
	int x1 = player1->getComponent<PositionComponent>()->pos.x;	
	int x2 = player2->getComponent<PositionComponent>()->pos.x;
	int y1 = player1->getComponent<PositionComponent>()->pos.y;
	int y2 = player2->getComponent<PositionComponent>()->pos.y;
	if(32 <= x1 && x1 <= 32 + 32){
		if(32 <= y1 && y1 <= 32 + 32){
			if(target2_1->getComponent<Target>()->active){
				player2->getComponent<PlayerComponent>()->health = std::max(0, player2->getComponent<PlayerComponent>()->health - 30);
				target2_1->getComponent<Target>()->active = false;
			}
		}
		else if(416 <= y1 + 32 && y1 + 32 <= 416 + 32){
			if(target2_2->getComponent<Target>()->active){
				player2->getComponent<PlayerComponent>()->health = std::max(0, player2->getComponent<PlayerComponent>()->health - 30);
				target2_2->getComponent<Target>()->active = false;
			}
		}
	}
	if(576 <= x2 + 32 && x2 + 32 <= 576 + 32){
		if(32 <= y2 && y2 <= 32 + 32){
			if(target1_1->getComponent<Target>()->active){
				player1->getComponent<PlayerComponent>()->health = std::max(0, player1->getComponent<PlayerComponent>()->health - 30);
				target1_1->getComponent<Target>()->active = false;
			}
		}
		else if(416 <= y2 + 32 && y2 + 32 <= 416 + 32){
			if(target1_2->getComponent<Target>()->active){
				player1->getComponent<PlayerComponent>()->health = std::max(0, player1->getComponent<PlayerComponent>()->health - 30);
				target1_2->getComponent<Target>()->active = false;
			}
		}
	}
}