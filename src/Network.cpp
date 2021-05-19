#include "Network.h"

Network::Network(const char* ip) {
	SDLNet_Init();
	IPaddress ip;
	if (SDLNet_ResolveHost(&ip, ipchar, 1234) == -1) {
		std::cout << "There was an error" << std::endl;
	}
	connection = SDLNet_TCP_Open(&ip);
	if (connection == NULL) {
		std::cout << "Bad IP ;((((((((" << std::endl;
	}
	server = SDLNet_AllocSocketSet(1);
	SDLNet_TCP_AddSocket(server, connection);
}

Network::~Network() {
	SDLNet_TCP_Send(connection, "2 \n", 4);
	SDLNet_TCP_Close();
	SDLNet_FreeSocketSet(server);
	SDLNet_Quit();
}

void Network::send(int xpos, int ypos, int fired) {
	sprintf(tmp, "1 %d %d %d \n", xpos, ypos, fired);
	int size = 0, len = strlen(tmp)+1;
	while (size < len) {
		size += SDLNet_TCP_Send(connection, tmp+size, len-size);	
	}
}