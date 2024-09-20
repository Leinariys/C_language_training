
#include "SocketTcpSender.h"

char* outputIp = NULL;
int outputPort = -1;

extern UT_array* socketDataQueue;
extern sem_t socketDataQueueLock;




///Достаёт сообщение из очереди и отправляет на обработку и дальнейшую отправку
void loopProcessAndSendMessages(void)
{



    for (;;)
    {
        if (NULL == socketDataQueue)
            continue;

        sem_wait(&socketDataQueueLock);
        struct SocketData* p;
        for (p = utarray_front(socketDataQueue);
             p != NULL;
             p = utarray_next(socketDataQueue, p))
        {
            printf("Thread[Send]: socket: %d size: %lu data: '%.*s'\n", p->socketC, p->size, p->size, p->data);

            printf("Thread[Send]: Address of var p: %p\n", (void*)p);

            //messageProcessing(p->socketC, p->size, p->data);
            printf("Thread[Send]: 111 \n");
            free(p->data);
            printf("Thread[Send]: 222 \n");
            free(p);
            printf("Thread[Send]: 333 \n");
        }

        //Если не нулл то чистим список
        if (socketDataQueue->i)
        {
            printf("Thread[Send]: i %d n %d\n", socketDataQueue->i, socketDataQueue->n);
            utarray_clear(socketDataQueue);
        }

        sem_post(&socketDataQueueLock);
    }
}










