#include <iostream>
#include "avl_tree.hpp"

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() {
    // Implement destructor to clean up the tree if needed
}

int AVLTree::getHeight(Node* N) const {
    if (N == nullptr)
        return 0;
    return N->height;
}

int AVLTree::getBalanceFactor(Node* N) const {
    if (N == nullptr)
        return 0;
    return getHeight(N->left) - getHeight(N->right);
}

Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    // Return new root
    return x;
}

Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    // Return new root
    return y;
}

Node* AVLTree::insertRecursive(Node* node, int data) {
    if (node == nullptr)
        return (new Node(data));

    if (data < node->data)
        node->left = insertRecursive(node->left, data);
    else if (data > node->data)
        node->right = insertRecursive(node->right, data);
    else // Duplicate keys are not allowed in BST
        return node;

    // Update height of this ancestor node
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    // Get the balance factor of this ancestor node to check whether
    // this node became unbalanced
    int balance = getBalanceFactor(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && data < node->left->data)
        return rotateRight(node);

    // Right Right Case
    if (balance < -1 && data > node->right->data)
        return rotateLeft(node);

    // Left Right Case
    if (balance > 1 && data > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left Case
    if (balance < -1 && data < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    // return the (unchanged) node pointer
    return node;
}

void AVLTree::insert(int data) {
    root = insertRecursive(root, data);
}

Node* AVLTree::minValueNode(Node* node) const {
    Node* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != nullptr)
        current = current->left;

    return current;
}

Node* AVLTree::removeRecursive(Node* root, int data) {
    // Perform standard BST delete
    if (root == nullptr)
        return root;

    if (data < root->data)
        root->left = removeRecursive(root->left, data);
    else if (data > root->data)
        root->right = removeRecursive(root->right, data);
    else {
        // node with only one child or no child
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node* temp = root->left ? root->left : root->right;

            // No child case
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else // One child case
                *root = *temp; // Copy the contents of the non-empty child

            delete temp;
        } else {
            // node with two children: Get the inorder successor (smallest in the right subtree)
            Node* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->data = temp->data;

            // Delete the inorder successor
            root->right = removeRecursive(root->right, temp->data);
        }
    }

    // If the tree had only one node then return
    if (root == nullptr)
        return root;

    // Update height of this ancestor node
    root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

    // Get the balance factor of this ancestor node to check whether
    // this node became unbalanced
    int balance = getBalanceFactor(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalanceFactor(root->left) >= 0)
        return rotateRight(root);

    // Left Right Case
    if (balance > 1 && getBalanceFactor(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Right Right Case
    if (balance < -1 && getBalanceFactor(root->right) <= 0)
        return rotateLeft(root);

    // Right Left Case
    if (balance < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

bool AVLTree::remove(int data) {
    if (search(data) == nullptr) {
        return false;
    }
    root = removeRecursive(root, data);
    return true;
}

Node* AVLTree::search(int data) const {
    Node* current = root;

    while (current != nullptr) {
        if (data < current->data)
            current = current->left;
        else if (data > current->data)
            current = current->right;
        else
            return current;
    }

    return nullptr; // Element not found
}

void AVLTree::inorderRecursive(Node* node) const {
    if (node != nullptr) {
        inorderRecursive(node->left);
        std::cout << node->data << " ";
        inorderRecursive(node->right);
    }
}

void AVLTree::inorderTraversal() const {
    inorderRecursive(root);
}
