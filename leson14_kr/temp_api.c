//
// Created by leina on 015 15.12.2023.
//


#include "temp_api.h"
#include <stdio.h>
#include <limits.h>

void monthlyAvgTemperature(Record* records, int records_count) {
    for (int month = 1; month <= 12; ++month) {
        int temp_sum = 0;
        int temp_count = 0;
        int is_present = 0;

        for (int i = 0; i < records_count; ++i) {
            if (records[i].month == month) {
                temp_sum += records[i].temperature;
                temp_count++;
                is_present = 1;
            }
        }
        if (is_present) {
            float avg_temp = temp_count == 0 ? 0 : (float)temp_sum / temp_count;
            printf("Средняя температура за месяц %d: %.2f\n", month, avg_temp);
        }
    }
    printf("\n");
}

void monthlyMinTemperature(Record* records, int records_count) {
    for (int month = 1; month <= 12; ++month) {
        int min_temp = INT_MAX;
        int is_present = 0;

        for (int i = 0; i < records_count; ++i) {
            if (records[i].month == month &&
                records[i].temperature < min_temp) {
                min_temp = records[i].temperature;
                is_present = 1;
            }
        }
        if (is_present) {
            printf("Минимальная температура за месяц %d: %d\n", month, min_temp);
        }
    }
    printf("\n");
}

void monthlyMaxTemperature(Record* records, int records_count) {
    for (int month = 1; month <= 12; ++month) {
        int max_temp = INT_MIN;
        int is_present = 0;

        for (int i = 0; i < records_count; ++i) {
            if (records[i].month == month &&
                records[i].temperature > max_temp) {
                max_temp = records[i].temperature;
                is_present = 1;
            }
        }
        if (is_present) {
            printf("Максимальная температура за месяц %d: %d\n", month, max_temp);
        }
    }
    printf("\n");
}

void yearlyAvgTemperature(Record* records, int records_count) {
    if (records_count == 0) return;


    int year = records[0].year;
    int temp_total = 0;

    for (int i = 0; i < records_count; ++i) {
        temp_total += records[i].temperature;
    }

    float avg_temp = (float)temp_total / records_count;

    printf("Средняя температура за год %d: %.2f\n", year, avg_temp);
}

void yearlyMinTemperature(Record* records, int records_count) {
    if (records_count == 0) return;


    int min_temp = records[0].temperature;

    for (int i = 1; i < records_count; ++i) {
        if (records[i].temperature < min_temp) {
            min_temp = records[i].temperature;
        }
    }

    printf("Минимальная температура за год %d: %d\n", records[0].year, min_temp);
}

void yearlyMaxTemperature(Record* records, int records_count) {
    if (records_count == 0) return;


    int max_temp = records[0].temperature;

    for (int i = 1; i < records_count; ++i) {
        if (records[i].temperature < max_temp) {
            max_temp = records[i].temperature;
        }
    }

    printf("Максимальная температура за год %d: %d\n", records[0].year, max_temp);
}
