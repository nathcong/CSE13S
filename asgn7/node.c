#include "node.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        n->oldspeak = strdup(oldspeak);
        n->newspeak = strdup(newspeak);
        n->left = NULL;
        n->right = NULL;
    }
    return n;
}

void node_delete(Node **n) {
    free(*n);
    *n = NULL;
    return;
}

void node_print(Node *n) {
    if (n) {
        printf(stderr, "%s", n->oldspeak);
        printf(stderr, "%s", n->newspeak);
        node_print(n->left);
        node_print(n->right);
    }
}
