#include "../tree/binary_search_tree.h"
#include <stdio.h>

void print_node(int key) {
    printf("%d\t", key);
}

int main() {
    BinarySearchTree *tree = new_binary_search_tree();

    int arr[] = {20, 3, 1, 8, 7, 21, 31, 40, 30};
    int length = sizeof(arr) / sizeof(int);

    for (int i = 0; i < length; i++) {
        tree->insert(tree, arr[i]);
    }

    printf("%-20s | Sequence\n", "Traversal Type");
    printf("---------------------|------------------------------------------------------------------------\n");

    printf("%-20s | ", "In-order");
    tree->in_order_traverse(tree, print_node);
    printf("\n");

    printf("%-20s | ", "Pre-order");
    tree->pre_order_traverse(tree, print_node);
    printf("\n");

    printf("%-20s | ", "Post-order");
    tree->post_order_traverse(tree, print_node);
    printf("\n");

    free_binary_search_tree(&tree);
}