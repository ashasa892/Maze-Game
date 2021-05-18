#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TextureManager
{
public:
	TextureManager(SDL_Renderer* ren) {
		renderer = ren;
	}
	static SDL_Renderer* renderer ;
	static SDL_Texture* loadTexture(const char* fileName);
	static void render(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect srcDest);

private:
	
	
};

