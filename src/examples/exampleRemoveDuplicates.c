#include "../filter/filter.h"
#include <stdio.h>

int main() {
    int nums[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5};
    int length = sizeof(nums) / sizeof(int);

    int k = removeDuplicates(nums, length);

    for (int i = 0; i < k; i++) {
        printf("%d\t", nums[i]);
    }

    return 0;
}