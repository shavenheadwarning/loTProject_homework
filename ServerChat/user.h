#pragma once
#include <winsock2.h>
#include <string>
#include <queue>
#include <map>
class Users
{
public:


	std::map<std::string, SOCKET*>usrMap;
	std::queue<std::string> msgbuffQueue;

	Users()=default;
	~Users()=default;
	std::string GetUserNameList();

private:

};


