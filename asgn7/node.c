#include "node.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* create new node */
Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        n->oldspeak = strdup(oldspeak);
        if (newspeak == NULL) {
            n->newspeak = NULL;
        } else {
            n->newspeak = strdup(newspeak);
        }
        n->left = NULL;
        n->right = NULL;
    }
    return n;
}

/* free memory and delete node */
void node_delete(Node **n) {
    free((*n)->oldspeak);
    free((*n)->newspeak);
    free(*n);
    *n = NULL;
    return;
}

/* print node along with its oldspeak, newspeak, and children */
void node_print(Node *n) {
    if (n) {
        if (n->oldspeak && n->newspeak) {
            fprintf(stderr, "%s -> %s\n", n->oldspeak, n->newspeak);
        }
        if (n->newspeak == NULL) {
            fprintf(stderr, "%s\n", n->oldspeak);
        }
        node_print(n->left);
        node_print(n->right);
    }
}
