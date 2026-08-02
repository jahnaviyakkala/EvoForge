#include <algorithm>
#include <memory>
#include "AVLTree.hpp"

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() {}

int AVLTree::getHeight(const std::shared_ptr<Node>& node) const {
    if (node == nullptr)
        return 0;
    return node->height;
}

std::shared_ptr<Node> AVLTree::rotateRight(std::shared_ptr<Node> y) {
    std::shared_ptr<Node> x = y->left;
    std::shared_ptr<Node> T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    // Return new root
    return x;
}

std::shared_ptr<Node> AVLTree::rotateLeft(std::shared_ptr<Node> x) {
    std::shared_ptr<Node> y = x->right;
    std::shared_ptr<Node> T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    // Return new root
    return y;
}

int AVLTree::getBalanceFactor(const std::shared_ptr<Node>& node) const {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

std::shared_ptr<Node> AVLTree::insertRecursive(std::shared_ptr<Node> node, int value) {
    // Perform the normal BST insertion
    if (node == nullptr)
        return std::make_shared<Node>(value);

    if (value < node->key)
        node->left = insertRecursive(node->left, value);
    else if (value > node->key)
        node->right = insertRecursive(node->right, value);
    else // Duplicate keys are not allowed in BST
        return node;

    // Update height of this ancestor node
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    // Get the balance factor of this ancestor node to check whether
    // this node became unbalanced
    int balance = getBalanceFactor(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && value < node->left->key)
        return rotateRight(node);

    // Right Right Case
    if (balance < -1 && value > node->right->key)
        return rotateLeft(node);

    // Left Right Case
    if (balance > 1 && value > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left Case
    if (balance < -1 && value < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    // return the (unchanged) node pointer
    return node;
}

void AVLTree::insert(int value) {
    root = insertRecursive(root, value);
}

std::shared_ptr<Node> AVLTree::removeRecursive(std::shared_ptr<Node> node, int value) {
    // Perform standard BST delete
    if (node == nullptr)
        return node;

    if (value < node->key)
        node->left = removeRecursive(node->left, value);
    else if (value > node->key)
        node->right = removeRecursive(node->right, value);
    else {
        // Node with only one child or no child
        if ((node->left == nullptr) || (node->right == nullptr)) {
            std::shared_ptr<Node> temp = (node->left != nullptr) ? node->left : node->right;

            // No child case
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else { // One child case
                *node = *temp; // Copy the contents of the non-empty child
            }
        } else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            std::shared_ptr<Node> temp = minValueNode(node->right);

            // Copy the inorder successor's data to this node
            node->key = temp->key;

            // Delete the inorder successor
            node->right = removeRecursive(node->right, temp->key);
        }
    }

    // If the tree had only one node then return
    if (node == nullptr)
        return node;

    // Update height of this ancestor node
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    // Get the balance factor of this ancestor node to check whether
    // this node became unbalanced
    int balance = getBalanceFactor(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalanceFactor(node->left) >= 0)
        return rotateRight(node);

    // Left Right Case
    if (balance > 1 && getBalanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Right Case
    if (balance < -1 && getBalanceFactor(node->right) <= 0)
        return rotateLeft(node);

    // Right Left Case
    if (balance < -1 && getBalanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

bool AVLTree::remove(int value) {
    root = removeRecursive(root, value);
    return true; // Assuming removal is always successful for simplicity
}

std::shared_ptr<Node> AVLTree::minValueNode(const std::shared_ptr<Node>& node) const {
    std::shared_ptr<Node> current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != nullptr)
        current = current->left;

    return current;
}

int AVLTree::getHeight() const {
    return getHeight(root);
}

std::shared_ptr<Node> AVLTree::getRoot() const {
    return root;
}
