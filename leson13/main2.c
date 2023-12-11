#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR_LEN 1000

int is_palindrom(char *str) {
    int count[26] = {0};

    for (int i = 0; str[i]; i++) {
        if ('a' <= tolower(str[i]) && tolower(str[i]) <= 'z') {
            count[tolower(str[i]) - 'a']++;
        }
    }

    int odd = 0;
    for (int i = 0; i < 26; i++) {
        if (count[i] % 2 == 1) {
            odd++;
        }
    }

    return odd <= 1;
}


int main() {
    printf("Hello, G20 Практ 2\n"
           "Проверка на палиндром\n"
           "Считать предложение из файла .txt и определить можно ли из английских букв предложения записанного в файле "
           "получить одно слово - палиндром. Ответ напечатать на стандартный поток вывода. "
           "Требуется реализовать логическую функцию и применить ее."
           "!\n");

    FILE *file;
    char str[MAX_STR_LEN + 1];

    if ((file = fopen("input.txt", "r"))) {
        fgets(str, sizeof str, file);
        fclose(file);
    } else {
        fprintf(stderr, "Unable to open the input file.\n");
        exit(EXIT_FAILURE);
    }

    if (is_palindrom(str)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;

    return 0;
}
