#include "threadListen.h"



/// Самописная серверная консоль для принятия метрик
/// @param ptr
void pThreadListen(void* arg)
{
    printf("Thread[Listen]: Initial arguments %d\n", *(int*)arg);


    doListener();

    /* end mgmt listener */
    printf("Thread[Listen]: Ending thread %d\n", *(int*)arg);
    pthread_exit(0);
}
