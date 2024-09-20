//
// Created by leina on Пн 16.09.2024.
//

#include "SocketTcpListener.h"


char* inputIp = NULL;
int inputPort = -1;
int backlog = 10;

UT_array* socketDataQueue = {};
sem_t socketDataQueueLock = {};

SOCKET socketServer;

/// Инициализация сокета
/// @return Дескриптор сокета, если ошибка то SOCKET_ERROR
int socketInitialize(void)
{
    //Создаем новый TCP сокет
    if ((socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) == INVALID_SOCKET)
    {
        printf("Thread[Listen]: Could not create socket stats mgmt. EXIT!");
        return SOCKET_ERROR;
    }

    int yes = 1;
    // Устанавливаем параметры сокета (реиспользование адреса+порта)
    if (setsockopt(socketServer, SOL_SOCKET, SO_REUSEADDR, (char*)&yes, sizeof(int)) == SOCKET_ERROR)
    {
        int err_code = errno;
        printf("Thread[Listen]: setsockopt failed with error code %d: %s\n", err_code, strerror(err_code));
        return SOCKET_ERROR;
    }

    /* bind */
    struct sockaddr_in serverAddr;
    memset((char*)&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(inputIp); //INADDR_ANY
    serverAddr.sin_port = htons(inputPort);

    if (bind(socketServer, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        printf("Thread[Listen]: Binding failed with error code: %d\n", WSAGetLastError());
        return SOCKET_ERROR;
    }

    if (listen(socketServer, backlog) == SOCKET_ERROR)
    {
        printf("Thread[Listen]: Listening failed with error code: %d\n", WSAGetLastError());
        return SOCKET_ERROR;
    }
    return socketServer;
}

/// Принять новое соединение
/// @param master
/// @param fdmax
/// @param socketServer
void acceptNewConnection(fd_set* master, int* fdmax, SOCKET socketServer)
{
    //TODO Метрика нового соединения
    struct sockaddr_in clientAddr;
    int newfd;
    int addrlen = sizeof(clientAddr);
    if ((newfd = accept(socketServer, (struct sockaddr*)&clientAddr, (socklen_t*)&addrlen)) == -1)
    {
        printf("Thread[Listen]: accept error");
    }
    else
    {
        //Если соединение установлено успешно, новый дескриптор добавляется в множество master
        FD_SET(newfd, master);
        if (newfd > *fdmax)
        {
            *fdmax = newfd;
        }
        printf("Thread[Listen]: New connection from %s on socket %d\n",
               inet_ntoa(clientAddr.sin_addr),
               newfd);

        //sendConnectionHint(newfd); //nen Тут надо сообщение в очередь на отправку класть если тебуется преветственное сообщение
    }
}


/// Обработка входящего сообщения
/// @param master
/// @param descriptorReadyToRead
/// @param continues
/// @return
void processDataFromClient(fd_set* master, int descriptorReadyToRead, int* continues)
{
    unsigned long bufferSizeReceived = 0;
    //Провное чтение для проверки что сообщение есть и соединение существует
    {
        int nbytes = -1;
        while (1)
        {
            if (ioctlsocket(descriptorReadyToRead, FIONREAD, &bufferSizeReceived) != 0)
            {
                printf("Thread[Listen]: Error getting available bytes\n");
            }

            char bufferReceived[3];
            //Если это FIN пакет или ошибка соединения nbytes вернёт -1
            nbytes = recv(descriptorReadyToRead, bufferReceived, 3, MSG_PEEK);
            if (nbytes <= 0)
            {
                if (nbytes == 0)
                {
                    //todo не понятно как сделать такой случай
                    printf("Thread[Listen]: Socket %d is stuck\n", descriptorReadyToRead);
                }
                else
                {
                    printf("Thread[Listen]: Socket %d close. Cause recv error()\n",
                           descriptorReadyToRead);
                }
                close(descriptorReadyToRead);
                FD_CLR(descriptorReadyToRead, master);
                break;
            }

            if (bufferSizeReceived)
            {
                printf("Thread[Listen]: Allocated memory: %lu bytes\n", bufferSizeReceived);
                break;
            }
            else
            {
                printf("Thread[Listen]: Thread Sleep\n");
                Sleep(1);
            }
        }
        if (nbytes == -1)
        {
            *continues = 1;
            return;
        }
    }

    //Выделение памяти под данные из сокета
    char* bufferReceived = malloc(bufferSizeReceived);
    if (bufferReceived == NULL)
    {
        printf("Thread[Listen]: Error allocating memory bufferReceived\n");
    }

    /* Получение данные от клиента */
    int nbytes;
    if ((nbytes = recv(descriptorReadyToRead, bufferReceived, bufferSizeReceived, 0)) <= 0)
    {
        if (nbytes == 0)
        {
            printf("Thread[Listen]: Socket %d is stuck\n", descriptorReadyToRead);
        }
        else
        {
            printf("Thread[Listen]: receiving error()");
        }

        close(descriptorReadyToRead);
        FD_CLR(descriptorReadyToRead, master);
    }
    else
    {
        sem_wait(&socketDataQueueLock);
        struct SocketData* sDate = malloc(sizeof(struct SocketData));
        if (sDate == NULL) {
            // Обработка ошибки, если выделение памяти не удалось
            printf("Error allocating memory for ip\n");
        }
        printf("Thread[Listen]: Address of var p: %p\n", (void*)sDate);
        sDate->socketI = socketServer;
        sDate->socketC = descriptorReadyToRead;
        sDate->data = malloc(bufferSizeReceived);
        if (sDate->data == NULL)
        {
            printf("Thread[Listen]: Error allocating memory ip->data\n");
        }
        memcpy(sDate->data, bufferReceived, bufferSizeReceived);
        sDate->size = bufferSizeReceived;
        utarray_push_back(socketDataQueue, sDate); //тут копирование memcpy ещё одно

        printf("Thread[Listen]: 111 \n");
        free(sDate);
        sDate = NULL;
        printf("Thread[Listen]: 222 \n");
        sem_post(&socketDataQueueLock);
    }
    printf("Thread[Listen]: 333 \n");
    if (bufferReceived) free(bufferReceived);
    printf("Thread[Listen]: 444 \n");
}

///
/// @return
int doListener(void)
{
    /* begin listener */
    UT_icd socketData_icd = {sizeof(struct SocketData), NULL, NULL, NULL};
    utarray_new(socketDataQueue, &socketData_icd);

    if ((socketServer = socketInitialize()) == SOCKET_ERROR) return SOCKET_ERROR;

    fd_set master;
    fd_set read_fds;
    FD_ZERO(&master);
    FD_ZERO(&read_fds);

    FD_SET(socketServer, &master);
    int fdmax = socketServer;

    for (;;)
    {
        //Копируем для select чтобы работал с полным набором дискрипторов
        read_fds = master;

        //Перебирает каждый дескриптор сокета от 0 до fdmax
        if (select(fdmax + 1, &read_fds, NULL, NULL, NULL) == SOCKET_ERROR)
        {
            printf("Thread[Listen]: Select failed with error code: %d\n", WSAGetLastError());
            return closesocket(socketServer);
        }

        //
        for (int descriptorReadyToRead = 0; descriptorReadyToRead <= fdmax; descriptorReadyToRead++)
        {
            //готов ли дескриптор файла i для чтения, но это НЕ значит что данные доступны все
            if (FD_ISSET(descriptorReadyToRead, &read_fds))
            {
                //Проверяем что сервер с новым соединением
                if (descriptorReadyToRead == socketServer)
                {
                    acceptNewConnection(&master, &fdmax, socketServer);
                }
                else
                {
                    int continues = 0;;
                    processDataFromClient(&master, descriptorReadyToRead, &continues);
                    if (continues) continue;
                }
            }
        }
    }
}
