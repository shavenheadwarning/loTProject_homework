
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

	//��ʼ��socket
	InitializeWinsock();
	ServerInit();
	Users serverUsersMap;
	
	//�������ڷ�����Ϣ���߳�
	HANDLE sendmsghandle = CreateThread(NULL, 1024, SendMessageToClient, &serverUsersMap, 0, NULL);

	//�ȴ�����
	AcceptFromClient(&serverUsersMap);

	while (1) {
		Sleep(100);
	}

	return 0;
}