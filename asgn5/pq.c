#include "pq.h"

#include "node.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct PriorityQueue {
    uint32_t capacity;
    uint32_t size;
    Node **items;
}

PriorityQueue *
    pq_create(uint32_t capacity) {
    PriorityQueue *pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (q) {
        q->size = 0;
        q->capacity = capacity;
        q->items = (uint32_t *) calloc(capacity, sizeof(Node));
        if (!q->items) {
            free(q);
            q = NULL;
        }
    }
    return q;
}

void pq_delete(PriorityQueue **q) {
    if (*q && (*q)->items) {
        free((*q)->items);
        free(*q);
        *q = NULL;
    }
    return;
}

bool pq_empty(PriorityQueue *q) {
    if (size == 0) {
        return true;
    } else {
        return false;
    }
}

bool pq_full(PriorityQueue *q) {
    if (q->size == q->capacity) {
        return true;
    } else {
        return false;
    }
}

uint32_t pq_size(PriorityQueue *q) {
    return q->size;
}

bool enqueue(PriorityQueue *q, Node *n) {
}

bool dequeue(PriorityQueue *q, Node **n) {
}

void pq_print(PriorityQueue *q) {
    for (uint32_t i = 0; i < q->size; i++) {
        node_print(q->items[i]);
    }
}
