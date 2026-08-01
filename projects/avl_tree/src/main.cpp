#include <iostream>
#include <limits>
#include "avl_tree.hpp"

int main() {
    AVLTree avl;
    std::string command;
    int data;

    while (true) {
        std::cout << "\nAVL Tree Operations:\n";
        std::cout << "1. Insert\n2. Delete\n3. Search\n4. Inorder Traversal\n5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> command;

        if (command == "exit") {
            break;
        } else if (command == "insert" || command == "delete" || command == "search") {
            std::cout << "Enter the integer value: ";
            std::cin >> data;

            if (!std::cin) {
                std::cerr << "Invalid input. Please enter an integer.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (command == "insert") {
                avl.insert(data);
                std::cout << "Element inserted successfully.\n";
            } else if (command == "delete") {
                bool result = avl.remove(data);
                if (result)
                    std::cout << "Element deleted successfully.\n";
                else
                    std::cout << "Element not found.\n";
            } else if (command == "search") {
                Node* node = avl.search(data);
                if (node != nullptr)
                    std::cout << "Element found: " << node->data << "\n";
                else
                    std::cout << "Element not found.\n";
            }
        } else if (command == "inorder") {
            std::cout << "Inorder Traversal of the AVL Tree:\n";
            avl.inorderTraversal();
            std::cout << "\n";
        } else {
            std::cerr << "Invalid command. Please try again.\n";
        }
    }

    return 0;
}
