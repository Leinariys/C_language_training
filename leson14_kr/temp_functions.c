
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "temp_functions.h"

void displayHelp(void) {
    printf("Версия приложения: 1.2.2\n");
    printf("Данное приложение предназначено для обработки csv-файла и вывода статистики.\n");
    printf("Поддерживаемые ключи и их назначение:\n");
    printf("  -h                    Показать эту справку.\n");
    printf("  -f <filename.csv>     Выбор входного файла csv для обработки. "
           "Замените <filename.csv> на имя файла.\n");
    printf("  -m <номер_месяца>     Если задан данный ключ, то выводится статистика "
           "только за указанный месяц. Замените <номер_месяца> на номер месяца.\n");
    printf("Пример использования:\n");
    printf("  Программа -f data.csv -m 3\n");
}

int isValidCsvLine(char *line, Record* recordLine) {
    memset(recordLine, 0, sizeof(*recordLine));
    char* tempLine = strdup(line);
    int fields = 0;
    char const *token = strtok(tempLine, ",");
    int temp;

    while (token != NULL) {
        if (sscanf(token, "%d", &temp) != 1) {
            free(tempLine);
            return 0;
        }
        switch (fields) {
            case 0: recordLine->year = temp; break;
            case 1: recordLine->month = temp; break;
            case 2: recordLine->day = temp; break;
            case 3: recordLine->hour = temp; break;
            case 4: recordLine->minute = temp; break;
            case 5: recordLine->temperature = temp; break;
        }
        fields++;
        token = strtok(NULL, ",");
    }
    free(tempLine);
    return fields == 6;
}
