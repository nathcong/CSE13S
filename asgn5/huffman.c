#include "node.h"
#include "code.h"
#include "defines.h"
#include "stack.h"
#include "pq.h"
#include "io.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

uint8_t buf[MAX_TREE_SIZE];

Node *build_tree(uint64_t hist[static ALPHABET]) {
    Node *n;
    Node *left;
    Node *right;
    Node *combined;
    PriorityQueue *pq = pq_create(ALPHABET);
    for (uint32_t i = 0; i < ALPHABET; i++) {
        if (hist[i] != 0) {
            n = node_create(i, hist[i]);
            enqueue(pq, n);
        }
    }
    while (pq_size(pq) > 1) {
        dequeue(pq, &left);
        dequeue(pq, &right);
        combined = node_join(left, right);
        enqueue(pq, combined);
    }
    dequeue(pq, &combined);
    pq_delete(&pq);
    return combined;
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    Code c = code_init();
    uint8_t bit_dump;
    if (root != NULL) {
        if (!root->left && !root->right) {
            table[root->symbol] = c;
        } else {
            code_push_bit(&c, 0);
            build_codes(root->left, table);
            code_pop_bit(&c, &bit_dump);

            code_push_bit(&c, 1);
            build_codes(root->right, table);
            code_pop_bit(&c, &bit_dump);
        }
    }
}

void dump_tree(int outfile, Node *root) {
    int i = 0;
    if (root) {
        dump_tree(outfile, root->left);
        dump_tree(outfile, root->right);
        if (root->left == NULL && root->right == NULL) {
            buf[i] = 'L';
            write_bytes(outfile, &buf[i++], 1);
            buf[i] = root->symbol;
            write_bytes(outfile, &buf[i++], 1);
        } else {
            buf[i] = 'I';
            write_bytes(outfile, &buf[i++], 1);
        }
    }
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {
    Node *n;
    Node *left;
    Node *right;
    Node *combined;
    Stack *s = stack_create(ALPHABET);
    for (uint32_t i = 0; i < nbytes; i++) {
        if (tree[i] == 'L') {
            n = node_create(tree[i + 1], 0);
            stack_push(s, n);
            i++;
        }
        if (tree[i] == 'I') {
            stack_pop(s, &right);
            stack_pop(s, &left);
            combined = node_join(left, right);
            stack_push(s, combined);
        }
    }
    stack_pop(s, &combined);
    stack_delete(&s);
    return combined;
}

void delete_tree(Node **root) {
    if (*root) {
        delete_tree(&(*root)->left);
        delete_tree(&(*root)->right);
        node_delete(root);
    }
}
