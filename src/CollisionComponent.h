#pragma once

#include <string>
#include <SDL2/SDL.h>
#include "Components.h"

class CollisionComponent : public Component
{
public:
	SDL_Rect collider;
	std::string tag;

	PositionComponent* pos;

	CollisionComponent(std::string tagName) {
		tag = tagName;
	}

	void init() override {
		collider.w = collider.h = 32;
		if (!entity->hasComponent<PositionComponent>()) {
			entity->addComponent<PositionComponent>();
		}
		pos = entity->getComponent<PositionComponent>();
	}

	void update() override {
		collider.x = pos->pos.x;
		collider.y = pos->pos.y;
	}
	
};