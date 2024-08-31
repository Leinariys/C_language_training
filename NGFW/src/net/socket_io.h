//
// Created by leina on Чт 15.08.2024.
//

#include <winsock2.h>
#include <stdio.h>

void* getDataFromSocket(SOCKET socketInput, int* bytesReceived);
boolean setDataToSocket(SOCKET socketOutput, char* buffer, int bytesReceived);