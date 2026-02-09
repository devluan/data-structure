#include "binary_search_tree.h"

#include <stdlib.h>
#include <stdbool.h>

static Node *new_node(int key) {
    Node *node = malloc(sizeof(Node));
    if (!node) return NULL;
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static void free_node(Node *node) {
    if (node) {
        free_node(node->left);
        free_node(node->right);
        free(node);
    }
}

static void insert_node(Node *node, int key) {
    if (key < node->key) {
        if (!node->left) node->left = new_node(key);
        else insert_node(node->left, key);
    } else {
        if (!node->right) node->right = new_node(key);
        else insert_node(node->right, key);
    }
}

void insert(BinarySearchTree *tree, int key) {
    if (!tree->root) tree->root = new_node(key);
    else insert_node(tree->root, key);
}

static void in_order_traverse_node(Node *node, void (*callback)(int key)) {
    if (node) {
        in_order_traverse_node(node->left, callback);
        callback(node->key);
        in_order_traverse_node(node->right, callback);
    }
}

void in_order_traverse(BinarySearchTree *tree, void (*callback)(int key)) {
    in_order_traverse_node(tree->root, callback);
}

static void pre_order_traverse_node(Node *node, void (*callback)(int key)) {
    if (node) {
        callback(node->key);
        pre_order_traverse_node(node->left, callback);
        pre_order_traverse_node(node->right, callback);
    }
}

void pre_order_traverse(BinarySearchTree *tree, void (*callback)(int key)) {
    pre_order_traverse_node(tree->root, callback);
}

static void post_order_traverse_node(Node *node, void (*callback)(int key)) {
    if (node) {
        post_order_traverse_node(node->left, callback);
        post_order_traverse_node(node->right, callback);
        callback(node->key);
    }
}

void post_order_traverse(BinarySearchTree *tree, void (*callback)(int key)) {
    post_order_traverse_node(tree->root, callback);
}

static Node *min_node(Node *node) {
    Node *current = node;
    while (current && current->left) {
        current = current->left;
    }
    return current;
}

Node* min(BinarySearchTree *tree) {
    return min_node(tree->root);
}

static Node *max_node(Node *node) {
    Node *current = node;
    while (current && current->right) {
        current = current->right;
    }
    return current;
}

Node *max(BinarySearchTree *tree) {
    return max_node(tree->root);
}

bool search_node(Node *node, int key) {
    if (!node) return false;
    if (key < node->key) return search_node(node->left, key);
    else if (key > node->key) return search_node(node->right, key);
    else return true;

}

bool search(BinarySearchTree *tree, int key) {
    return search_node(tree->root, key);
}

Node *remove_node(Node *node, int key) {
    if (!node) return NULL;
    if (key < node->key) {
        node->left = remove_node(node->left, key);
        return node;
    } else if (key > node->key) {
        node->right = remove_node(node->right, key);
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
        Node *aux = min_node(node->right);
        node->key = aux->key;
        node->right = remove_node(node->right, aux->key);
        return node;
    }
}

void remove(BinarySearchTree *tree, int key) {
    tree->root = remove_node(tree->root, key);
}

BinarySearchTree *new_binary_search_tree() {
    BinarySearchTree *tree = malloc(sizeof(BinarySearchTree));
    if (!tree) return NULL;
    tree->root = NULL;
    tree->insert = insert;
    tree->in_order_traverse = in_order_traverse;
    tree->pre_order_traverse = pre_order_traverse;
    tree->post_order_traverse = post_order_traverse;
    tree->min = min;
    tree->max = max;
    tree->search = search;
    tree->remove = remove;
    return tree;
}

void free_binary_search_tree(BinarySearchTree **tree) {
    if (tree && *tree) {
        free_node((*tree)->root);
        free(*tree);
        *tree = NULL;
    }
}