#include "../tree/BinarySearchTree.h"
#include <stdio.h>

void printNode(int key) {
    printf("%d\t", key);
}

int main() {
    BinarySearchTree *tree = createAVLTree();

    int arr[] = {41, 20, 65, 11, 29, 50, 91, 32, 72, 99};
    int length = sizeof(arr) / sizeof(int);

    for (int i = 0; i < length; i++) {
        tree->insert(tree, arr[i]);
    }

    printf("AVL Tree (Preorder Traversal)\n");
    printf("--------------------------------------------------------------------------------------\n");
    tree->preOrderTraverse(tree, printNode);
    printf("\n\n");

    int key = 42;
    printf("After inserting %d\n", key);
    printf("--------------------------------------------------------------------------------------\n");
    tree->insert(tree, key);
    tree->preOrderTraverse(tree, printNode);
    printf("\n\n");

    int target = 72;
    printf("Searching for value %d\n", target);
    printf("--------------------------------------------------------------------------------------\n");
    if (tree->search(tree, target)) printf("Value %d is found", target);
    else printf("Value %d is not in the BST", target);
    printf("\n\n");

    target = 65;
    printf("Removing value %d\n", target);
    printf("--------------------------------------------------------------------------------------\n");
    tree->remove(tree, target);
    tree->preOrderTraverse(tree, printNode);
    printf("\n");
    
    return 0;
}