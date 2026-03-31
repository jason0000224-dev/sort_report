#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 10000      // 陣列大小，可依需求修改

/* insertion_sort：插入排序（升冪）
 *  a[] : 待排序整數陣列
 *  n   : 陣列長度
 */
void insertion_sort(int a[], int n)
{
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;

        /* 將 a[i] 插入到已排序子陣列 a[0..i-1] 中 */
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = key;
    }
}

int main()
{
    int a[N];
    clock_t start, end;
    double cpu_time_used;

    /* 初始化為完全逆序（最差情況） */
    for (int i = 0; i < N; i++)
        a[i] = N - i;

    printf("排序前（前 10 個元素）: ");
    for (int i = 0; i < 10 && i < N; i++)
        printf("%d ", a[i]);
    printf("...\n");

    start = clock();

    insertion_sort(a, N);

    end = clock();
    cpu_time_used = (double)(end - start) / CLOCKS_PER_SEC;

    printf("排序後（後 10 個元素）: ... ");
    for (int i = N - 10; i < N; i++)
        printf("%d ", a[i]);
    printf("\n");

    printf("排序 %d 個元素，花費時間 = %.4f 秒\n", N, cpu_time_used);

    return 0;
}
