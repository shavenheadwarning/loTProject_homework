

//usr include
#include "client.h"

#define _CRT_SECURE_NO_WARNINGS


#include <stdlib.h>
#include <stdio.h>

//connect to server
SOCKET ConnectToServer() {
	struct addrinfo* result = NULL, 
        * ptr=NULL,
        hints;

    int iResult;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;


    iResult = getaddrinfo(SERVER_IP, SERVER_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return INVALID_SOCKET;
    }

    SOCKET connectSocket = INVALID_SOCKET;
    // Attempt to connect to an address until one succeeds
    int trycount = 0;
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        if (trycount++ > 10)break;
        // Create a SOCKET for connecting to server
        connectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (connectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return connectSocket;
        }

        // Connect to server.
        iResult = connect(connectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(connectSocket);
            connectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }


    return connectSocket;
}