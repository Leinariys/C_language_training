#include "threadSendToCarbon.h"


char* carbonIp = NULL;
int carbonPort = -1;
int intervalSendToCarbona = -1, percentiles[5], debug = 0;

void dump_stats()
{
    if (debug)
    {
        {
            printf("Thread[Flush]: Stats dump:");
            statsd_stat_t *s, *tmp;
            HASH_ITER(hh, stats, s, tmp)
            {
                printf("%s.%s: %ld", s->name.group_name, s->name.key_name, s->value);
            }
            if (s) free(s);
            if (tmp) free(tmp);
        }

        {
            printf("Thread[Flush]: Counters dump:");
            statsd_counter_t *c, *tmp;
            HASH_ITER(hh, counters, c, tmp)
            {
                printf("%s: %Lf", c->key, c->value);
            }
            if (c) free(c);
            if (tmp) free(tmp);
        }

        {
            printf("Thread[Flush]: Gauges dump:");
            statsd_gauge_t *g, *tmp;
            HASH_ITER(hh, gauges, g, tmp)
            {
                printf("%s: %Lf", g->key, g->value);
            }
            if (g) free(g);
            if (tmp) free(tmp);
        }
    }
}


int double_sort(const void* a, const void* b)
{
    double _a = *(double*)a;
    double _b = *(double*)b;
    if (_a == _b) return 0;
    return (_a < _b) ? -1 : 1;
}


// функция для
void pThreadSendToCarbon(void* ptr)
{
    printf("Thread[Flush]: Initial Arguments %d\n", *(int*)ptr);

    while (1)
    {
        THREAD_SLEEP(intervalSendToCarbona);

        dump_stats();

        long ts = time(NULL);
        int numStats = 0;
        UT_string* statString;

        utstring_new(statString);

        /* ---------------------------------------------------------------------
          Метрики счетчика процессов
          Counter Metrics: Структура счетчиков проанализирована, значения переведены в
          средние значения за период времени (определяется flush_interval),
          и эти значения отсылаются в Graphite .
          -------------------------------------------------------------------- */
        {
            statsd_counter_t *s_counter, *tmp;
            HASH_ITER(hh, counters, s_counter, tmp)
            {
                long double value = s_counter->value / intervalSendToCarbona;

                utstring_printf(statString, "stats.%s %Lf %ld\nstats_counts_%s %Lf %ld\n", s_counter->key, value,
                                ts, s_counter->key, s_counter->value, ts);


                /* Очистить счетчик после того, как мы с ним закончим. */
                wait_for_counters_lock();
                s_counter->value = 0;
                remove_counters_lock();

                numStats++;
            }
            if (s_counter) free(s_counter);
            if (tmp) free(tmp);
        }

        /* ---------------------------------------------------------------------
          Метрики таймера процесса
          Timer Metrics: Метрики времени это немного сложнее.
          На основе собранных данных рассчитываются несколько статистических
          параметров (среднее, минимальное, максимальное, количество и процентили)
          и данные отправляются в Graphite .
          -------------------------------------------------------------------- */

        {
            statsd_timer_t *s_timer, *tmp;
            HASH_ITER(hh, timers, s_timer, tmp)
            {
                if (s_timer->count > 0)
                {
                    int pctThreshold = percentiles[0]; /* TODO FIXME: support multiple percentiles */

                    /* Sort all values in this timer list */
                    wait_for_timers_lock();
                    utarray_sort(s_timer->values, double_sort);

                    double min = 0;
                    double max = 0;
                    {
                        double* i = NULL;
                        int count = 0;
                        while ((i = (double*)utarray_next(s_timer->values, i)))
                        {
                            if (count == 0)
                            {
                                min = *i;
                                max = *i;
                            }
                            else
                            {
                                if (*i < min) min = *i;
                                if (*i > max) max = *i;
                            }
                            count++;
                        }
                    }

                    double mean = min;
                    double maxAtThreshold = max;

                    if (s_timer->count > 1)
                    {
                        // Найдите индекс порога 90-го процентиля.
                        int thresholdIndex = (pctThreshold / 100.0) * s_timer->count;
                        maxAtThreshold = *(utarray_eltptr(s_timer->values, thresholdIndex - 1));
                        printf("Thread[Flush]: Count = %d Thresh = %d, MaxThreshold = %f\n", s_timer->count,
                               thresholdIndex,
                               maxAtThreshold);

                        double sum = 0;
                        double* i = NULL;
                        int count = 0;
                        while ((i = (double*)utarray_next(s_timer->values, i)) && count < s_timer->count - 1)
                        {
                            sum += *i;
                            count++;
                        }
                        mean = sum / s_timer->count;
                    }

                    /* Clear all values for this timer */
                    utarray_clear(s_timer->values);
                    s_timer->count = 0;
                    remove_timers_lock();


                    utstring_printf(statString, "stats.timers.%s.mean %f %ld\n"
                                    "stats.timers.%s.upper %f %ld\n"
                                    "stats.timers.%s.upper_%d %f %ld\n"
                                    "stats.timers.%s.lower %f %ld\n"
                                    "stats.timers.%s.count %d %ld\n",
                                    s_timer->key, mean, ts,
                                    s_timer->key, max, ts,
                                    s_timer->key, pctThreshold, maxAtThreshold, ts,
                                    s_timer->key, min, ts,
                                    s_timer->key, s_timer->count, ts
                    );
                }
                numStats++;
            }
            if (s_timer) free(s_timer);
            if (tmp) free(tmp);
        }

        /* ---------------------------------------------------------------------
          Показатели датчика процесса
          auge Metrics: Это просто отправляет значение метрики на Graphite.
          -------------------------------------------------------------------- */

        {
            statsd_gauge_t *s_gauge, *tmp;
            HASH_ITER(hh, gauges, s_gauge, tmp)
            {
                long double value = s_gauge->value;

                utstring_printf(statString, "stats.%s %Lf %ld\nstats_gauges_%s %Lf %ld\n", s_gauge->key, value, ts,
                                s_gauge->key, s_gauge->value, ts);

                numStats++;
            }
            if (s_gauge) free(s_gauge);
            if (tmp) free(tmp);
        }

        /* ---------------------------------------------------------------------
          Итоги процесса
          Misc Metrics: Затем функция отправляет метрику, отслеживающую общее
          количество рассчитанных статистических данных.
          -------------------------------------------------------------------- */

        {
            utstring_printf(statString, "statsd.numStats %d %ld\n", numStats, ts);
        }

        /* Отправка в Карбон */

        printf("Thread[Flush]: Messages:\n%s", utstring_body(statString));
        int nova = 0, sock = -1;
        struct sockaddr_in sa;
        memset(&sa, 0, sizeof(struct sockaddr_in));

        if (inet_pton(AF_INET, carbonIp, &sa.sin_addr) <= 0)
        {
            nova = 1;
            printf("Thread[Flush]: inet_pton() ERROR\n");
        }
        if (!nova)
        {
            sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if (sock < 0)
            {
                nova = 1;
                printf("Thread[Flush]: graphite won't work!\n");
            }
        }
        if (!nova)
        {
            sa.sin_family = AF_INET;
            sa.sin_port = htons(carbonPort);
            if (connect(sock, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
            {
                fprintf(stderr, "Thread[Flush]: Connection failed: %d\n", WSAGetLastError());
                pthread_exit(0);
            }
            int status = send(sock, utstring_body(statString), utstring_len(statString), 0);
            if (status == SOCKET_ERROR)
            {
                fprintf(stderr, "Thread[Flush]: send failed: %d\n", WSAGetLastError());
                pthread_exit(0);
            }
            close(sock);
            char flush_time[12] = {};
            sprintf(flush_time, "%ld", time(NULL));
            update_stat("ngfw", "last_send_to_carbon", flush_time);
        }

        utstring_free(statString);
    }

    printf("Thread[Flush]: Ending thread %d\n", (int)*((int*)ptr));
    pthread_exit(0);
}
