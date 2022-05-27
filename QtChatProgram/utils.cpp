#define    WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <iostream>
#include "utils.h"
#pragma comment (lib, "Ws2_32.lib")


// Initialize Winsock
void InitializeWinsock() {
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		std::cerr << "WSAStartup failed with error:" << iResult << std::endl;
		return;
	}

}



