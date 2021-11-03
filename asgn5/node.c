#include "node.h"
#include <stdlib.h>
#include <stdio.h>

Node *node_create(uint8_t symbol, uint64_t frequency);

void node_delete(Node **n);

Node *node_join(Node *left, Node *right);

void node_print(Node *n);

