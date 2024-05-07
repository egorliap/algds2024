#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header.h"

int is_in_tree(rb_tree* tree,int key) {
	if (tree != NULL) {
		if (key == tree->key) {
			return 0;
		}
		else if (key <= tree->key) {
			return is_in_tree(tree->left, key);
		}
		else {
			return is_in_tree(tree->right, key);
		}
	}
	else {
		return 1;
	}
}

int check_all_heights(rb_tree* tree) {
	if (tree != NULL) {
		int sl = 0,sr = 0;
		count_black_h(tree,&sl,&sr);
		if (sl != sr) {
			printf("\nERROR: disbalance at node with key %d", tree->key);
			return 1;
		}
		else {
			return check_all_heights(tree->right) + check_all_heights(tree->left);
		}
	}else{
		return 0;
	}
}

void test_insert(rb_tree* tree) {
	int i = 0;
	int ret;
	while (i<10000) {
		int key = rand() % 1000;
		add_node(&tree, key);

		ret = is_in_tree(tree, key);
		if (ret == 1) {
			return;
		}
		ret = check_all_heights(tree);
		if (ret > 0) {
			return;
		}
		
		i++;
	}
	printf("\nInsert is tested successfully");
	printf("\nBalance is tested successfully, no disbalance detected");
}
void test_delete(rb_tree* tree) {
	int ret;
	char key_str[256];
	int i = 0, key = 0;

	printf("\nEnter key to test delete: ");
	fgets(key_str, 256, stdin);
	key_str[strlen(key_str) - 1] = '\0';

	key = atoi(key_str);
	
	delete_node(tree, NULL, key);
	check_all_heights(tree);
	printf("\nDelete is tested successfully");
}