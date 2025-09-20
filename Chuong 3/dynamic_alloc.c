#include <stdio.h>
#include <stdlib.h>

int main() {
    // Cấp phát nhiều khối nhỏ
    printf("--- Cap phat nhieu khoi nho ---\n");
    int *p1 = (int*) malloc(10 * sizeof(int));
    int *p2 = (int*) malloc(20 * sizeof(int));
    int *p3 = (int*) malloc(15 * sizeof(int));
    int *p4 = (int*) malloc(5 * sizeof(int));

    printf("Dia chi khoi p1: %p\n", p1);
    printf("Dia chi khoi p2: %p\n", p2);
    printf("Dia chi khoi p3: %p\n", p3);
    printf("Dia chi khoi p4: %p\n", p4);

    // Giải phóng một vài khối ở giữa
    printf("\n--- Giai phong p2 va p4 ---\n");
    free(p2);
    free(p4);
    printf("Da giai phong p2 va p4.\n");

    // Yêu cầu một khối lớn
    printf("\n--- Cap phat mot khoi lon (p5) ---\n");
    int *p5 = (int*) malloc(50 * sizeof(int));
    printf("Dia chi khoi p5: %p\n", p5);

    // Giải phóng toàn bộ
    free(p1);
    free(p3);
    free(p5);

    return 0;
}