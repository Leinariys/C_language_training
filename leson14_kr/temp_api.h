//
// Created by leina on 015 15.12.2023.
//


typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int temperature;
} Record;

void monthlyAvgTemperature(Record* records, int records_count);
void monthlyMinTemperature(Record* records, int records_count);
void monthlyMaxTemperature(Record* records, int records_count);

void yearlyAvgTemperature(Record* records, int records_count);
void yearlyMinTemperature(Record* records, int records_count);
void yearlyMaxTemperature(Record* records, int records_count);

