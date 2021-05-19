#include "Main.h"
#include "Network.h"


App app;


int main(int argc, char** argv) {

	//init SDL
	if ( !app.getQuit() ) app.init();

	Network net("127.0.0.1");


	while (!app.getQuit()) {
		app.handleEvents();
		app.update();
		app.render();
	}


	
}