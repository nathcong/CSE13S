#include "pq.h"

#include "node.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct PriorityQueue {
    uint32_t capacity;
    uint32_t top;
    Node **items;
};

PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (q) {
        q->top = 0;

        q->items = (Node **) calloc(capacity, sizeof(Node *));
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
    if (q->top == 0) {
        return true;
    } else {
        return false;
    }
}

bool pq_full(PriorityQueue *q) {
    if (q->top == q->capacity) {
        return true;
    } else {
        return false;
    }
}

uint32_t pq_size(PriorityQueue *q) {
    return q->top;
}

void pq_insertion_sort(PriorityQueue *q) {
    uint32_t i;
    uint32_t j;
    Node *temp;
    uint32_t m = q->top;
    for (i = 0; i < m; i++) {
        j = i;
        temp = q->items[i];
        while (j > 0 && temp->frequency > q->items[j - 1]->frequency) {
            q->items[j] = q->items[j - 1];
            j -= 1;
        }
        q->items[j] = temp;
    }
}

bool enqueue(PriorityQueue *q, Node *n) {
    if (q->top < q->capacity) {
        q->items[q->top] = n;
        q->top++;
        pq_insertion_sort(q);
        return true;
    } else {
        return false;
    }
}

bool dequeue(PriorityQueue *q, Node **n) {
    if (q->top != 0) {
        *n = q->items[q->top - 1];
        q->top--;
        return true;
    } else {
        return false;
    }
}

void pq_print(PriorityQueue *q) {
    for (uint32_t i = 0; i < q->top; i++) {
        node_print(q->items[i]);
    }
}
