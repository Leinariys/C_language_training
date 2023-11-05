#include <stdio.h>
#include <complex.h>


int main() {
    int nums[5];
    printf("Ввести пять чисел и  вывести наибольшее из них: \n");
    for(int i = 0; i < 5;i++){
        scanf("%d", &nums[i]);
    }

    int max = nums[0];
    for(int i = 1; i < 5; i++){
        if(nums[i] > max){
            max = nums[i];
        }
    }

    printf("%d\n", max);
    return 0;
}
