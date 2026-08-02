#include <stdbool.h>
#include <stdlib.h>
#include "avl.h"

int getHeight(const struct Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int getBalanceFactor(const struct Node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

struct Node* rotateRight(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = fmax(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = fmax(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

struct Node* rotateLeft(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = fmax(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = fmax(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

struct Node* insertNode(struct Node* node, int key) {
    if (node == NULL) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        newNode->key = key;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->height = 1;
        return newNode;
    }

    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node; // Duplicate keys are not allowed

    node->height = 1 + fmax(getHeight(node->left), getHeight(node->right));

    int balance = getBalanceFactor(node);

    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void freeTree(struct Node* node) {
    if (node == NULL)
        return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

bool searchNode(const struct Node* node, int key) {
    if (node == NULL)
        return false;
    if (key < node->key)
        return searchNode(node->left, key);
    else if (key > node->key)
        return searchNode(node->right, key);
    else
        return true;
}
