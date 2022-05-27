//#pragma once
#ifndef __SERVER_H
#define __SERVER_H

#include <winsock2.h>
#include <ws2tcpip.h>

#include "user.h"

#define DEFAULT_PORT "27015"

#define MAX_CONNETCTIONS 5

void ServerInit();
void AcceptFromClient(Users*);



#endif // __SERVER_H

