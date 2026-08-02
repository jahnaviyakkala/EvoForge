#ifndef AVLTREE_H
#define AVLTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};

int getHeight(const struct Node* node);
int getBalanceFactor(const struct Node* node);
struct Node* rotateRight(struct Node* y);
struct Node* rotateLeft(struct Node* x);
struct Node* insertNode(struct Node* node, int key);
void freeTree(struct Node* node);
bool searchNode(const struct Node* node, int key);

#endif // AVLTREE_H
