#include <memory>
#include "AVLTree.hpp"
#include <iostream>
#include <string>

void displayMenu() {
    std::cout << "AVL Tree Operations:\n";
    std::cout << "1. Insert a new element (insert <value>)\n";
    std::cout << "2. Delete an existing element (delete <value>)\n";
    std::cout << "3. Search for an element (search <value>)\n";
    std::cout << "4. Display the current state of the tree (display)\n";
    std::cout << "5. Exit\n";
}

void displayTree(const std::shared_ptr<Node>& node, int level) {
    if (node != nullptr) {
        displayTree(node->right, level + 1);
        for (int i = 0; i < level; ++i)
            std::cout << "   ";
        std::cout << node->key << "(" << node->height << ")" << std::endl;
        displayTree(node->left, level + 1);
    }
}

int main() {
    AVLTree avlTree;
    std::string command;

    while (true) {
        displayMenu();
        std::cout << "Enter command: ";
        std::getline(std::cin, command);

        if (command == "exit") {
            break;
        } else if (command.substr(0, 6) == "insert") {
            int value = std::stoi(command.substr(7));
            avlTree.insert(value);
            std::cout << "Inserted " << value << ". Height of tree: " << avlTree.getHeight() << std::endl;
        } else if (command.substr(0, 6) == "delete") {
            int value = std::stoi(command.substr(7));
            avlTree.remove(value);
            std::cout << "Deleted " << value << ". Height of tree: " << avlTree.getHeight() << std::endl;
        } else if (command.substr(0, 6) == "search") {
            int value = std::stoi(command.substr(7));
            // Implement search functionality
            std::cout << "Search for " << value << ".\n";
        } else if (command == "display") {
            displayTree(avlTree.getRoot(), 0);
        } else {
            std::cout << "Invalid command. Please try again.\n";
        }
    }

    return 0;
}
