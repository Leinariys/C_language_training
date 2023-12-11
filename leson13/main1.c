#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>



char soundexVal(char ch) {
    switch(tolower(ch)) {
        case 'b': case 'f': case 'p': case 'v':
            return '1';
        case 'c': case 'g': case 'j': case 'k': case 'q': case 's': case 'x': case 'z':
            return '2';
        case 'd': case 't':
            return '3';
        case 'l':
            return '4';
        case 'm': case 'n':
            return '5';
        case 'r':
            return '6';
        default:
            return 0;
    }
}

void soundex(const char *name, char *res) {
    while (*res = *name) {
        *res = toupper(*res);
        res++;
        name++;
    }
    *res = soundexVal(*name);
    char prevVal = *res;
    while (*name) {
        char val = soundexVal(*name);
        if (val > 0 && val != prevVal) {
            *(res++) = val;
            prevVal = val;
        }
        name++;
    }
    while(res - res < 4 && *res) {
        *(res++) = '0';
    }
    *res = '\0';
}



int main() {
    printf("Hello, G22\n"
           "Soundex\n"
           "Известный алгоритм Soundex (https://ru.wikipedia.org/wiki/Soundex) определяет, "
           "похожи ли два английских слова по звучанию. На вход он принимает слово и заменяет "
           "его на некоторый четырёхсимвольный код. Если коды двух слов совпадают, то слова, "
           "как правило, звучат похоже.!\n");

    FILE *file_in, *file_out;
    char name[21];
    char result[5];
    if ((file_in = fopen("input.txt", "r"))) {
        fscanf(file_in, "%20s", name);
        fclose(file_in);
    }
    else {
        fprintf(stderr, "Unable to open the input file.\n");
        exit(EXIT_FAILURE);
    }
    soundex(name, result);
    if ((file_out = fopen("output.txt", "w"))) {
        fprintf(file_out, "%s\n", result);
        fclose(file_out);
    }
    else {
        fprintf(stderr, "Unable to open the output file.\n");
        exit(EXIT_FAILURE);
    }
    return 0;

    return 0;
}
