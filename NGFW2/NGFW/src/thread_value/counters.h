#ifndef __COUNTERS_H__
#define __COUNTERS_H__ 1

#include <semaphore.h>

#include "../uthash/uthash.h"


typedef struct {
    char key[100];
    long double value;
    UT_hash_handle hh; /* делает эту структуру хешируемой */
} statsd_counter_t;

extern statsd_counter_t *counters;
extern sem_t counters_lock;

#define wait_for_counters_lock() sem_wait(&counters_lock)
#define remove_counters_lock() sem_post(&counters_lock)

#endif /* __COUNTERS_H__ */


