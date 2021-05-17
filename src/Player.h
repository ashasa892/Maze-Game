#include "TextureManager.h"

class Player
{
public:
	Player(const char* fileName, SDL_Renderer* renderer, int x, int y);
	~Player();

	void update();
	void render();

	int x() {return xpos;}
	int y() {return ypos;}
	void setx(int x) {xpos = x};
	void sety(int y) {ypos = y};


private:
	int xpos, ypos;

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
		
};