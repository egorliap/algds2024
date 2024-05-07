#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"
#define _CRT_SECURE_NO_WARNINGS
#define INITIAL_KEY 20
int main() {
    srand(time(NULL));
    rb_tree* tree = create_tree(INITIAL_KEY);
    char command[256];
    
    printf("Insert/Delete to Red-Black Tree programme.\n");
    while (1) {

        printf("\nEnter command (insert, delete, print, bh (black height), test insert, exit): ");
        fgets(command, 256, stdin);
        command[strlen(command) - 1] = '\0';

        if (strcmp(command, "insert") == 0) {
            insert_dialog(&tree);
        }
        else if (strcmp(command, "delete") == 0) {
            delete_dialog(&tree);
        }
        else if (strcmp(command, "print") == 0) {
            print_dialog(tree);
        }
        else if (strcmp(command, "tree") == 0) {
            tree_dialog(&tree);
        }
        else if (strcmp(command, "bh") == 0) {
            sums_dialog(tree);
        }
        else if (strcmp(command, "test insert") == 0) {
            test_insert(tree);
        }
        else if (strcmp(command, "test delete") == 0) {
            test_delete(tree);
        }
        else if (strcmp(command, "exit") == 0) {
            destroy_tree(tree);
            break;
        }
        else {
            printf("Invalid command.\n");
        }

    }

    printf("Program terminated.\n");
    return 0;
}