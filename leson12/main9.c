#include <stdio.h>

int countEvenNumbers(const int arr[], int n) {
    int count = 0;
    for(int i = 0; i < n; ++i) {
        if(arr[i] % 2 == 0) {
            ++count;
        }
    }
    return count;
}

int countOddNumbers(const int arr[], int n) {
    return n - countEvenNumbers(arr, n);
}

int productOfEvenDigits(int num) {
    int product = 1;
    while(num) {
        int digit = num % 10;
        if(digit % 2 == 0 && digit != 0) {
            product *= digit;
        }
        num /= 10;
    }
    return product;
}

int productOfOddDigits(int num) {
    int product = 1;
    while(num) {
        int digit = num % 10;
        if(digit % 2 != 0) {
            product *= digit;
        }
        num /= 10;
    }
    return product;
}

void transformArray(int arr[], int n) {
    if(countEvenNumbers(arr, n) > countOddNumbers(arr, n)) {
        for(int i = 0; i < n; ++i) {
            if (arr[i] % 2 != 0) {
                arr[i] = productOfOddDigits(arr[i]);
            }
        }
    }
    else {
        for(int i = 0; i < n; ++i) {
            if (arr[i] % 2 == 0) {
                arr[i] = productOfEvenDigits(arr[i]);
            }
        }
    }
}


int main() {
    printf("Hello, F20\n"
           "Четные и нечетные\n"
           "Написать функцию и программу, демонстрирующую работу данной функции.\n"
           "Дан целочисленный массив из 10 элементов. Необходимо определить количество четных и нечетных чисел. "
           "Если количество чётных чисел больше, чем количество нечётных, заменить каждое нечетное число на произведение "
           "нечетных цифр в его десятичной записи. Если количество нечётных чисел больше или равно количеству чётных, "
           "заменить каждое чётное число на произведение чётных цифр в его десятичной записи. !\n");

    int arr[10];
    for(int i = 0; i < 10; ++i) {
        scanf("%d", &arr[i]);
    }
    transformArray(arr, 10);
    for(int i = 0; i < 10; ++i) {
        printf("%d ", arr[i]);
    }
    return 0;
}
