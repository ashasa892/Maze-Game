#pragma once
#include "PositionComponent.h"
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
		position->pos.print();
	}

	void render() override {
		if(visible){
			TextureManager::render(texture, srcRect, destRect);
		}
	}

};
