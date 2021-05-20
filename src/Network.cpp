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

void Network::send(Entity* player) {
	PositionComponent* pos = player->getComponent<PositionComponent>();
	sprintf(tmp, "1 %f %f %d %d \n", (pos->pos.x), (pos->pos.y), (pos->face_direction), player->getComponent<PlayerComponent>()->fired);
	
	printf("in Network send %s", tmp);
	int size = SDLNet_TCP_Send(connection, tmp, strlen(tmp)+1);
	printf("size %d\n", size);	
	// int size = 0, len = strlen(tmp)+1;
	// while (size < len) {
	// 	size += 
	// 	
	// 	if (size <= 0) break;
	// }
	
	
	// printf("sent %s\n", tmp);

}

void Network::recv(Entity* player) {

	while (SDLNet_CheckSockets(server, 0) > 0 && SDLNet_SocketReady(connection)) {
		int offset = 0;
		SDLNet_TCP_Recv(connection, tmp, 1400);
		// do {
		// 	offset += SDLNet_TCP_Recv(connection, tmp+offset, 1400);
		// 	if (offset <= 0) return;
		// } while (tmp[strlen(tmp)-1] != '\n');
	}
	// if (tmp[0] == '\0') return;
	int type, id;
	sscanf(tmp, "%d", &type);
	printf(tmp);
	if (type == 0) {
		sscanf(tmp, "0 %d \n", &id);
		player->getComponent<PlayerComponent>()->id = id;
		if (id==1) {
			player->getComponent<PlayerComponent>()->isOpponentOnline = true;
		}
	}
	else if (type == 1) {
		PositionComponent* pos = player->getComponent<PositionComponent>();
		sscanf(tmp, "1 %f %f %d %d \n", &(pos->pos.x), &(pos->pos.y), &(pos->face_direction), &(player->getComponent<PlayerComponent>()->fired));
	}
	else if (type == 3) {
		printf("3 came\n");
		player->getComponent<PlayerComponent>()->isOpponentOnline = true;
	}
	tmp[0] = '\0';
	// printf("received %s\n", tmp);
}