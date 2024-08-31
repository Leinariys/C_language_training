
#include "string_replacement.h"


void readServerParametersFromArguments(int argc, char* argv[], char** input_ip, int* input_port, char** output_ip,
                                       int* output_port)
{
    if (argc > 3)
    {
        *input_ip = argv[1];
        *input_port = atoi(argv[2]);
        *output_ip = argv[3];
        *output_port = atoi(argv[4]);
    }
    else
    {
        printf("Not enough arguments provided. Using default parameters.\n");
    }

    printf("Input IP: %s\n", *input_ip);
    printf("Input Port: %d\n", *input_port);
    printf("Output IP: %s\n", *output_ip);
    printf("Output Port: %d\n", *output_port);
}

void findAndReplace(char* buffer, int bufferSize)
{
    char* searchString = "192.168.1.10:8011";
    char* replaceString = "192.168.1.10:8077";

    char* found = strstr(buffer, searchString);

    if (found != NULL)
    {
        int searchLen = strlen(searchString);
        int replaceLen = strlen(replaceString);

        if (replaceLen > searchLen)
        {
            // Если длина заменяемой строки больше, сдвигаем оставшуюся часть буфера
            memmove(found + replaceLen, found + searchLen, bufferSize - (found - buffer) - searchLen);
        }
        else if (replaceLen < searchLen)
        {
            // Если длина заменяемой строки меньше, сдвигаем оставшуюся часть буфера
            memmove(found + replaceLen, found + searchLen, bufferSize - (found - buffer) - searchLen);
        }

        // Копируем заменяемую строку в буфер
        memcpy(found, replaceString, replaceLen);
    }
}

