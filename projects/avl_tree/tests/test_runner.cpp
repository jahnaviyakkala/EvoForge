#include <cassert>
#include <iostream>
#include <sstream>
#include "avl_tree.hpp"

void test_insert() {
    AVLTree avl;
    avl.insert(10);
    assert(avl.search(10) != nullptr);

    avl.insert(20);
    assert(avl.search(20) != nullptr);

    avl.insert(30);
    assert(avl.search(30) != nullptr);
}

void test_remove() {
    AVLTree avl;
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);

    assert(avl.remove(20));
    assert(avl.search(20) == nullptr);

    assert(!avl.remove(40)); // Attempt to remove a non-existent element
}

void test_search() {
    AVLTree avl;
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);

    assert(avl.search(10) != nullptr);
    assert(avl.search(20) != nullptr);
    assert(avl.search(30) != nullptr);
    assert(avl.search(40) == nullptr); // Search for a non-existent element
}

void test_inorder_traversal() {
    AVLTree avl;
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);

    std::ostringstream oss;
    std::streambuf* old_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    avl.inorderTraversal();

    std::cout.rdbuf(old_cout_streambuf);
    assert(oss.str() == "10 20 30 ");
}

int main() {
    test_insert();
    test_remove();
    test_search();
    test_inorder_traversal();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
