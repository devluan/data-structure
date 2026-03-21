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

int getNodeHeight(Node *node) {
    if (!node) return - 1;
    int leftHeight = getNodeHeight(node->left);
    int rightHeight = getNodeHeight(node->right);
    return  (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

#define UNBALANCED_RIGHT -2
#define SLIGHTLY_UNBALANCED_RIGHT -1
#define BALANCED 0
#define SLIGHTLY_UNBALANCED_LEFT 1
#define UNBALANCED_LEFT 2

int getBalanceFactor(Node *node) {
    return getNodeHeight(node->left) - getNodeHeight(node->right);
}

Node* rotationLL(Node *node) {
    Node *tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;
    return tmp;
}

Node* rotationRR(Node *node) {
    Node *tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    return tmp;
}

Node *rotationLR(Node *node) {
    node->left = rotationRR(node->left);
    return rotationLL(node);
}

Node *rotationRL(Node *node) {
    node->right = rotationLL(node->right);
    return rotationRR(node);
}

Node *insertAVLNode(Node *node, int key) {
    if (!node) return createNode(key);
    else if (key < node->key) node->left = insertAVLNode(node->left, key);
    else if (key > node->key) node->right = insertAVLNode(node->right, key);
    else return node;
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor == UNBALANCED_LEFT) {
        if (key < node->left->key) node = rotationLL(node);
        else return rotationLR(node);
    }
    if (balanceFactor == UNBALANCED_RIGHT) {
        if (key > node->right->key) node = rotationRR(node);
        else return rotationRL(node);
    }
    return node;
}

void insertAVL(BinarySearchTree *tree, int key) {
    tree->root = insertAVLNode(tree->root, key);
}

Node *removeAVLNode(Node *node, int key) {
    node = removeNode(node, key);
    if (!node) return node;
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor == UNBALANCED_LEFT) {
        int balanceFactorLeft = getBalanceFactor(node->left);
        if (balanceFactorLeft == BALANCED || balanceFactor == SLIGHTLY_UNBALANCED_LEFT) return rotationLL(node);
        if (balanceFactor == SLIGHTLY_UNBALANCED_RIGHT) return rotationLR(node->left);
    }
    if (balanceFactor == UNBALANCED_RIGHT) {
        int balanceFactorRight = getNodeHeight(node->right);
        if (balanceFactorRight == BALANCED || balanceFactor == SLIGHTLY_UNBALANCED_RIGHT) return rotationRR(node);
        if (balanceFactorRight == SLIGHTLY_UNBALANCED_LEFT) return rotationRL(node->right);
    }
    return node;
}

void removeAVL(BinarySearchTree *tree, int key) {
    tree->root = removeAVLNode(tree->root, key);
}

BinarySearchTree *createAVLTree() {
    BinarySearchTree *tree = malloc(sizeof(BinarySearchTree));
    if (!tree) return NULL;
    tree->root = NULL;
    tree->insert = insertAVL;
    tree->inOrderTraverse = inOrderTraverse;
    tree->preOrderTraverse = preOrderTraverse;
    tree->postOrderTraverse = postOrderTraverse;
    tree->min = min;
    tree->max = max;
    tree->search = search;
    tree->remove = removeAVL;
    return tree;
}