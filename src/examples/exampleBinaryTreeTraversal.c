#include "../tree/BinarySearchTree.h"
#include <stdio.h>

void printNode(int key) {
    printf("%d\t", key);
}

int main() {
    BinarySearchTree *tree = createBinarySearchTree();

    int arr[] = {20, 3, 1, 8, 7, 21, 31, 40, 30};
    int length = sizeof(arr) / sizeof(int);

    for (int i = 0; i < length; i++) {
        tree->insert(tree, arr[i]);
    }

    printf("%-20s | Sequence\n", "Traversal Type");
    printf("---------------------|------------------------------------------------------------------------\n");

    printf("%-20s | ", "In-order");
    tree->inOrderTraverse(tree, printNode);
    printf("\n");

    printf("%-20s | ", "Pre-order");
    tree->preOrderTraverse(tree, printNode);
    printf("\n");

    printf("%-20s | ", "Post-order");
    tree->postOrderTraverse(tree, printNode);
    printf("\n");

    freeBinarySearchTree(&tree);
}