#pragma once
#ifndef __UTILS_H
#define __UTILS_H

#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>



#include "user.h"

#define msgUserlist '0'
#define msgContent '1'
#define msgGetUserService '2'
#define msgClientUserName '3'

struct RecvMsgThreadData
{

	Users* userMapPtr;
	SOCKET* clientsocket;
	
};




void InitializeWinsock();
std::vector<std::string> SplitMsg(const std::string);


//all msg  form client should be preprocessed by this function
//std::string msgfromClientPreprocess(const char* content);


#endif
