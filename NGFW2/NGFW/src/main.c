#include "main.h"


pthread_t threadListen;
pthread_t threadSend;
pthread_t threadSendToCarbon;

statsd_stat_t* stats = NULL;
sem_t stats_lock;
statsd_counter_t* counters = NULL;
sem_t counters_lock;
statsd_gauge_t* gauges = NULL;
sem_t gauges_lock;
statsd_timer_t* timers = NULL;
sem_t timers_lock;

extern sem_t socketDataQueueLock;

//threadSendToCarbon.c
extern int intervalSendToCarbona, percentiles[5];
int numPercentiles = 0;

extern char* inputIp;
extern int inputPort;
extern char* outputIp;
extern int outputPort;
extern char* carbonIp;
extern int carbonPort;

void syntax(char* argv[])
{
    fprintf(stderr, "NGFW version %s\n", NGFW_VERSION);
    fprintf(stderr,
            "Usage: %s [-hT] [-I host] [-i port] [-O host] [-o port] [-C host] [-c port]\n",
            argv[0]);
    fprintf(stderr, "\t-I ipv4           прослушивание IP-адрес (обязателеный)\n");
    fprintf(stderr, "\t-i port           прослушивание порт, TCP (обязателеный)\n");
    fprintf(stderr, "\t-O ipv4           отправка IP-адрес (обязателеный)\n");
    fprintf(stderr, "\t-o port           отправка порт, TCP (обязателеный)\n");
    fprintf(stderr, "\t-C ipv4           карбоновый IP-адрес (обязателеный)\n");
    fprintf(stderr, "\t-c port           карбоновый порт (обычно 2003), TCP (обязателеный)\n");
    fprintf(stderr, "\t-h                этот справочный экран\n");
    fprintf(stderr, "\t-T                пороговые значения процентилей, csv (по умолчанию 90)\n");
    exit(1);
}

void cleanup()
{
    //Сигнал на остановку потоков
    pthread_cancel(threadListen);
    pthread_cancel(threadSend);
    pthread_cancel(threadSendToCarbon);

    sem_destroy(&stats_lock);
    sem_destroy(&timers_lock);
    sem_destroy(&counters_lock);
    sem_destroy(&gauges_lock);
    sem_destroy(&socketDataQueueLock);

    printf("Thread[Main]: Stop NGFW\n");
}

void signal_handler(int signal_number)
{
    printf("Thread[Main]: Received OS signal: %d\n", signal_number);
    cleanup();
    exit(EXIT_FAILURE);
}


void readArguments(int argc, char* argv[])
{
    int opt = 0;
    char *p_raw, *pch;
    while ((opt = getopt(argc, argv, "hI:i:O:o:C:c:T:F:")) != -1)
    {
        switch (opt)
        {
        case 'I':
            inputIp = strdup(optarg);
            printf("Thread[Main]: Ip inputIp %s\n", inputIp);
            break;
        case 'i':
            inputPort = atoi(optarg);
            printf("Thread[Main]: Port of inputPort %d\n", inputPort);
            break;
        case 'O':
            outputIp = strdup(optarg);
            printf("Thread[Main]: Ip outputIp %s\n", outputIp);
            break;
        case 'o':
            outputPort = atoi(optarg);
            printf("Thread[Main]: Port of outputPort %d\n", outputPort);
            break;
        case 'C':
            carbonIp = strdup(optarg);
            printf("Thread[Main]: Ip carbonIp %s\n", carbonIp);
            break;
        case 'c':
            carbonPort = atoi(optarg);
            printf("Thread[Main]: Port of carbonPort %d\n", carbonPort);
            break;
        case 'F':
            intervalSendToCarbona = atoi(optarg);
            printf("Thread[Main]: Carbona Send to interval %d seconds.\n", intervalSendToCarbona);
            break;
        case 'T':
            p_raw = strdup(optarg);
            pch = strtok(p_raw, ",");
            while (pch != NULL)
            {
                percentiles[numPercentiles] = atoi(pch);
                pch = strtok(p_raw, ",");
                numPercentiles++;
            }
            printf("Thread[Main]: Percentiles %s (%d values)\n", p_raw, numPercentiles);
            break;
        case 'h':
        default:
            syntax(argv);
            break;
        }
    }
}

void init_stats()
{
    char startup_time[12]; //заполняем строку началом эпохи 1970
    sprintf(startup_time, "%ld", time(NULL));

    remove_stats_lock();

    update_stat("ngfw", "last_send_to_carbon", startup_time); //последний слив
    update_stat("messages", "last_msg_seen", startup_time); //последнее просмотренное сообщение
    update_stat("messages", "bad_lines_seen", "0"); //видны плохие линии
}

int checkValidArgument(void)
{
    int isNotValid = 0;
    if (intervalSendToCarbona == -1)
    {
        isNotValid++;
        printf("Error: The [-F] field is empty.\n");
    }
    if (inputIp == NULL)
    {
        isNotValid++;
        printf("Error: The [-I host] field is empty.\n");
    }
    if (inputPort == -1)
    {
        isNotValid++;
        printf("Error: The [-i port] field is empty.\n");
    }
    if (outputIp == NULL)
    {
        isNotValid++;
        printf("Error: The [-O host] field is empty.\n");
    }
    if (outputPort == -1)
    {
        isNotValid++;
        printf("Error: The [-o port] field is empty.\n");
    }
    if (carbonIp == NULL)
    {
        isNotValid++;
        printf("Error: The [-C host] field is empty.\n");
    }
    if (carbonPort == -1)
    {
        isNotValid++;
        printf("Error: The [-c port] field is empty.\n");
    }


    if (!isNotValid)
    {
        printf("All fields are filled in correctly.\n");
    }
    return isNotValid;
}

int main(int argc, char* argv[])
{
    printf("Thread[Main]: Hello, TimeLine DataBase!\n");
    int pids[3] = {1, 2, 3};



    // Обработка сигналов
    signal(SIGINT, signal_handler); // Обработка прерывания из консоли (Ctrl+C)
    signal(SIGTERM, signal_handler); // Обработка запроса на завершение процесса

    //инициализации семафоров для блокировки потоков
    sem_init(&stats_lock, 0, 1);
    sem_init(&timers_lock, 0, 1);
    sem_init(&counters_lock, 0, 1);
    sem_init(&gauges_lock, 0, 1);
    sem_init(&socketDataQueueLock, 0, 1);

    readArguments(argc, argv);
    if (checkValidArgument()) return 1;



    //Настройка процентили дефолтные
    if (numPercentiles == 0)
    {
        percentiles[0] = 90;
        numPercentiles = 1;
    }

    /* Инициализация системных метрик здесь. */
    init_stats();

    // Инициализация Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
    {
        printf("Thread[Main]: WSAStartup unsuccessful.\n");
        return 1;
    }

    pthread_create(&threadListen, NULL, (void*)&pThreadListen, &pids[0]);
    pthread_create(&threadSend, NULL, (void*)&pThreadMgmtSend, &pids[1]);
    //pthread_create(&threadSendToCarbon, NULL, (void*)&pThreadSendToCarbon, &pids[2]);

    printf("Thread[Main]: Waiting for pthread to complete\n");
    pthread_join(threadListen, NULL);
    pthread_join(threadSend, NULL);
    pthread_join(threadSendToCarbon, NULL);
    printf("Thread[Main]: Pthreads discontinued\n");

    // Завершаем использование библиотеки WS2_32.dll
    WSACleanup();
    return 0;
}
