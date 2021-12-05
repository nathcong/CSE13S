#include "node.h"
#include "bst.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

uint64_t branches;

Node *bst_create(void) {
	
}

uint32_t bst_height(Node *root) {
	if (root) {
		return 1 + max(bst_height(root->left), bst_height(root->right));	
	}
	else {
		return 0;
	}
}

uint32_t bst_size(Node *root) {
	
}

Node *bst_find(Node *root, char *oldspeak) {
	if (root) {
		if (strcmp(root->oldspeak) > strcmp(oldspeak)) {
			return bst_find(root->left, oldpseak);
		}	
		if (strcmp(root->oldspeak) < strcmp(oldspeak)) {
			return bst_find(root->right, oldspeak);
		}
	}
	else {
		Node *null = NULL;
		return null;
	}
	return root;
}

Node *bst_insert(Node *root, char *oldspeak, char *newspeak) {
	if (root && bst_find(root, oldspeak) != NULL) {
		if (strcmp(root->oldspeak) > strcmp(oldspeak)) {
                        root->left = bst_insert(root->left, oldspeak, newspeak);
                }
                if (strcmp(root->oldspeak) < strcmp(oldspeak)) {
                        root->right = bst_insert(root->right, oldspeak, newspeak);
                }
	}
	else {
		Node *null = NULL;
		return null;
	}
	return root;
}

void bst_print(Node *root) {
	if (root) {
		node_print(root);
		bst_print(root->left);
		bst_print(root->right);
	}
}

void bst_delete(Node **root) {
	if (*root) {
		bst_delete(&(*root)->left);
		bst_delete(&(*root)->right);
		node_delete(root);
	}
}

