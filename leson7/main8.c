#include <stdio.h>
#include <complex.h>


int main() {
    int nums[5];
    printf("Ввести пять чисел и  вывести наименьшее из них \n"
           "Нужно напечатать наименьшее число: \n");
    for(int i = 0; i < 5;i++){
        scanf("%d", &nums[i]);
    }

    int min = nums[0];
    for(int i=1; i<5; i++){
        if(nums[i] < min){
            min = nums[i];
        }
    }

    printf("%d\n", min);
    return 0;
}
