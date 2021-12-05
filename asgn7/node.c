#include "node.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        n->oldspeak = strdup(oldspeak);
	if (newspeak == NULL) {
		n->newspeak = NULL;
	}
	else {
        	n->newspeak = strdup(newspeak);
	}
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
