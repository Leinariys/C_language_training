//
// Created by leina on Чт 15.08.2024.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void readServerParametersFromArguments(int argc, char* argv[], char** input_ip, int* input_port, char** output_ip,
                                       int* output_port);

void findAndReplace(char* buffer, int bufferSize);
