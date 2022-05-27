#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>

// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable : 4996)

int main()
{

    int iResult;
    WSADATA wsaData;

    SOCKET SendSocket = INVALID_SOCKET;
    sockaddr_in RecvAddr;

    unsigned short Port = 2705;

    char SendBuf[1024] = { 0 };
    int BufLen = 1024;

    //----------------------
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    //---------------------------------------------
    // Create a socket for sending data
    SendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (SendSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    RecvAddr.sin_family = AF_INET;
    RecvAddr.sin_port = htons(Port);
    RecvAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //printf("%d\n", RecvAddr.sin_port);
    //---------------------------------------------
    // Send a datagram to the receiver
    printf("input a message ...\n");
    scanf("%s", SendBuf);
    iResult = sendto(SendSocket,
        SendBuf, BufLen, 0, (SOCKADDR*)&RecvAddr, sizeof(RecvAddr));
    if (iResult == SOCKET_ERROR) {
        printf("sendto failed with error: %d\n", WSAGetLastError());
        closesocket(SendSocket);
        WSACleanup();
        return 1;
    }
    //printf("%d\n", RecvAddr.sin_addr.S_un.S_addr);
    //printf("%d\n", RecvAddr.sin_port);
    //printf("%d\n", SendSocket);

    sockaddr_in ServerAddr;
    int SenderAddrSize = sizeof(ServerAddr);
    ZeroMemory(SendBuf, 1024);
    iResult=recvfrom(SendSocket, SendBuf, BufLen,0, (SOCKADDR*)&ServerAddr,&SenderAddrSize);
    if (iResult == SOCKET_ERROR) {
        printf("receive failed with error: %d\n", WSAGetLastError());
        closesocket(SendSocket);
        WSACleanup();
        return 1;
    }
    printf("back from server:%s\n", SendBuf);

    //---------------------------------------------
    // When the application is finished sending, close the socket.
    //printf("Finished sending. Closing socket.\n");
    iResult = closesocket(SendSocket);
    if (iResult == SOCKET_ERROR) {
        printf("closesocket failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    //---------------------------------------------
    // Clean up and quit.
    printf("Exiting.\n");
    WSACleanup();
    return 0;
}