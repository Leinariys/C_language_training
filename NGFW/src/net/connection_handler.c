//
// Created by leina on Чт 15.08.2024.
//

#include "connection_handler.h"
#include "../setings.h"


char* output_ip = OUTPUT_IP;
int output_port = OUTPUT_PORT;


void handleConnection(void* socketIn)
{
    printf("Thread[Handle] Thread ID: %lu ClientSocket old address: %p\n", GetCurrentThreadId(), socketIn);

    SOCKET socketInput = *(SOCKET*)socketIn;
    struct sockaddr_in addrOutput;

    printf("Thread[Handle] ID: %lu ClientSocket new address: %p \n", GetCurrentThreadId(), (void*)&socketInput);

    // Создать сокет для выходного порта
    SOCKET socketOutput = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (socketOutput == INVALID_SOCKET)
    {
        printf("Thread[Handle] Socket creation error\n");
        return;
    }

    addrOutput.sin_family = AF_INET;
    addrOutput.sin_addr.s_addr = inet_addr(output_ip);
    addrOutput.sin_port = htons(output_port);

    // Подключитесь к  выходному порту
    if (connect(socketOutput, (struct sockaddr*)&addrOutput, sizeof(addrOutput)) == SOCKET_ERROR)
    {
        printf("Thread[Handle] Connect failed\n");
        return;
    }

    // Передача данных между вход->выход->выход(ожидание ответа)->вход
    while (1)
    {
        int bytesReceived = -9;
        void* bufferInput = getDataFromSocket(socketInput, &bytesReceived);
        if (bufferInput == NULL) break;

        //todo тут надо добавить фильтрацию по IP черный/белый список

        if (!setDataToSocket(socketOutput, bufferInput, bytesReceived)) break;

        bytesReceived = -9;
        void* bufferOutput = getDataFromSocket(socketOutput, &bytesReceived);
        if (bufferOutput == NULL) break;

        if (!setDataToSocket(socketInput, bufferOutput, bytesReceived)) break;
    }
    //todo сделать обработчики ошибок - разрыв соединения и т.д. и потоки закрывать

    closesocket(socketInput);
    closesocket(socketOutput);
}

