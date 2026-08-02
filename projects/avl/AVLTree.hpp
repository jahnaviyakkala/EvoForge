#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <iostream>
#include <memory>

struct Node {
    int key;
    int height;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    Node(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    void insert(int value);
    bool remove(int value);
    int getHeight() const;
    std::shared_ptr<Node> getRoot() const;

private:
    std::shared_ptr<Node> root;

    std::shared_ptr<Node> rotateRight(std::shared_ptr<Node> y);
    std::shared_ptr<Node> rotateLeft(std::shared_ptr<Node> x);
    int getBalanceFactor(const std::shared_ptr<Node>& node) const;
    std::shared_ptr<Node> balance(std::shared_ptr<Node> node);
    std::shared_ptr<Node> insertRecursive(std::shared_ptr<Node> node, int value);
    std::shared_ptr<Node> removeRecursive(std::shared_ptr<Node> node, int value);
    std::shared_ptr<Node> minValueNode(const std::shared_ptr<Node>& node) const;
    int getHeight(const std::shared_ptr<Node>& node) const;
};

#endif // AVLTREE_HPP
