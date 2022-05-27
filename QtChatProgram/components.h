#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !1




#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <queue>
#include <qqueue.h>
#include <QtWidgets/QMainWindow>
#include <qstandarditemmodel.h>
#include <string>
#include <set>


//


typedef struct UpdateUsrListData {
	SOCKET	recvSockt;
};


class ComponentClient
{
public:
	
	QQueue<QString> msgQueue;
	std::set<std::string> usrnameSet;
	
	std::string clientUserName;
	SOCKET sockerToServer;

	ComponentClient()=default;
	~ComponentClient()= default;
	SOCKET GetServerSocket()const;
	void SetServerSocket(SOCKET);
	
};

