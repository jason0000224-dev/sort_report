#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 50000      // 陣列大小，可依需求修改

/* partition：以隨機選擇的樞紐分割 a[left..right]，回傳樞紐最終索引 */
int partition(int a[], int left, int right)
{
    /* 隨機選樞紐以降低遇到最差情況的機率 */
    int pivot_idx = left + rand() % (right - left + 1);
    int pivot = a[pivot_idx];
    /* 把樞紐移到最右邊方便處理 */
    int tmp = a[pivot_idx];
    a[pivot_idx] = a[right];
    a[right] = tmp;

    int i = left - 1;
    for (int j = left; j <= right - 1; j++) {
        if (a[j] <= pivot) {
            i++;
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }
    /* 把樞紐放回中間位置 */
    int t2 = a[i + 1];
    a[i + 1] = a[right];
    a[right] = t2;
    return i + 1;
}

/* quick_sort：對 a[left..right] 進行遞迴快速排序 */
void quick_sort(int a[], int left, int right)
{
    if (left < right) {
        int pi = partition(a, left, right);
        quick_sort(a, left, pi - 1);
        quick_sort(a, pi + 1, right);
    }
}

int main()
{
    int *a = (int *)malloc(N * sizeof(int));
    if (a == NULL) {
        fprintf(stderr, "記憶體配置失敗：無法配置 %d 個整數\n", N);
        return EXIT_FAILURE;
    }

    /* 使用時間當亂數種子，讓每次執行的隨機化樞紐不同 */
    srand((unsigned)time(NULL));

    /* 初始化為完全逆序（最差情況），但我們用隨機樞紐來避免最壞遞迴深度 */
    for (int i = 0; i < N; i++)
        a[i] = N - i;

    printf("排序前（前 10 個元素）: ");
    for (int i = 0; i < 10 && i < N; i++)
        printf("%d ", a[i]);
    printf("...\n");

    clock_t start = clock();

    quick_sort(a, 0, N - 1);

    clock_t end = clock();
    double cpu_time_used = (double)(end - start) / CLOCKS_PER_SEC;

    printf("排序後（後 10 個元素）: ... ");
    for (int i = N - 10; i < N; i++)
        printf("%d ", a[i]);
    printf("\n");

    printf("排序 %d 個元素，花費時間 = %.4f 秒\n", N, cpu_time_used);

    free(a);
    return 0;
}
