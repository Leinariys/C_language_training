//
// Created by leina on Чт 15.08.2024.
//

#include "../net/server.h"
#include "connection_handler.h"
#include "../setings.h"


char* input_ip = INPUT_IP;
int input_port = INPUT_PORT;


//TODO да этот метод можно разбить на методы но читать стало не очень
int initServer()
{
    WSADATA wsa;
    SOCKET clientSocket;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_len = sizeof(client_addr);
    unsigned int threadId;
    printf("Thread[Main] ID: %lu ", GetCurrentThreadId());

    // Инициализировать Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Thread[Main] WSAStartup failed. Error Code : %d\n", WSAGetLastError());
        return 1;
    }

    // Создать сокет для входящего порта.
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (serverSocket == INVALID_SOCKET)
    {
        printf("Thread[Main] Could not create socket : %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(input_ip);
    server_addr.sin_port = htons(input_port);

    // Привязать сокет к входящему порту
    if (bind(serverSocket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
    {
        printf("Thread[Main] Bind failed with error code : %d\n", WSAGetLastError());
        return 1;
    }

    // Начало прослушивания входящие соединения
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) //0x7fffffff = 2147483647 количество соединений
    {
        printf("Thread[Main] Listen failed\n");
        return 1;
    }

    printf("Thread[Main] Waiting for incoming connections...\n");

    while (1)
    {
        printf("Thread[Main] ClientSocket address: %p\n", (void*)&clientSocket);
        // ожидание и принятие входящего соединения
        clientSocket = accept(serverSocket, (struct sockaddr*)&client_addr, &client_addr_len);
        if (clientSocket == INVALID_SOCKET)
        {
            printf("Thread[Main] Accept failed\n");
            return 1;
        }

        printf("Thread[Main] Thread ID: %lu ClientSocket address: %p Connection accepted from IP: %s, Port: %d, \n",
               GetCurrentThreadId(), (void*)&clientSocket, inet_ntoa(client_addr.sin_addr),
               ntohs(client_addr.sin_port));


        //todo сделать список потоков и опрашивать их статус(системный) + свой статус передавать (отправка/чтение)
        _beginthreadex(NULL, 0, handleConnection, &clientSocket, 0, &threadId);
    }

    closesocket(serverSocket);
    WSACleanup();
}


