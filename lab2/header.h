#pragma once
typedef enum {
	RED,
	BLACK
}node_type;

typedef struct {
	node_type type;
	int key;
	int head;
	int height;
	struct rb_tree* left;
	struct rb_tree* right;
}rb_tree;


rb_tree* create_tree(int key);
void destroy_tree(rb_tree* tree);

void print_dialog(rb_tree* tree);
void print_tree(rb_tree* t);


void count_black_h(rb_tree* tree, int* sum_l, int* sum_r);
void sums_dialog(rb_tree* tree);

void tree_dialog(rb_tree** tree);

void insert_dialog(rb_tree** tree);
int add_node(rb_tree** tree, int key);

void delete_dialog(rb_tree** tree);
int delete_node(rb_tree** tree, rb_tree* g_tree, int key);

void test_insert(rb_tree* tree);
void test_delete(rb_tree* tree);