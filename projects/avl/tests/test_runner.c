#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "../avl.h"

void test_insert() {
    struct Node* root = NULL;
    root = insertNode(root, 10);
    assert(getHeight(root) == 1);
    assert(searchNode(root, 10) == true);

    root = insertNode(root, 20);
    assert(getHeight(root) == 2);
    assert(searchNode(root, 20) == true);

    root = insertNode(root, 30);
    assert(getHeight(root) == 2);
    assert(searchNode(root, 30) == true);

    freeTree(root);
}

void test_insert_duplicates() {
    struct Node* root = NULL;
    root = insertNode(root, 10);
    assert(getHeight(root) == 1);
    assert(searchNode(root, 10) == true);

    root = insertNode(root, 10); // Duplicate key
    assert(getHeight(root) == 1);
    assert(searchNode(root, 10) == true);

    freeTree(root);
}

void test_search() {
    struct Node* root = NULL;
    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);

    assert(searchNode(root, 10) == true);
    assert(searchNode(root, 20) == true);
    assert(searchNode(root, 30) == true);
    assert(searchNode(root, 40) == false);

    freeTree(root);
}

void test_delete() {
    // TODO: Implement delete functionality and tests
}

void test_height() {
    struct Node* root = NULL;
    root = insertNode(root, 10);
    assert(getHeight(root) == 1);

    root = insertNode(root, 20);
    assert(getHeight(root) == 2);

    root = insertNode(root, 30);
    assert(getHeight(root) == 2);

    freeTree(root);
}

void test_isBalanced() {
    // TODO: Implement isBalanced functionality and tests
}

int main() {
    test_insert();
    test_insert_duplicates();
    test_search();
    test_delete(); // Placeholder for future implementation
    test_height();
    test_isBalanced(); // Placeholder for future implementation

    printf("All tests passed!\n");
    return 0;
}
