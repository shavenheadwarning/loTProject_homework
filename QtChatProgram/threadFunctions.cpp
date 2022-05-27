
#include <stdio.h>


//
#include "threadFunction.h"
#include "client.h"
#include "components.h"
#include "utils.h"

//
#include <QDebug>
#include "ClientUI.h"



////thread function for receiving message from server
DWORD WINAPI RecvMessageFromServer(LPVOID lpParameter) {
	RecvThreadData* pThreadData = (RecvThreadData*)lpParameter;
	char recvbuf[1000] = { 0 };
	//while:always receive message
	while (1) {
		ZeroMemory(recvbuf, 1000);
		int iResult = recv((pThreadData->recvSockt), recvbuf, 1000, 0);
		if (iResult > 0) {

			//如果是聊天内容，则用信号通知更新聊天框
			if (recvbuf[0] == msgContent) {
				(pThreadData->msgQueuePtr)->enqueue(QString(recvbuf));
				emit pThreadData->window->updateBrowser();
				//qDebug() << QString("finish");
			}
			//如果是在线的用户名单，则更新用户列表
			else if(recvbuf[0] == msgUserlist) {
				emit pThreadData->window->updateOnlineUserlistView(QString(recvbuf));
			}

				
			//}
			
			 //更新msg queue
		}
		 //更新msg queue


		//printf("%s\n", recvbuf);
	}
	return 0L;
}







