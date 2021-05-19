#pragma once
#include "CollisionComponent.h"
#include "TextureManager.h"
#include <SDL2/SDL.h>

class Target : public Component {
private:
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

public:
	PositionComponent *pos;
	bool active = true;
	Target(const char* fileName) {
		texture = TextureManager::loadTexture(fileName);
	}

	void init() override {
		pos = (entity->getComponent<PositionComponent>());
		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;
		destRect.w = destRect.h = 32;
	}

	void update() override {
		destRect.x = pos->pos.x;
		destRect.y = pos->pos.y;
	}

	void render() override {
		if(active){
			TextureManager::render(texture, srcRect, destRect);
		}
	}

};
