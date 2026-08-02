#include <stdbool.h>
#include "avl.h"
#include <stdio.h>
#include <string.h>

struct Node* root = NULL;

void insert(int key) {
    root = insertNode(root, key);
}

bool search(int key) {
    return searchNode(root, key);
}

void freeMemory() {
    freeTree(root);
}

int main() {
    char command[20];
    int value;

    while (1) {
        printf("Enter command (insert <value>, delete <value>, search <value>, height, isBalanced, exit): ");
        scanf("%s", command);

        if (strcmp(command, "exit") == 0) {
            freeMemory();
            break;
        } else if (strcmp(command, "insert") == 0) {
            scanf("%d", &value);
            insert(value);
        } else if (strcmp(command, "delete") == 0) {
            scanf("%d", &value);
            // Implement delete functionality
        } else if (strcmp(command, "search") == 0) {
            scanf("%d", &value);
            if (search(value))
                printf("Value %d found\n", value);
            else
                printf("Value %d not found\n", value);
        } else if (strcmp(command, "height") == 0) {
            // Implement height functionality
        } else if (strcmp(command, "isBalanced") == 0) {
            // Implement isBalanced functionality
        } else {
            printf("Invalid command\n");
        }
    }

    return 0;
}
