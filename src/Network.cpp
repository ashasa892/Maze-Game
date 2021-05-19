#include "Network.h"

Network::Network(const char* ipchar) {
	SDLNet_Init();
	IPaddress ip;
	if (SDLNet_ResolveHost(&ip, ipchar, 1234) == -1) {
		std::cout << "There was an error" << std::endl;
	}
	connection = SDLNet_TCP_Open(&ip);
	if (connection == NULL) {
		std::cout << "Bad IP ;((((((((" << std::endl;
	}
	std::cout << "connection stablished to server ;)" << std::endl;
	server = SDLNet_AllocSocketSet(1);
	SDLNet_TCP_AddSocket(server, connection);
}

Network::~Network() {
	SDLNet_TCP_Send(connection, "2 \n", 4);
	SDLNet_TCP_Close(connection);
	SDLNet_FreeSocketSet(server);
	SDLNet_Quit();
}

void Network::send(PositionComponent* pos) {
	sprintf(tmp, "1 %f %f %d \n", (pos->pos.x), (pos->pos.y), (pos->face_direction));
	int size = 0, len = strlen(tmp)+1;
	while (size < len) {
		size += SDLNet_TCP_Send(connection, tmp+size, len-size);	
	}
}

void Network::recv(PositionComponent* pos) {

	while (SDLNet_CheckSockets(server, 0) > 0 && SDLNet_SocketReady(connection)) {
		int offset = 0;
		do {
			offset += SDLNet_TCP_Recv(connection, tmp+offset, 1400);
			if (offset <= 0) return;
		} while (tmp[strlen(tmp)-1] != '\n');
	}
	int type;
	sscanf(tmp, "%d", &type);
	if (type == 1) {
		sscanf(tmp, "1 %f %f %d \n", &(pos->pos.x), &(pos->pos.y), &(pos->face_direction));
	}
}