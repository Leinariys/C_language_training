#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 1000


int main() {
    printf("Hello, G13\n"
           "Изменить расширение\n"
           "В файле .txt записан полный адрес файла (возможно, без расширения). Необходимо изменить "
           "его расширение на \".html\" и записать результат в файл .txt. !\n");

    FILE *file_in, *file_out;
    char path[MAX_STR_LEN + 1];

    if ((file_in = fopen("input.txt", "r"))) {
        fgets(path, sizeof path, file_in);
        fclose(file_in);
    } else {
        fprintf(stderr, "Unable to open the input file.\n");
        return EXIT_FAILURE;
    }

    // Удаляем newline полученный из fgets
    path[strcspn(path, "\n")] = 0;
    char *ext_pos = strrchr(path, '.');  // Позиция последней точки
    if (ext_pos != NULL) {
        *ext_pos = '\0'; // Заканчиваем строку перед точкой если она найдена
    }

    strcat(path, ".html");

    if ((file_out = fopen("output.txt", "w"))) {
        fprintf(file_out, "%s\n", path);
        fclose(file_out);
    } else {
        fprintf(stderr, "Unable to open the output file.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
