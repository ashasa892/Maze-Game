#pragma once
#include <SDL2/SDL.h>
#include <SDL_net.h>
#include <iostream>
#include <vector>
#include <cstring>


class Network
{
private:
	SDLNet_SocketSet server;
	TCPsocket connection;
	char tmp[1400];
public:
	Network(const char* ip);
	~Network();

	void send(int xpos, int ypos, int fired);
	void recv();
		
};