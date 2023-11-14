#include <stdio.h>


int checkBrackets(char* s1);

int main() {
    printf("Hello, C20 Задача со *\n"
           "Скобки\n"
           "Проверить строку состоящую из скобок \"(\" и \")\" на корректность. !\n");

    char s1[1002] ;
    scanf("%s", &s1);

    int count = checkBrackets(&s1);

    printf(count == 0 ? "YES\n" : "NO\n");

    return 0;
}


//int checkBrackets(char *s1[]) {  todo почему с [] не работает
int checkBrackets(char *s1) {
    int count = 0;
    for (int i = 0; s1[i] != '.'; i++) {
        if (s1[i] == '(') {
            count++;
        }
        if (s1[i] == ')') {
            count--;
            if (count < 0) {
                return -1;
            }
        }
    }
    return count;
}


