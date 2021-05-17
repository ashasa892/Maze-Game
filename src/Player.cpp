#include "Player.h"

Player::Player(const char* fileName, SDL_Renderer* renderer, int x, int y) {
	texture = TextureManager::loadTexture(fileName, renderer);
	xpos = x;
	ypos = y;

	srcRect.x = 0, srcRect = 0;
	srcRect.h = srcRect.w = 32;
	destRect.h = destRect.w = 64;
}

void Player::update() {
	destRect.x = x, destRect.y = y;
}

void Player::render() {
	TextureManager::render()
}

