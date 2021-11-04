#include "node.h"
#include <stdlib.h>
#include <stdio.h>

Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        n->symbol = symbol;
        n->frequency = frequency;
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
Node *node_join(Node *left, Node *right) {
}
void node_print(Node *n) {
    fprintf(stdout, "%d", n->symbol);
    return;
}
