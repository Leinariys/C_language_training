#ifndef THREADLISTEN_H
#define THREADLISTEN_H 1
#include <stdio.h>
#include <winsock2.h>
#include <pthread.h>
#include <io.h>
#include <ws2tcpip.h>

#include "../service/SocketTcpListener.h"

void pThreadListen(void* ptr);
#endif // THREADLISTEN_H
