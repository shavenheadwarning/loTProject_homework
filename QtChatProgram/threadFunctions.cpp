
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

			//������������ݣ������ź�֪ͨ���������
			if (recvbuf[0] == msgContent) {
				(pThreadData->msgQueuePtr)->enqueue(QString(recvbuf));
				emit pThreadData->window->updateBrowser();
				//qDebug() << QString("finish");
			}
			//��������ߵ��û�������������û��б�
			else if(recvbuf[0] == msgUserlist) {
				emit pThreadData->window->updateOnlineUserlistView(QString(recvbuf));
			}

				
			//}
			
			 //����msg queue
		}
		 //����msg queue


		//printf("%s\n", recvbuf);
	}
	return 0L;
}







