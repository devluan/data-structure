#include "search.h"

int sequentialSearch(int arr[], int length, int target) {
    for (int i = 0; i < length; i++) {
        if (arr[i] == target) return i;
    }

    return -1;
}

int binarySearch(int arr[], int length, int target) {
    int start = 0;
    int end = length - 1;
    int mid;

    while (start <= end) {
        mid = start + (end - start) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) end = mid - 1;
        else start = mid + 1;
    }
    
    return -1;
}