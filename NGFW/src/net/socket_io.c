//
// Created by leina on Чт 15.08.2024.
//

#include "socket_io.h"


// Чтения данных из сокета
void* getDataFromSocket(SOCKET socketInput, int* bytesReceived)
{
    unsigned long bytesAvailable;
    while (1)
    {
        if (ioctlsocket(socketInput, FIONREAD, &bytesAvailable) != 0)
        {
            printf("Error getting available bytes\n");
            return NULL;
        }
        if (bytesAvailable)
        {
            printf("Allocated memory: %lu bytes\n", bytesAvailable);
            break;;
        }
        else
        {
            Sleep(1);
        }
    }

    char* buffer = malloc(bytesAvailable);
    if (buffer == NULL)
    {
        printf("Error allocating memory\n");
        return NULL;
    }

    *bytesReceived = recv(socketInput, buffer, bytesAvailable, MSG_WAITALL);

    // Логирование прочитанных данных в ковычках с указанием размера
    //printf("Received data: \"%.*s\" (Size: %d)\n", *bytesReceived, buffer, *bytesReceived);

    if (*bytesReceived < 0)
    {
        int savedErrno = errno;
        // Обработка ошибки при чтении
        if (savedErrno == EAGAIN)
        {
            //Ресурс временно недоступен
            fprintf(stderr, "Resource temporarily unavailable\n");
        }
        else if (savedErrno == ECONNRESET)
        {
            //Сброс соединения партнером
            fprintf(stderr, "Connection reset by peer\n");
        }
        else
        {
            //Ошибка получения данных
            printf("Error receiving data: %d\n", savedErrno);
        }
        // Дополнительная обработка ошибки
        free(buffer); // Освобождаем память при обработке ошибки
        return NULL;
    }
    else if (*bytesReceived == 0)
    {
        // Соединение закрыто или сообщение завершено
        printf("Connection closed or message completed\n");
        return NULL;
    }
    else
    {
        // Обработка принятых данных (например, сохранение их в буфер)
        printf("Processing received data \n");
    }

    return buffer;
}

//Отправка данных
boolean setDataToSocket(SOCKET socketOutput, char* buffer, int bytesReceived)
{
    int bytesSent = send(socketOutput, buffer, bytesReceived, 0);
    free(buffer);
    if (bytesSent <= 0) return 0;
    return 1;
};

