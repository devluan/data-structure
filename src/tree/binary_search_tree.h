#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

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
    void (*in_order_traverse)(BinarySearchTree *self, void (*callback)(int key));
    void (*pre_order_traverse)(BinarySearchTree *self, void (*callback)(int key));
    void (*post_order_traverse)(BinarySearchTree *self, void (*callback)(int key));
    Node *(*min)(BinarySearchTree *self);
    Node *(*max)(BinarySearchTree *self);
    bool (*search)(BinarySearchTree *self, int key);
    void (*remove)(BinarySearchTree *self, int key);
};

BinarySearchTree *new_binary_search_tree();

void free_binary_search_tree(BinarySearchTree **tree);

#endif