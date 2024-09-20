#ifndef STATS_H
#define STATS_H 1
#include <stdio.h>
#include <stdbool.h>
#include <semaphore.h>
#include "../uthash/uthash.h"


typedef struct {
    char group_name[100];
    char key_name[100];
} statsd_stat_name_t;

typedef struct {
    statsd_stat_name_t name;
    long value;
    bool locked;
    UT_hash_handle hh; /* делает эту структуру хешируемой */
} statsd_stat_t;

extern statsd_stat_t *stats;
extern sem_t stats_lock;

void update_stat(char* group, char* key, char* value);


#define UPDATE_LAST_MSG_SEEN() { \
char time_sec[32]; \
sprintf(time_sec, "%ld", time(NULL)); \
update_stat( "messages", "last_msg_seen", time_sec); \
}

#define wait_for_stats_lock() sem_wait(&stats_lock)
#define remove_stats_lock() sem_post(&stats_lock)

#endif // STATS_H
