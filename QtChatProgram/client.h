#pragma once
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT "27015"

SOCKET ConnectToServer();

