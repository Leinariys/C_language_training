

#include "threadSend.h"



void pThreadMgmtSend(void* ptr)
{
    printf("Thread[Send]: Initial arguments %d\n", *(int*)ptr);

    loopProcessAndSendMessages();
}
