#ifndef __GAUGES_H__
#define __GAUGES_H__ 1

#include <semaphore.h>
#include "../uthash/uthash.h"

typedef struct {
    char key[100];
    long double value;
    UT_hash_handle hh; /* делает эту структуру хешируемой */
} statsd_gauge_t;

extern statsd_gauge_t *gauges;
extern sem_t gauges_lock;

#define wait_for_gauges_lock() sem_wait(&gauges_lock)
#define remove_gauges_lock() sem_post(&gauges_lock)

#endif /* __GAUGES_H__ */
