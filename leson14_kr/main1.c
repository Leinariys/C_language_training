#include <stdio.h>

#include "temp_api.h"



int main() {
    Record records[100];
    int records_count = 0;

    monthlyAvgTemperature(records, records_count);
    monthlyMinTemperature(records, records_count);
    monthlyMaxTemperature(records, records_count);

    yearlyAvgTemperature(records, records_count);
    yearlyMinTemperature(records, records_count);
    yearlyMaxTemperature(records, records_count);

    return 0;
}



