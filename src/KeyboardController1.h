#pragma once 

#include "App.h"


class KeyboardController1 : public Component
{
public:
	PositionComponent *pos;

	void init() override {
		pos = entity->getComponent<PositionComponent>();
	}

	void update() override {
		if (App::event.type == SDL_KEYDOWN) {
			switch (App::event.key.keysym.sym) {
				case SDLK_UP:
					pos->velocity.y = -1;
					break;
				case SDLK_DOWN:
					pos->velocity.y = 1;
					break;
				case SDLK_LEFT:
					pos->velocity.x = -1;
					break;
				case SDLK_RIGHT:
					pos->velocity.x = 1;
					break;
				default:
					break;
			}
		}

		if (App::event.type == SDL_KEYUP) {
			switch (App::event.key.keysym.sym) {
				case SDLK_UP:
					pos->velocity.y = 0;
					break;
				case SDLK_DOWN:
					pos->velocity.y = 0;
					break;
				case SDLK_LEFT:
					pos->velocity.x = 0;
					break;
				case SDLK_RIGHT:
					pos->velocity.x = 0;
					break;
				default:
					break;
			}
		}
	}
	
};