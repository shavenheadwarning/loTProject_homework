
#include "components.h"



//��ȡserver��Ӧ��socket
SOCKET ComponentClient::GetServerSocket()const {
	return this->sockerToServer;
}

//����server��Ӧ��socket
void ComponentClient::SetServerSocket(SOCKET in_socket) {
	this->sockerToServer = in_socket;
}



