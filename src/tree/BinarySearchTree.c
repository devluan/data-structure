#include "BinarySearchTree.h"

#include <stdlib.h>
#include <stdbool.h>

static Node *createNode(int key) {
    Node *node = malloc(sizeof(Node));
    if (!node) return NULL;
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static void freeNode(Node *node) {
    if (node) {
        freeNode(node->left);
        freeNode(node->right);
        free(node);
    }
}

static void insertNode(Node *node, int key) {
    if (key < node->key) {
        if (!node->left) node->left = createNode(key);
        else insertNode(node->left, key);
    } else {
        if (!node->right) node->right = createNode(key);
        else insertNode(node->right, key);
    }
}

void insert(BinarySearchTree *tree, int key) {
    if (!tree->root) tree->root = createNode(key);
    else insertNode(tree->root, key);
}

static void inOrderTraverseNode(Node *node, void (*callback)(int key)) {
    if (node) {
        inOrderTraverseNode(node->left, callback);
        callback(node->key);
        inOrderTraverseNode(node->right, callback);
    }
}

void inOrderTraverse(BinarySearchTree *tree, void (*callback)(int key)) {
    inOrderTraverseNode(tree->root, callback);
}

static void preOrderTraverseNode(Node *node, void (*callback)(int key)) {
    if (node) {
        callback(node->key);
        preOrderTraverseNode(node->left, callback);
        preOrderTraverseNode(node->right, callback);
    }
}

void preOrderTraverse(BinarySearchTree *tree, void (*callback)(int key)) {
    preOrderTraverseNode(tree->root, callback);
}

static void postOrderTraverseNode(Node *node, void (*callback)(int key)) {
    if (node) {
        postOrderTraverseNode(node->left, callback);
        postOrderTraverseNode(node->right, callback);
        callback(node->key);
    }
}

void postOrderTraverse(BinarySearchTree *tree, void (*callback)(int key)) {
    postOrderTraverseNode(tree->root, callback);
}

static Node *minNode(Node *node) {
    Node *current = node;
    while (current && current->left) {
        current = current->left;
    }
    return current;
}

Node* min(BinarySearchTree *tree) {
    return minNode(tree->root);
}

static Node *maxNode(Node *node) {
    Node *current = node;
    while (current && current->right) {
        current = current->right;
    }
    return current;
}

Node *max(BinarySearchTree *tree) {
    return maxNode(tree->root);
}

static bool searchNode(Node *node, int key) {
    if (!node) return false;
    if (key < node->key) return searchNode(node->left, key);
    else if (key > node->key) return searchNode(node->right, key);
    else return true;

}

bool search(BinarySearchTree *tree, int key) {
    return searchNode(tree->root, key);
}

Node *removeNode(Node *node, int key) {
    if (!node) return NULL;
    if (key < node->key) {
        node->left = removeNode(node->left, key);
        return node;
    } else if (key > node->key) {
        node->right = removeNode(node->right, key);
        return node;
    } else {
        if (!node->left && !node->right) {
            free(node);
            return NULL;
        }
        if (!node->left) {
            Node *right = node->right;
            free(node);
            return right;
        } else if (!node->right) {
            Node *left = node->left;
            free(node);
            return left;
        }
        Node *aux = minNode(node->right);
        node->key = aux->key;
        node->right = removeNode(node->right, aux->key);
        return node;
    }
}

void remove(BinarySearchTree *tree, int key) {
    tree->root = removeNode(tree->root, key);
}

BinarySearchTree *createBinarySearchTree() {
    BinarySearchTree *tree = malloc(sizeof(BinarySearchTree));
    if (!tree) return NULL;
    tree->root = NULL;
    tree->insert = insert;
    tree->inOrderTraverse = inOrderTraverse;
    tree->preOrderTraverse = preOrderTraverse;
    tree->postOrderTraverse = postOrderTraverse;
    tree->min = min;
    tree->max = max;
    tree->search = search;
    tree->remove = remove;
    return tree;
}

void freeBinarySearchTree(BinarySearchTree **tree) {
    if (tree && *tree) {
        freeNode((*tree)->root);
        free(*tree);
        *tree = NULL;
    }
}