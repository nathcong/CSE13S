#include "node.h"
#include "bst.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

uint64_t branches;

static uint32_t size;
static uint32_t height;

Node *bst_create(void) {
    return NULL;
}

uint32_t bst_height(Node *root) {
    height = 0;
    if (root) {
        height = 1 + max(bst_height(root->left), bst_height(root->right));
    }
    return height;
}

uint32_t bst_size(Node *root) {
    size = 0;
    if (root) {
        size = 1 + bst_size(root->left) + bst_size(root->right);
    }
    return size;
}

Node *bst_find(Node *root, char *oldspeak) {
    if (root) {
        if (strcmp(root->oldspeak, oldspeak) > 0) {
            return bst_find(root->left, oldspeak);
        }
        if (strcmp(root->oldspeak, oldspeak) < 0) {
            return bst_find(root->right, oldspeak);
        }
    } else {
        Node *null = NULL;
        return null;
    }
    return root;
}

Node *bst_insert(Node *root, char *oldspeak, char *newspeak) {
    if (root) {
        if (strcmp(root->oldspeak, oldspeak) > 0) {
            return bst_insert(root->left, oldspeak, newspeak);
        }
        if (strcmp(root->oldspeak, oldspeak) < 0) {
            return bst_insert(root->right, oldspeak, newspeak);
        }
        if (strcmp(root->oldspeak, oldspeak) == 0) {
            Node *null = NULL;
            return null;
        }
    } else {
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
