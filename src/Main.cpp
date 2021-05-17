#include "Main.h"



App app;


int main(int argc, char** argv) {

	//init SDL
	if ( !app.getQuit() ) app.init();

	while (!app.getQuit()) {
		app.handleEvents();
		app.update();
		app.render();
	}

	
}