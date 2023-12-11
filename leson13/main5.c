#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR_LEN 1000

void swapPairs(char *str) {
    for (int i = 0; i < strlen(str) - 1; i += 2) {
        if (!isblank(str[i]) && !isblank(str[i+1])) {
            char temp = str[i];
            str[i] = str[i+1];
            str[i+1] = temp;
        }
    }
}

int main() {
    printf("Hello, G17\n"
           "Пары соседних символов\n"
           "В файле .txt записаны символы. Необходимо разработать функцию, которая меняет местами "
           "пары соседних символов не обращая внимание на символы пробел. Если количество символов "
           "нечетно (пробелы не считаем), то последний символ не меняем. Результат записать в файл .txt. !\n");


    FILE *file_in, *file_out;
    char str[MAX_STR_LEN + 1];

    if ((file_in = fopen("input.txt", "r"))) {
        fgets(str, sizeof str, file_in);
        fclose(file_in);
    } else {
        fprintf(stderr, "Unable to open the input file.\n");
        return EXIT_FAILURE;
    }

    swapPairs(str);

    if ((file_out = fopen("output.txt", "w"))) {
        fprintf(file_out, "%s\n", str);
        fclose(file_out);
    } else {
        fprintf(stderr, "Unable to open the output file.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
