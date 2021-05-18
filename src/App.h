#pragma once
#include <iostream>
#include <SDL2/SDL.h>







#define GAME_NAME "Luffy vs Kaido" 
#define SCREEN_WIDTH 640 // height of the game window  (change in Map.h)
#define SCREEN_HEIGHT 480  // width of the game window

class App 
{
public:
	App();
	~App();

	void init(); //init sdl and window
	void handleEvents();
	void update();
	void render();

	static SDL_Event event;
    inline bool getQuit() const { return quit; }
    void setQuit( bool q ) { quit = q; }

private:
	
	bool quit;
	SDL_Window* window;
	SDL_Renderer* renderer;
	
	
	
	


};