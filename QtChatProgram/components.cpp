
#include "components.h"



//获取server对应的socket
SOCKET ComponentClient::GetServerSocket()const {
	return this->sockerToServer;
}

//设置server对应的socket
void ComponentClient::SetServerSocket(SOCKET in_socket) {
	this->sockerToServer = in_socket;
}



