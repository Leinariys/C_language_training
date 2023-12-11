#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR_LEN 1000

void removeSpaces(char *str) {
    int count = 0;
    int i = 0;
    while (isspace(str[i]))
        i++;
    for (; str[i]; i++) {
        if (!isspace(str[i]) || (i + 1 < MAX_STR_LEN && !isspace(str[i+1]))) {
            str[count] = str[i];
            count++;
        }
    }
    str[count] = '\0';
}

int main() {
    printf("Hello, G18\n"
           "Удалить пробелы из текста\n"
           "В файле .txt необходимо удалить все лишние пробелы (в начале предложения и сдвоенные пробелы). "
           "Для решения задачи разработать функцию. Результат записать в .txt. !\n");

    FILE *file_in, *file_out;
    char sentence[MAX_STR_LEN + 1];

    if ((file_in = fopen("input.txt", "r"))) {
        fgets(sentence, sizeof sentence, file_in);
        fclose(file_in);
    } else {
        fprintf(stderr, "Unable to open the input file.\n");
        return EXIT_FAILURE;
    }

    removeSpaces(sentence);

    if ((file_out = fopen("output.txt", "w"))) {
        fprintf(file_out, "%s\n", sentence);
        fclose(file_out);
    } else {
        fprintf(stderr, "Unable to open the output file.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
