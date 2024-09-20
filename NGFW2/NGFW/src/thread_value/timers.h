#ifndef __TIMER_H__
#define __TIMER_H__ 1

#include <semaphore.h>

#include "../uthash/uthash.h"
#include "../uthash/utarray.h"



typedef struct {
    UT_hash_handle hh; /* делает эту структуру хешируемой */
    char key[100];
    int count;
    UT_array *values;
} statsd_timer_t;

extern statsd_timer_t *timers;
extern sem_t timers_lock;

#define wait_for_timers_lock() sem_wait(&timers_lock)
#define remove_timers_lock() sem_post(&timers_lock)

#endif /* __TIMER_H__ */

