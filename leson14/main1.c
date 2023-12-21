#include <stdio.h>
#include <stdlib.h>
#include <fileapi.h>

#include "temp_functions.h"

Record *parseCSV(const char *filename, int *recordCount, int month) {
    const int MAX_CHAR_PER_LINE = 1024;
    int lineNumber = 0;
    char line[MAX_CHAR_PER_LINE];
    Record recordLine;
    Record *records = (Record *) malloc(*recordCount * sizeof(Record));


    // Открываем файл
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        char absolutePath[MAX_PATH];
        DWORD sz = GetFullPathName(filename, MAX_PATH, absolutePath, NULL);
        if (sz > 0 && sz <= MAX_PATH) {
            printf("Could not open file %s\n", absolutePath);
        } else {
            printf("Could not open file %s\n", filename);
        }
        return NULL;
    }


    while (fgets(line, sizeof(line), file)) {
        if (lineNumber++ == 0) continue;


        if (isValidCsvLine(line, &recordLine)) {

            if (month) {
                if (recordLine.month == month) {
                    (*recordCount)++;
                    Record *temp = realloc(records, (*recordCount) * sizeof(Record));
                    if (temp == NULL) {
                        printf("Не удалось выделить память, остановка чтения, вывод данных\n");
                        fclose(file);
                        return records;
                    } else {
                        records = temp;
                    }
                    records[*recordCount - 1] = recordLine;
                }
            } else {
                (*recordCount)++;
                Record *temp = realloc(records, (*recordCount) * sizeof(Record));
                if (temp == NULL) {
                    printf("Не удалось выделить память, остановка чтения, вывод данных\n");
                    fclose(file);
                    return records;
                } else {
                    records = temp;
                }
                records[*recordCount - 1] = recordLine;
            }

        } else {
            printf("Ошибка при парсинге числа, строка: %d\n", lineNumber);
        }

    }

    fclose(file);
    return records;
}

int main(int argc, char *argv[]) {
    // Разбор аргументов командной строки
    char *filename = NULL;
    int month = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            displayHelp();
            return 0;
        } else if (strcmp(argv[i], "-f") == 0) {
            if (i + 1 < argc) {
                filename = argv[i + 1];
                i++;
            }
        } else if (strcmp(argv[i], "-m") == 0) {
            if (i + 1 < argc) {
                month = atoi(argv[i + 1]);
                i++;
            }
        }
    }
    int recordCount = 0;

    // Читаем данные из файла
    Record *records = parseCSV(filename, &recordCount, month);

    // Выводим считанные данные
    //for (int i = 0; i < recordCount; i++) {
    //    printf("Year: %d, Month: %d, Day: %d, Hour: %d, Minute: %d, Temperature: %d\n",
    //           records[i].year,
    //           records[i].month,
    //           records[i].day,
    //           records[i].hour,
    //           records[i].minute,
    //           records[i].temperature);
    //}
    printf("\n");

    monthlyAvgTemperature(records, recordCount);
    monthlyMinTemperature(records, recordCount);
    monthlyMaxTemperature(records, recordCount);

    if (!month) {
        yearlyAvgTemperature(records, recordCount);
        yearlyMinTemperature(records, recordCount);
        yearlyMaxTemperature(records, recordCount);
    }



    free(records);

    return 0;
}



