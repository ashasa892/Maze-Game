#include <SDL2/SDL.h>
#include <SDL_net.h>
#include <iostream>
#include <vector>
#include <cstring>


struct data
{
	TCPsocket socket;
	Uint32 timeout;
	int id;
	data(TCPsocket sock, Uint32 t, int i) : socket(sock), timeout(t), id(i) {}
};


int main(int argc, char** argv) {

	SDL_Init(SDL_INIT_EVERYTHING);
	SDLNet_Init();

	int curid = 0;
	int playernum = 0;

	SDL_Event event;
	IPaddress ip;
	SDLNet_ResolveHost(&ip, NULL, 1234);
	std::vector<data> socketvector;
	char tmp[1400];
	
	bool running = true;
	SDLNet_SocketSet sockets = SDLNet_AllocSocketSet(2);
	TCPsocket server = SDLNet_TCP_Open(&ip);

	if (!server) {
		std::cout << "Error in creating server" << std::endl;

	}

	SDL_CreateWindow("server", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        SDL_WINDOW_SHOWN);
	
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)) {
				running = false;
			}	
		}
		
		


		TCPsocket tmpsocket = SDLNet_TCP_Accept(server);
		
			
		
		if (tmpsocket) {
			
			if (playernum < 2) {
				SDLNet_TCP_AddSocket(sockets, tmpsocket);
				socketvector.push_back(data(tmpsocket, SDL_GetTicks(), curid));
				sprintf(tmp, "0 %d \n", curid);	
				std::cout << "New Connection:  " << curid << "\n";
				curid++;
				playernum++;
			}
			else {
				sprintf(tmp, "4 \n");
				printf("cannot connect to more clients\n");
			}
			SDLNet_TCP_Send(tmpsocket, tmp, strlen(tmp)+1);
			
			if (curid == 2) {
				printf("haha\n");
				sprintf(tmp, "3 \n");
				SDLNet_TCP_Send(socketvector[0].socket, tmp, strlen(tmp)+1);
				curid = -1;
			}
		}
		

		// check for incoming data

		while (SDLNet_CheckSockets(sockets, 0) > 0) {
			for (int i=0; i<socketvector.size(); i++) {
				if (SDLNet_SocketReady(socketvector[i].socket))
				{
					socketvector[i].timeout = SDL_GetTicks();
					SDLNet_TCP_Recv(socketvector[i].socket, tmp, 1400);
					// printf("server received %s \n", tmp);
					int num = tmp[0]-'0', j=1;
					while (tmp[j] >= '0' && tmp[j] <= '9') {
						num *= 10;
						num += tmp[j] - '0';
						j++;
					}
					printf(tmp);
					if (num == 1) {
						for (int k=0; k<socketvector.size(); k++)
						{
							if (k==i) continue;
							SDLNet_TCP_Send(socketvector[k].socket, tmp, strlen(tmp)+1);
						}
					} 
					else if (num == 2) {
						for (int k=0; k<socketvector.size(); k++)
						{
							if (k==i) continue;
							SDLNet_TCP_Send(socketvector[k].socket, tmp, strlen(tmp)+1);
						}
						SDLNet_TCP_DelSocket(sockets, socketvector[i].socket);
						SDLNet_TCP_Close(socketvector[i].socket);
						socketvector.erase(socketvector.begin()+i);
						// playernum--;
					}
				}
			}
		}

		// disconnect, timeout
		for (int i=0; i<socketvector.size(); i++) {
			if (SDL_GetTicks() - socketvector[i].timeout > 5000) {
				sprintf(tmp, "2 %d", i);
				for (int j=0; j<socketvector.size(); j++) {
					if (j==i) continue;
					SDLNet_TCP_Send(socketvector[j].socket, tmp, strlen(tmp)+1);
				}
				SDLNet_TCP_DelSocket(sockets, socketvector[i].socket);
				SDLNet_TCP_Close(socketvector[i].socket);
				socketvector.erase(socketvector.begin()+i);
				playernum--;
			}
		}

	}

	for (int i=0; i<socketvector.size(); i++) {
		SDLNet_TCP_Close(socketvector[i].socket);
	}

	SDLNet_FreeSocketSet(sockets);
	SDLNet_TCP_Close(server);
	SDLNet_Quit();
	SDL_Quit();


}