
/*
线程函数的声明
*/


#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

DWORD WINAPI RecvMessageToServer(LPVOID lpParameter);
DWORD WINAPI SendMessageToClient(LPVOID lpParameter);


