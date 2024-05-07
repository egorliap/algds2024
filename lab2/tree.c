#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "header.h"

rb_tree* create_tree(int key) {
	rb_tree* t = (rb_tree*)malloc(sizeof(rb_tree));
	t->key = key;
	t->type = BLACK;
	t->head = 1;
	t->right = t->left = NULL;
	return t;
}


void rotate_left(rb_tree* parent) {
	rb_tree* child = parent->right;
	rb_tree* between_xy;
	if (child != NULL) {
		between_xy = child->left;
		
		child->left = parent;
		parent->right = between_xy;

		child->type = parent->type;
		parent->type = RED;
		if (parent->head) {
			parent->head = 0;
			child->head = 1;
		}
	}
}
void rotate_right(rb_tree* parent) {
	rb_tree* child = parent->left;
	rb_tree* between_xy;
	if (child != NULL) {
		between_xy = child->right;

		child->right = parent;
		parent->left = between_xy;

		child->type = parent->type;
		parent->type = RED;
		if (parent->head) {
			parent->head = 0;
			child->head = 1;
		}
	}
}

void big_rotate_left(rb_tree* g) {
	rb_tree* p = g->left;
	rb_tree* x = p->left;
	rb_tree* u = g->right;

	rb_tree* between_pg = p->right;

	p->right = g;
	g->left = between_pg;
	p->type = g->type;

	g->type = RED;

	if (g->head) {
		g->head = 0;
		p->head = 1;
	}
}
void big_rotate_right(rb_tree* g) {
	rb_tree* p = g->right;
	rb_tree* x = p->right;
	rb_tree* u = g->left;

	rb_tree* between_pg = p->left;

	p->left = g;
	g->right = between_pg;
	p->type = g->type;
	g->type = RED;
	if (g->head) {
		g->head = 0;
		p->head = 1;
	}
}

void type_swap(rb_tree* parent) {
	rb_tree* left_child = parent->left;
	rb_tree* right_child = parent->right;
	if (right_child != NULL && left_child != NULL && parent->type == BLACK && left_child->type == RED && right_child->type == RED) {
		parent->type = RED;
		left_child->type = right_child->type = BLACK;
		if (parent->head == 1) {
			parent->type = BLACK;
		}
	}
}


rb_tree* balance(rb_tree* G, int father_is_left, int child_is_left) {
	rb_tree* F, * X, * U, * ret_node = G;
	if (!father_is_left) {
		F = G->right;
		U = G->left;
	}
	else {
		F = G->left;
		U = G->right;

	}
	if (!child_is_left) {
		X = F->right;
	}
	else {
		X = F->left;
	}

	if (U != NULL && U->type == RED) {
		type_swap(G);
		return G;
	}
	if (father_is_left != child_is_left && (U == NULL || U->type == BLACK)) {
		if (father_is_left) {
			rotate_left(F);
			G->left = X;
			return balance(G, 1, 1);
		}
		else {
			rotate_right(F);
			G->right = X;
			return balance(G, 0, 0);
		}
	}
	else if (father_is_left == child_is_left && (U == NULL || U->type == BLACK)) {
		if (father_is_left) {
			big_rotate_left(G);
			return F;
		}
		else {
			big_rotate_right(G);
			return F;
		}
	}
	else {
		return G;
	}
}

rb_tree* check_balance_insert(rb_tree* G) {
	if (G == NULL) {
		return NULL;
	}
	rb_tree* r = G->right;
	rb_tree* l = G->left;
	if (r != NULL && r->type == RED) {
		rb_tree* rr = r->right;
		rb_tree* rl = r->left;


		if (rr != NULL && rr->type == RED) {
			return balance(G, 0, 0);
		}
		else if (rl != NULL && rl->type == RED) {
			return balance(G, 0, 1);
		}

	}
	if (l != NULL && l->type == RED) {
		rb_tree* lr = l->right;
		rb_tree* ll = l->left;

		if (lr != NULL && lr->type == RED) {
			return balance(G, 1, 0);
		}
		else if (ll != NULL && ll->type == RED) {
			return balance(G, 1, 1);
		}

	}
	return G;
}




int add_node(rb_tree** tree,int key) {
	int ret;
	if ((*tree) == NULL || tree == NULL) {
		return 1;
	}
	else {
		if (key <= (*tree)->key ) {
			ret = add_node(&((*tree)->left), key);
			if (ret == 1) {
				rb_tree* new_node = malloc(sizeof(rb_tree));
				new_node->key = key;
				new_node->left = NULL;
				new_node->right = NULL;
				new_node->head = 0;
				new_node->type = RED;
				(*tree)->left = new_node;

			}
		}
		else {
			ret = add_node(&((*tree)->right), key);
			if (ret == 1) {
				rb_tree* new_node = malloc(sizeof(rb_tree));
				new_node->key = key;
				new_node->left = NULL;
				new_node->right = NULL;
				new_node->head = 0;
				new_node->type = RED;
				(*tree)->right = new_node;
			}
		}
	*tree = check_balance_insert((*tree));
	(*tree)->left = check_balance_insert((*tree)->left);
	(*tree)->right = check_balance_insert((*tree)->right);	
	}

	return 0;

}

rb_tree** find_max(rb_tree* node) {
	rb_tree* parent = node;
	rb_tree** ans = malloc(sizeof(rb_tree*) * 2);

	if (parent->right == NULL) {
		ans[0] = NULL;
		ans[1] = parent;
		return ans;
	}
	else {

		rb_tree* child = parent->right;
		while (child->right!=NULL) {
			child = child->right;
			parent = parent->right;
		}
		ans[0] = parent;
		ans[1] = child;
		return ans;
	}
}
rb_tree** find_min(rb_tree* node) {
	rb_tree* parent = node;
	rb_tree** ans = malloc(sizeof(rb_tree*) * 2);

	if (parent->left == NULL) {
		ans[0] = NULL;
		ans[1] = parent;
		return ans;
	}
	else {

		rb_tree* child = parent->left;
		while (child->left != NULL) {
			child = child->left;
			parent = parent->left;
		}
		ans[0] = parent;
		ans[1] = child;
		return ans;
	}
}

rb_tree* check_balance_delete(rb_tree* G, rb_tree* rem_F, int del_on_left) {

	if (rem_F == NULL) {
		G->type = BLACK;
		if (del_on_left) {
			G->left = NULL;
		}
		else {
			G->right = NULL;

		}

		return G;
	}


	rb_tree* g_child_left = rem_F->left;
	rb_tree* g_child_right = rem_F->right;



	if (G->type == RED && rem_F->type == BLACK) {


		if ((g_child_left == NULL || g_child_left->type == BLACK) && (g_child_right == NULL || g_child_right->type == BLACK)) {
			G->type = BLACK;
			rem_F->type = RED;
			if (del_on_left) {
				G->left = NULL;
			}
			else {
				G->right = NULL;

			}
			return G;
		}


		if (del_on_left) {
			if (g_child_right != NULL && g_child_right->type == RED) {

				big_rotate_right(G);
				g_child_right->type = BLACK;

				G->left = NULL;
				G->type = BLACK;

				return rem_F;

			}
			else if ((g_child_right == NULL || g_child_right->type == BLACK) && (g_child_left != NULL && g_child_left->type == RED)) {
				rotate_right(rem_F);
				G->right = g_child_left;
				big_rotate_right(G);
				G->left = NULL;
				g_child_left->type = BLACK;
				return g_child_left;
			}
		}
		else {
			if (g_child_left != NULL && g_child_left->type == RED) {

				big_rotate_left(G);
				g_child_left->type = BLACK;
				G->type = BLACK;


				G->right = NULL;

				return rem_F;

			}
			else if ((g_child_left == NULL || g_child_left->type == BLACK) && (g_child_right != NULL && g_child_right->type == RED)) {
				rotate_left(rem_F);
				G->left = g_child_right;
				big_rotate_left(G);
				G->right = NULL;
				g_child_right->type = BLACK;
				return g_child_right;
			}
		}
	}
	else if (G->type == BLACK && rem_F->type == RED) {



		if (del_on_left) {
			if (g_child_left != NULL) {
				rb_tree* gg_child_left = g_child_left->left;
				rb_tree* gg_child_right = g_child_left->right;
				if ((gg_child_left == NULL || gg_child_left->type == BLACK) && (gg_child_right == NULL || gg_child_right->type == BLACK)) {


					big_rotate_right(G);
					G->type = BLACK;
					g_child_right->type = RED;
					G->left = NULL;

					return rem_F;
				}
				else if (((gg_child_right == NULL || gg_child_right->type == BLACK) && (gg_child_left != NULL && gg_child_left->type == RED))) {
					rotate_right(rem_F);
					G->right = g_child_left;
					big_rotate_left(G);
					G->left = NULL;

					return g_child_left;
				}

			}
		}
		else {
			if (g_child_right != NULL) {
				rb_tree* gg_child_left = g_child_right->left;
				rb_tree* gg_child_right = g_child_right->right;
				if ((gg_child_left == NULL || gg_child_left->type == BLACK) && (gg_child_right == NULL || gg_child_right->type == BLACK)) {


					big_rotate_left(G);
					G->type = BLACK;
					g_child_right->type = RED;
					G->right = NULL;

					return rem_F;
				}


				else if (((gg_child_left == NULL || gg_child_left->type == BLACK) && (gg_child_right != NULL && gg_child_right->type == RED))) {
					rotate_left(rem_F);
					G->left = g_child_right;
					big_rotate_right(G);
					G->right = NULL;

					return g_child_left;
				}
			}

		}
	}
	else if (G->type == BLACK && rem_F->type == BLACK) {

		if (del_on_left == 1) {
			if (g_child_left != NULL && g_child_left->type == RED) {
				rotate_right(rem_F);
				G->right = g_child_left;
				big_rotate_right(G);
				G->left = NULL;
				g_child_left->type = BLACK;
				rem_F->type = BLACK;
				G->type = BLACK;
				return g_child_left;
			}
			else if (g_child_left == NULL || g_child_right->type == BLACK) {
				rem_F->type = RED;
				G->left = NULL;
				
				return G;
			}
		}
		else {
			if (g_child_right != NULL && g_child_right->type == RED) {
				rotate_left(rem_F);
				G->left = g_child_right;
				big_rotate_left(G);
				G->right = NULL;
				g_child_right->type = BLACK;
				rem_F->type = BLACK;
				G->type = BLACK;

				return g_child_right;
			}

			else if (g_child_right == NULL || g_child_right->type == BLACK) {
				rem_F->type = RED;
				G->right = NULL;
				
				return G;

			}
		}
	}
}




	


rb_tree* delete_variants(rb_tree* del) {
	if (del->type == RED) {




		if (del->left != NULL && del->right != NULL) {
			rb_tree** s = find_min(del->right);
			rb_tree* gg = del->right;

			if (s[0] == NULL) {
				del->type = gg->type;
				gg->type = RED;

				gg->left = del->left;
				del->right = gg->right;
				del->left = NULL;
				gg->right = del;
				rb_tree* ans = delete_variants(del);
				if (ans != 1) {
					gg->right = ans;
					
				}
				else {
					return check_balance_delete(gg, gg->left, 0);
				}
				
				return gg;
			}
			else {
				rb_tree* p = s[1],*g = s[0];
				del->type = p->type;
				p->type = RED;

				p->left = del->left;
				del->right = p->right;
				del->left = NULL;
				g->left = del;
				p->right = gg;
				rb_tree* prev_g = NULL;
				if (gg != g) {
					prev_g = gg;
					while (prev_g->left != g) {
						prev_g = prev_g->left;
					}
					
				}
				
				rb_tree* ans = delete_variants(del);
				if(ans!= 1){
					g->left = ans;
					
				}
				else {
					if (gg != g) {
						
						prev_g->left = check_balance_delete(g, g->right, 1);

					}
					else {
						p->right = check_balance_delete(g, g->right, 1);
					}
				}
				return p;
			}
		}




		else if(del->left == NULL && del->right == NULL) {
			free(del);
			return NULL;
		}
		else {
			printf("\nBALANCE ERROR");
		}
	}
	else {




		if (del->left != NULL && del->right != NULL) {
			rb_tree** s = find_min(del->right);
			rb_tree* gg = del->right;

			if (s[0] == NULL) {
				del->type = gg->type;
				gg->type = BLACK;

				gg->left = del->left;
				del->right = gg->right;
				del->left = NULL;
				gg->right = del;
				rb_tree* ans = delete_variants(del);
				if (ans != 1) {
					gg->right = ans;

				}
				else {
					return check_balance_delete(gg, gg->left, 0);
				}

				return gg;
			}



			else {
				rb_tree* p = s[1], * g = s[0];
				del->type = p->type;
				p->type = BLACK;

				p->left = del->left;
				del->right = p->right;
				del->left = NULL;
				g->left = del;
				p->right = gg;
				rb_tree* prev_g = NULL;
				if (gg != g) {
					prev_g = gg;
					while (prev_g->left != g) {
						prev_g = prev_g->left;
					}

				}

				rb_tree* ans = delete_variants(del);
				if (ans != 1) {
					g->left = ans;

				}
				else {
					if (gg != g) {

						prev_g->left = check_balance_delete(g, g->right, 1);

					}
					else {
						p->right = check_balance_delete(g, g->right, 1);
					}
				}
				return p;
				
			}
		}




		else if (del->left == NULL && del->right == NULL) {
			// the most complicated case - we have to balance after this case

			return 1;
		}
		else {
			if (del->right != NULL) {
				rb_tree* only_child = del->right;
				only_child->type = BLACK;
				free(del);
				return only_child;
			}
			else {
				rb_tree* only_child = del->left;
				only_child->type = BLACK;
				free(del);
				return only_child;
			}
		}
	}
}

int delete_node(rb_tree** tree, rb_tree** g_tree, int key)
{	
	rb_tree* on_del;
	int ret;
	if (*tree == NULL) {
		return 1;
	}
	else if ((*tree)->key == key) {
		return 2;
	}
	else {
		if ((*tree)->key >= key) {
			ret = delete_node(&((*tree)->left),tree, key);
			if (ret == 2) {
				on_del = (*tree)->left;
				rb_tree* ans = delete_variants(on_del);
				if (ans != 1) {
					(*tree)->left = ans;
					
				}
				else {
					//здесь разбираются 6 ситуаций в случае удаления черного ребенка tree с 0 детей
					if ((*g_tree)->left == (*tree)) {


						(*g_tree)->left = check_balance_delete((*tree), (*tree)->right, 1);

					}
					else {
						(*g_tree)->right = check_balance_delete((*tree), (*tree)->right, 1);
					}
				

					free(on_del);

				}
				ret = 0;
			}
			else if(ret == 1) {
				printf("\nNOT FOUND");
				return;
			}
		}
		else {
			ret = delete_node(&((*tree)->right),tree, key);
			if (ret == 2) {
				on_del = (*tree)->right;
				rb_tree* ans = delete_variants(on_del);
				if (ans != 1) {
					(*tree)->right = ans;

				}
				else {
					//здесь разбираются 6 ситуаций в случае удаления черного ребенка tree с 0 детей
					if ((*g_tree)->left == (*tree)) {
						(*g_tree)->left = check_balance_delete((*tree), (*tree)->left, 0);
					}
					else {
						(*g_tree)->right = check_balance_delete((*tree), (*tree)->left, 0);
					}
			
					free(on_del);

				}
				ret = 0;
			}
			else if (ret == 1) {
				printf("\nNOT FOUND");
				return;
			}
		}
	}
	return 0;
}


void destroy_tree(rb_tree* t) {
	if (t != NULL)
	{
		destroy_tree(t->left);
		destroy_tree(t->right);
		free(t);
	}
};

char s[20][800];


int _print_t(rb_tree* tree, int is_left, int offset, int depth)
{

	char b[20];
	int width = 8;

	if (tree == NULL) return 0;


	
	int left = _print_t(tree->left, 1, offset+2, depth + 1, s);
	int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);

	sprintf(b, "(%d %s)", tree->key, tree->type ? "B" : "R");
	width = strlen(b);
	for (int i = 0; i < width; i++) {
		if (b[i] != '\0') {
			s[2 * depth][offset + left + i] = b[i];
		}
	}
	if (depth && is_left) {

		for (int i = 0; i < width + right; i++)
			s[2 * depth - 1][offset + left + width / 2 + i] = '-';

		s[2 * depth - 1][offset + left + width / 2] = '+';
		s[2 * depth - 1][offset + left + width + right + width / 2] = '+';

	}
	else if (depth && !is_left) {

		for (int i = 0; i < left + width; i++)
			s[2 * depth - 1][offset - width / 2 + i] = '-';

		s[2 * depth - 1][offset + left + width / 2] = '+';
		s[2 * depth - 1][offset - width / 2 - 1] = '+';
	}
	return left + width + right;
}



void print_tree(rb_tree* tree)
{

	for (int i = 0; i < 20; i++)
		sprintf(s[i], "%110s", " ");

	_print_t(tree, 0, 5, 0, s);
	for (int i = 0; i < 20; i++) {
		s[i][strlen(s[i]) - 1] = '\0';

		printf("%s\n", s[i]);
	}
	

}


int count_bh_left(rb_tree *tree){
	int ans = 0;
	while (tree != NULL) {
		if (tree->type == BLACK) {
			ans++;
		}
		tree = tree->left;
	}
	return ans;
}
int count_bh_right(rb_tree* tree) {
	int ans = 0;
	while (tree != NULL) {
		if (tree->type == BLACK) {
			ans++;
		}
		tree = tree->right;
	}
	return ans;
}
void count_black_h(rb_tree* tree, int* sum_l, int* sum_r) {
	*sum_l = count_bh_left(tree->left);
	*sum_r  = count_bh_right(tree->right);
}

