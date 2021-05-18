#include "TextureManager.h"

SDL_Renderer* TextureManager::renderer = NULL;

SDL_Texture* TextureManager::loadTexture(const char* fileName) {
	SDL_Surface* tempSurface = IMG_Load(fileName);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}

void TextureManager::render(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect srcDest) {
	SDL_RenderCopy(renderer, texture, &srcRect, &srcDest);
}
