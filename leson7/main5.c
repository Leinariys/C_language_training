#include <stdio.h>
#include <complex.h>


int main() {
    float x1, y1, x2, y2;
    printf("Определить уравнение прямой по координатам двух точек X1 Y1 X2 Y2: \n");
    scanf("%f %f %f %f", &x1, &y1, &x2, &y2);
    //scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    //float k = (float)(y2 - y1) / (x2 - x1);
    float k = (y2 - y1) / (x2 - x1);
    float b = y1 - k * x1;

    if(b < 0.f)
        printf("y = %.2f*x - %.2f\n", k, -b);
    else if(b == 0.f)
        printf("y = %.2f*x\n", k);
    else
        printf("y = %.2f*x + %.2f\n", k, b);
    return 0;
}
