#pragma once 

#include "App.h"


class KeyboardController2 : public Component
{
public:
	PositionComponent *pos;
	PlayerComponent *player;
	Fireball *fire;

	void init() override {
		pos = entity->getComponent<PositionComponent>();
		player = entity->getComponent<PlayerComponent>();
		fire = entity->getComponent<Fireball>();
	}

	void update() override {
		if (App::event.type == SDL_KEYDOWN) {
			switch (App::event.key.keysym.sym) {
				case SDLK_w:
					pos->face_direction = -1;
					pos->velocity.y = -1;
					break;
				case SDLK_s:
					pos->face_direction = 1;
					pos->velocity.y = 1;
					break;
				case SDLK_a:
					pos->face_direction = -2;
					pos->velocity.x = -1;
					break;
				case SDLK_d:
					pos->face_direction = 2;
					pos->velocity.x = 1;
					break;
				case SDLK_KP_ENTER:
					if(player->fireballs > 0 && !fire->visible){
						player->fireballs --;
						fire->visible = true;
					}
					break;
				default:
					break;
			}
		}

		if (App::event.type == SDL_KEYUP) {
			switch (App::event.key.keysym.sym) {
				case SDLK_w:
					pos->velocity.y = 0;
					break;
				case SDLK_s:
					pos->velocity.y = 0;
					break;
				case SDLK_a:
					pos->velocity.x = 0;
					break;
				case SDLK_d:
					pos->velocity.x = 0;
					break;
				default:
					break;
			}
		}
	}
	
};