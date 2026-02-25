#include "sort.h"
#include <stdlib.h>

void bubbleSort(int arr[], int length) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

static int *slice(int arr[], int start, int end) {
    int length = end - start;
    int *result = malloc(length * sizeof(int));
    for (int i = 0; i < length; i++) {
        result[i] = arr[start + i];
    }
    return result;
}

static void merge(int arr[], int left, int middle, int right) {
    int *l = slice(arr, left, middle), *r = slice(arr, middle, right);
    int lenL = middle - left, lenR = right - middle;
    int i = 0, j = 0, k = left;
    while(i < lenL && j < lenR) {
        arr[k++] = l[i] <= r[j] ? l[i++] : r[j++];
    }
    while(i < lenL) {
        arr[k++] = l[i++];
    }
    while(j < lenR) {
        arr[k++] = r[j++];
    }
    free(l);
    free(r);
}

void mergeSort(int arr[], int left, int right) {
    int length = right - left;
    if (length > 1) {
        int middle = left + (right - left) / 2;
        mergeSort(arr, left, middle);
        mergeSort(arr, middle, right);
        merge(arr, left, middle, right);
    }
}