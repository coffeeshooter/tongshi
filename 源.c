#include <stdio.h>
#include <string.h>
#define MAX 100
void bucketsort(int A[], int size, int max_num)
{
    int count[MAX];
    memset(count, 0, sizeof(count));
    for (int i = 0; i < size; i++) {
        ++count[A[i]];
    }
    for (int j = 0; j <= max_num; j++) {
        while (count[j] > 0) {
            printf("%d ", j);
            count[j]--;
        }
    }
    printf("\n");
}


int main()
{ 
    int a[] = { 2, 5, 6, 12, 4, 8, 8, 6, 7, 8, 8, 10, 7, 6, 0, 1 };
    bucketsort(a, sizeof(a) / sizeof(a[0]), 12);
    return 0;
}
