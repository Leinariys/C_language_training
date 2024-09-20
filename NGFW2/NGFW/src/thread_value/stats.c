#include "stats.h"





/**
 * Запишите или обновите значение статистики.
 */
void update_stat(char* group, char* key, char* value)
{
    printf("update_stat ( %s, %s, %s )\n", group, key, value);
    statsd_stat_t* s;
    statsd_stat_name_t l;

    memset(&l, 0, sizeof(statsd_stat_name_t));
    strcpy(l.group_name, group);
    strcpy(l.key_name, key);
    printf("HASH_FIND '%s' '%s'\n", l.group_name, l.key_name);
    HASH_FIND(hh, stats, &l, sizeof(statsd_stat_name_t), s);

    if (s)
    {
        printf("Updating an old statistics record\n");
        wait_for_stats_lock();
        s->value = atol(value);
        remove_stats_lock();
    }
    else
    {
        printf("Adding a new statistics entry\n");
        s = malloc(sizeof(statsd_stat_t));
        memset(s, 0, sizeof(statsd_stat_t));

        strcpy(s->name.group_name, group);
        strcpy(s->name.key_name, key);
        s->value = atol(value);
        s->locked = 0;

        wait_for_stats_lock();
        HASH_ADD(hh, stats, name, sizeof(statsd_stat_name_t), s);
        remove_stats_lock();
    }
}


