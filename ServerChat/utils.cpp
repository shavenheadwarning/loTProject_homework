
/*
* 
* 一些功能函数的实现
*/


#define    WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <iostream>
#include "utils.h"
#include <sstream>
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

//以','分割字符串
std::vector<std::string> SplitMsg(const std::string msg) {
	std::stringstream input(msg);
	std::string temp;
	std::vector<std::string> result;
	while (std::getline(input,temp,','))
	{
		result.push_back(temp);
	}
	return result;

}