#ifndef THREADSENDTOCARBON_H
#define THREADSENDTOCARBON_H 1

#include <stdio.h>
#include <winsock2.h>
#include <pthread.h>
#include <io.h>
#include <unistd.h>
#include <ws2tcpip.h>
#include <sys/time.h>

#include "../thread_value/counters.h"
#include "../thread_value/gauges.h"
#include "../thread_value/stats.h"
#include "../thread_value/timers.h"

#include "../uthash/utstring.h"


#define THREAD_SLEEP(x){        \
pthread_mutex_t fakeMutex = PTHREAD_MUTEX_INITIALIZER;  \
pthread_cond_t fakeCond = PTHREAD_COND_INITIALIZER; \
struct timespec timeToWait; \
struct timeval now; \
int rt; \
gettimeofday(&now,NULL);    \
timeToWait.tv_sec = now.tv_sec + x; \
timeToWait.tv_nsec = now.tv_usec;   \
pthread_mutex_lock(&fakeMutex); \
rt = pthread_cond_timedwait(&fakeCond, &fakeMutex, &timeToWait);    \
if (rt != 0) { } pthread_mutex_unlock(&fakeMutex);  \
}


void pThreadSendToCarbon(void* ptr);


#endif // THREADSENDTOCARBON_H
