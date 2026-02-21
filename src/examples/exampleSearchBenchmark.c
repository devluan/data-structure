#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../search/search.h"

int main() {
    clock_t start, end;
    volatile int result;
    int length = 10000;
    int *arr = malloc(length * sizeof(int));

    if (!arr) return 1;

    for (int i = 0; i < length; i++) {
        arr[i] = i;
    }

    start = clock();
    for (int i = 0; i < length; i++) {
         result = sequentialSearch(arr, length, i);
    }
    end = clock();

    double sequentialSearchTime = ((double) end - start) / CLOCKS_PER_SEC;

    start = clock();
    for (int i = 0; i < length; i++) {
        result = binarySearch(arr, length, i);
    }
    end = clock();

    double binarySearchTime = ((double) end - start) / CLOCKS_PER_SEC;

    printf("-------------------------------------------------\n");
    printf("%-20s Total time (s)\n", "Algorithm");
    printf("-------------------------------------------------\n");
    printf("%-20s %.6f\n", "Sequential Search", sequentialSearchTime);
    printf("%-20s %.6f\n", "Binary Search", binarySearchTime);

    free(arr);
    return 0;
}