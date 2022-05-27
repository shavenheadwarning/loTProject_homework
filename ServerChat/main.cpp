
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

	//≥ı ºªØsocket
	InitializeWinsock();
	ServerInit();
	Users serverUsersMap;
	
	HANDLE sendmsghandle = CreateThread(NULL, 1024, SendMessageToClient, &serverUsersMap, 0, NULL);

	//function test
	AcceptFromClient(&serverUsersMap);

	printf("initiate finish\n");
	while (1) {
		Sleep(100);
	}

	return 0;
}