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

static void merge(int arr[], int temp[], int start, int end) {
    int length = end - start;
    if (length > 1) {
        int mid = start + (end - start) / 2;
        merge(arr, temp, start, mid);
        merge(arr, temp, mid, end);
        for (int i = start; i < mid; i++) {
            temp[i] = arr[i];
        }
        for (int i = mid; i < end; i++) {
            temp[i] = arr[i];
        }
        int i = start;
        int j = mid;
        int k = start;
        while(i < mid && j < end) {
            arr[k++] = temp[i] <= temp[j] ? temp[i++] : temp[j++];
        }
        while(i < mid) {
            arr[k++] = temp[i++];
        }
        while(j < end) {
            arr[k++] = temp[j++];
        }
    }
}

void mergeSort(int arr[], int length) {
    int *temp = malloc(length * sizeof(int));
    if (!temp) return;
    merge(arr, temp, 0, length);
    free(temp);
}