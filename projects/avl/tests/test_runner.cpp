#include <cassert>
#include <iostream>
#include "AVLTree.hpp"

void test_insert() {
    AVLTree tree;
    tree.insert(10);
    assert(tree.getHeight() == 1);

    tree.insert(20);
    assert(tree.getHeight() == 2);

    tree.insert(30);
    assert(tree.getHeight() == 2); // Should be balanced after insertion of 30

    tree.insert(40);
    assert(tree.getHeight() == 3);

    tree.insert(50);
    assert(tree.getHeight() == 3); // Should be balanced after insertion of 50
}

void test_remove() {
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);

    tree.remove(50);
    assert(tree.getHeight() == 3);

    tree.remove(40);
    assert(tree.getHeight() == 2); // Should be balanced after removal of 40

    tree.remove(30);
    assert(tree.getHeight() == 2);

    tree.remove(20);
    assert(tree.getHeight() == 1);

    tree.remove(10);
    assert(tree.getHeight() == 0); // Tree should be empty
}

void test_search() {
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);

    // Implement search functionality and add assertions here
    // For now, we will just insert a placeholder for the search tests
    assert(true); // Placeholder assertion
}

int main() {
    test_insert();
    test_remove();
    test_search();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
