#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000      // 陣列大小（預設改為 50000）

/* merge：合併兩個已排序子陣列 a[left..mid] 與 a[mid+1..right] */
void merge(int a[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    if (L == NULL || R == NULL) {
        fprintf(stderr, "記憶體配置失敗\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }
    while (i < n1)
        a[k++] = L[i++];
    while (j < n2)
        a[k++] = R[j++];

    free(L);
    free(R);
}

/* merge_sort：對 a[left..right] 進行合併排序（遞迴） */
void merge_sort(int a[], int left, int right)
{
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(a, left, mid);
        merge_sort(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}

int main()
{
    int *a = (int *)malloc(N * sizeof(int));
    if (a == NULL) {
        fprintf(stderr, "記憶體配置失敗：無法配置 %d 個整數\n", N);
        return EXIT_FAILURE;
    }

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

    merge_sort(a, 0, N - 1);

    end = clock();
    cpu_time_used = (double)(end - start) / CLOCKS_PER_SEC;

    printf("排序後（後 10 個元素）: ... ");
    for (int i = N - 10; i < N; i++)
        printf("%d ", a[i]);
    printf("\n");

    printf("排序 %d 個元素，花費時間 = %.4f 秒\n", N, cpu_time_used);

    free(a);
    return 0;
}
