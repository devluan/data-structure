#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <stdbool.h>

typedef struct Node Node;

struct Node {
    int key;
    Node *left;
    Node *right;
};

typedef struct BinarySearchTree BinarySearchTree;

struct BinarySearchTree {
    Node *root;
    void (*insert)(BinarySearchTree *self, int key);
    void (*inOrderTraverse)(BinarySearchTree *self, void (*callback)(int key));
    void (*preOrderTraverse)(BinarySearchTree *self, void (*callback)(int key));
    void (*postOrderTraverse)(BinarySearchTree *self, void (*callback)(int key));
    Node *(*min)(BinarySearchTree *self);
    Node *(*max)(BinarySearchTree *self);
    bool (*search)(BinarySearchTree *self, int key);
    void (*remove)(BinarySearchTree *self, int key);
};

BinarySearchTree *createBinarySearchTree();

void freeBinarySearchTree(BinarySearchTree **tree);

BinarySearchTree *createAVLTree();

#endif