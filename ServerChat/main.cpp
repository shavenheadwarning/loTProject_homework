
#define WIN32_LEAN_AND_MEAN

//
#include <windows.h>
#include <stdio.h>

//usr include
#include "utils.h"
#include "server.h"
#include "user.h"
#include "threadFunctions.h"

int main() {

	//初始化socket
	InitializeWinsock();
	ServerInit();
	Users serverUsersMap;
	
	//创建用于发送消息的线程
	HANDLE sendmsghandle = CreateThread(NULL, 1024, SendMessageToClient, &serverUsersMap, 0, NULL);

	//等待连接
	AcceptFromClient(&serverUsersMap);

	while (1) {
		Sleep(100);
	}

	return 0;
}