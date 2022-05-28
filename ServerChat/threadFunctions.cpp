

/*
线程函数的实现
*/


#include <stdio.h>
#include <queue>
#include <string>
#include <vector>
#include <exception>

// usr include 
#include "threadFunctions.h"
#include "server.h"
#include "utils.h"
#include "user.h"


//thread function for receiving message from client
DWORD WINAPI RecvMessageToServer(LPVOID lpParameter) {
	RecvMsgThreadData* pThreadData = (RecvMsgThreadData*)lpParameter;
	printf("receiving \n");
	char recvbuf[1000] = { 0 };

	//while:always receive message
	while (1) {
		ZeroMemory(recvbuf, 1000);
		auto cs = *pThreadData->clientsocket;
		int iResult = recv(*pThreadData->clientsocket, recvbuf, 1000, 0);
		if (iResult > 0) {
			printf("from socket %d:  %s\n", *pThreadData->clientsocket, recvbuf);
			pThreadData->userMapPtr->msgbuffQueue.push(std::string(recvbuf));


		}
		Sleep(10);

	}

	return 0L;
}

//thread function for sending message to client
DWORD WINAPI SendMessageToClient(LPVOID lpParameter) {
	Users* pThreadData = (Users*)lpParameter;

	auto localmsgQueuePtr = &pThreadData->msgbuffQueue;
	auto localusrMapPtr = &pThreadData->usrMap;
	while (1) {
		
		if (localmsgQueuePtr->size() == 0)continue;
		if (localusrMapPtr->size() == 0)continue;
		
		auto msgStr= localmsgQueuePtr->front();
		auto msgtype = msgStr[0];
		printf("receive buffer is %s\n", msgStr.c_str());

		//根据约定好的消息类型处理接受到的信息
		if (msgtype == msgClientUserName) {
			continue;
		}
		else if (msgtype == msgGetUserService) {
			std::string sendStr=pThreadData->GetUserNameList();

			auto targetsocket = pThreadData->usrMap[msgStr.substr(2)];
			printf("name list: %s\n", sendStr.c_str());
			send(*targetsocket, sendStr.c_str(),sendStr.size(),0);
		}
		else if (msgtype == msgContent) {
			auto msgSplitResult = SplitMsg(msgStr);
			auto targetName = msgSplitResult[2];
			auto targetsocket = pThreadData->usrMap[msgSplitResult[1]];
			auto sendMsg = "1," + targetName + "," + msgSplitResult[3];
			printf("going to send %s\n", sendMsg.c_str());
			send(*targetsocket, sendMsg.c_str(), sendMsg.size(), 0);

		}
		localmsgQueuePtr->pop();
		
		
		Sleep(10);
	}

	return 0L;
	
}