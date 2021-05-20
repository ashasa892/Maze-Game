#pragma once
#include "CollisionComponent.h"
#include "TextureManager.h"
#include <SDL2/SDL.h>

class Fireball : public Component {
private:
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

public:
	Entity *ent;
	PositionComponent *position;
	PositionComponent *parent_pos;
	CollisionComponent *collide;
	bool visible = false;
	Fireball(const char* fileName, Entity* entity) {
		texture = TextureManager::loadTexture(fileName);
		ent = entity;
	}

	void init() override {
		parent_pos = (entity->getComponent<PositionComponent>());
		position = &(ent->addComponent<PositionComponent>(parent_pos->pos.x, parent_pos->pos.y));
		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;
		destRect.w = destRect.h = 32;
	}

	void update() override {
		destRect.x = position->pos.x;
		destRect.y = position->pos.y;
		if (parent_pos->entity->getComponent<PlayerComponent>()->fired) {
			Fireball *fire = this;
			parent_pos->entity->getComponent<PlayerComponent>()->fireballs--;
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
			parent_pos->entity->getComponent<PlayerComponent>()->fired = false;
		}
	}

	void render() override {
		if(visible){
			TextureManager::render(texture, srcRect, destRect);
		}
	}

};
