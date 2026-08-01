#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    void insert(int data);
    bool remove(int data);
    Node* search(int data) const;
    void inorderTraversal() const;

private:
    Node* root;
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    int getHeight(Node* N) const;
    int getBalanceFactor(Node* N) const;
    Node* insertRecursive(Node* node, int data);
    Node* removeRecursive(Node* root, int data);
    Node* minValueNode(Node* node) const;
    void inorderRecursive(Node* node) const;
};

#endif // AVL_TREE_HPP
