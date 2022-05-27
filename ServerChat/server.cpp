


#define WIN32_LEAN_AND_MEAN

//
#include <windows.h>

#include <stdlib.h>
#include <stdio.h>
#include <vector>

//usr include
#include "server.h"
#include "utils.h"
#include "threadFunctions.h"



//全局变量，让thread共同读取
SOCKET listenSocket= INVALID_SOCKET;

//create socket,bind to port and listen
void ServerInit() {
	struct addrinfo* result = NULL;
	struct addrinfo hints;
    int iResult;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        //printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return ;
    }

    // Create a SOCKET for connecting to server
    
    listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (listenSocket == INVALID_SOCKET) {
        //printf("socket failed with error: %ld\n", WSAGetLastError());
        //freeaddrinfo(result);
        WSACleanup();
        return;
    }

    iResult = bind(listenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
            
        //freeaddrinfo(result);
        //closesocket(listenSocket);
        WSACleanup();
        return;
    }
        

    //staring listening
    iResult = listen(listenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return;
    }
    
    freeaddrinfo(result);
    return;
    
}


//accept client function for thread to call
//parameter：
//          usrsPtr：指向Users的指针，用于修改Users的内容
void AcceptFromClient(Users* usrsPtr) {

    //check if listenSocket is successfully initiate
    if (listenSocket == INVALID_SOCKET) {
        printf("listenSocket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return;
    }

    //always waitting for client to connect
    while (1) {


        SOCKET* clientSocket = (SOCKET*)malloc(sizeof(SOCKET));
        *clientSocket=accept(listenSocket, NULL, NULL);
        if (*clientSocket == INVALID_SOCKET) {
            printf("accept failed with error: %d\n", WSAGetLastError());
            WSACleanup();
            return ;
        }
        else {
            
            printf("accept connection\n");
            char tempbuff [10] = { 0 };
            recv(*clientSocket, tempbuff, 10, 0);

            usrsPtr->usrMap.emplace(std::string(tempbuff+1),clientSocket);
            
        }

        //if client connected,create a thread for receiving
        auto recvTData = new RecvMsgThreadData;
        recvTData->clientsocket = clientSocket;
        recvTData->userMapPtr = usrsPtr;
        HANDLE hThread1 = CreateThread(NULL, 1024, RecvMessageToServer, recvTData, 0, NULL);
        if (hThread1 == NULL) {
            printf("thread failed with error: %ld\n", WSAGetLastError());
        }
    }
}

