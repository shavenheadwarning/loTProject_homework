#pragma once

#include <string>
#include <queue>
#include <string>
#include <set>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <qqueue.h>


#include "ClientUI.h"

#define msgUserlist '0'
#define msgContent '1'
#define msgGetUserService '2'
#define msgClientUserName '3'


//
typedef struct RecvThreadData {
	SOCKET	recvSockt;
	QQueue<QString>* msgQueuePtr;
	std::set<std::string>* usrlistSet;
	ClientUI* window;
};

void InitializeWinsock();

