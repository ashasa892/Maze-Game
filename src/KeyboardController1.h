#pragma once 

#include "App.h"


class KeyboardController1 : public Component
{
public:
	PositionComponent *pos;
	PlayerComponent *player;
	Fireball *fire;
	bool change;

	void init() override {
		pos = entity->getComponent<PositionComponent>();
		player = entity->getComponent<PlayerComponent>();
		fire = entity->getComponent<Fireball>();
		change = false;
	}

	void update() override {
		if (App::event.type == SDL_KEYDOWN) {
			change = true;
			switch (App::event.key.keysym.sym) {
				case SDLK_UP:
					pos->face_direction = -1;
					pos->velocity.y = -1;
					break;
				case SDLK_DOWN:
					pos->face_direction = 1;
					pos->velocity.y = 1;
					break;
				case SDLK_LEFT:
					pos->face_direction = -2;
					pos->velocity.x = -1;
					break;
				case SDLK_RIGHT:
					pos->face_direction = 2;
					pos->velocity.x = 1;
					break;
				case SDLK_SPACE:
					if(player->fireballs > 0 && !(fire->visible)){
						player->fireballs --;
						fire->visible = true;
						fire->position->pos.x = fire->parent_pos->pos.x;
						fire->position->pos.y = fire->parent_pos->pos.y;
						switch(fire->parent_pos->face_direction){
							case 1:
								fire->position->velocity.y = 1;
								fire->position->velocity.x = 0;
								break;
							case 2:
								fire->position->velocity.y = 0;
								fire->position->velocity.x = 1;
								break;
							case -1:
								fire->position->velocity.y = -1;
								fire->position->velocity.x = 0;
								break;
							case -2:
								fire->position->velocity.y = 0;
								fire->position->velocity.x = -1;
								break;
							default:
								break;
						}
					}
					break;
				default:
					break;
			}
		}

		else if (App::event.type == SDL_KEYUP) {
			change = true;
			switch (App::event.key.keysym.sym) {
				case SDLK_i:
					pos->velocity.y = 0;
					break;
				case SDLK_k:
					pos->velocity.y = 0;
					break;
				case SDLK_j:
					pos->velocity.x = 0;
					break;
				case SDLK_l:
					pos->velocity.x = 0;
					break;
				default:
					break;
			}
		}
		else {
			change = false;
		}
	}
	
};