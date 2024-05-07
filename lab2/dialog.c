#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "header.h"


void insert_dialog(rb_tree** tree) {
    char key_str[256];
    int i = 0,key=0;

    printf("\nEnter key: ");
    fgets(key_str, 256, stdin);
    key_str[strlen(key_str) - 1] = '\0';
    
    key = atoi(key_str);
    if (key == 0) {
        char ans[256];
        printf("\nAre you sure to input 0? (y/n): ");
        fgets(ans, 256, stdin);
        ans[strlen(ans) - 1] = '\0';
        if (strcmp(ans, "n") == 0) {
            printf("\nTry again");
            return insert_dialog(tree);
        }
    }
    add_node(tree,key);
 
}

void delete_dialog(rb_tree** tree) {
    char key_str[256];
    int i = 0, key = 0;

    printf("\nEnter key: ");
    fgets(key_str, 256, stdin);
    key_str[strlen(key_str) - 1] = '\0';

    key = atoi(key_str);
    if (key == 0) {
        char ans[256];
        printf("\nAre you sure to input 0? (y/n): ");
        fgets(ans, 256, stdin);
        ans[strlen(ans) - 1] = '\0';
        if (strcmp(ans, "n") == 0) {
            printf("\nTry again");
            return delete_dialog(tree);
        }
    }
    delete_node(tree, tree,key);
}


void print_dialog(rb_tree* tree) {

    print_tree(tree);
}
void tree_dialog(rb_tree** tree) {
    add_node(tree, 10);
    add_node(tree, 25);
    add_node(tree, 4);
    add_node(tree, 16);
    add_node(tree, 23);
    add_node(tree, 30);
    add_node(tree, 2);
    add_node(tree, 5);
    add_node(tree, 14);
    add_node(tree, 17);
    add_node(tree, 3);
    add_node(tree, 12);
    add_node(tree, 15);
    add_node(tree, 19);
    add_node(tree, 11);   
}

void sums_dialog(rb_tree* tree) {
    int left_sum = 0, right_sum = 0;
    count_black_h(tree, &left_sum, &right_sum);
    printf("\nleft sum: %d, right sum %d", left_sum, right_sum);
}