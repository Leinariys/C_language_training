#ifndef THREADSEND_H
#define THREADSEND_H 1

#include <stdio.h>
#include <winsock2.h>
#include <pthread.h>
#include <io.h>
#include <ws2tcpip.h>


#include "../service/SocketTcpSender.h"


void pThreadMgmtSend(void* ptr);
#endif // THREADSEND_H
