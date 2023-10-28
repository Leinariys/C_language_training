#include <stdio.h>
#include <string.h>

#define MAX_STRING_SIZE 200

char *convertStringArrayTokens(char *str);

int main() {
    char str[MAX_STRING_SIZE];
    int stepSize = 0;
    printf("Введите текст для разбития лесенкой:\n");
    fgets(str, MAX_STRING_SIZE, stdin);

    char *token = convertStringArrayTokens(str);

    while (token) {
        for (int i = 0; i < stepSize; ++i) {
            printf(" ");
        }
        printf("%s\n", token);

        token = strtok(NULL, " ");//NULL-продолжить разбивать ту же исходную строку
        stepSize += 2;
    }

    return 0;
}

char *convertStringArrayTokens(char *str) {
    str[strcspn(str, "\n")] = 0;
    return strtok(str, " ");//не strtok_r, используем с сохранением состояния
}
