#include "graph.h"

#include "vertices.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Graph struct defintion*/
struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
};

/* creates graph with given number of vertices and can be undirected or not */
Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) calloc(1, sizeof(Graph));
    G->vertices = vertices;
    G->undirected = undirected;
    return G;
}

/* deletes graph and frees memory */
void graph_delete(Graph **G) {
    free(*G);
    *G = NULL;
    return;
}

/* returns number of vertices of graph */
uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

/* adds edge weight to vertex */
bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if (i < G->vertices && j < G->vertices) {
        G->matrix[i][j] = k;
        if (G->undirected == true) {
            G->matrix[j][i] = k;
        }
        return true;
    } else {
        return false;
    }
}

/* checks if vertex has edge weight applied */
bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if (0 <= i < G->vertices && 0 <= j < G->vertices && G->matrix[i][j] > 0) {
        return true;
    } else {
        return false;
    }
}
/* returns edge weight of vertex if applicable */
uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if (0 <= i < G->vertices && 0 <= j < G->vertices) {
        if (G->matrix[i][j] > 0) {
            return G->matrix[i][j];
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

/* checks if vertex has been visited */
bool graph_visited(Graph *G, uint32_t v) {
    if (v < G->vertices) {
        if (G->visited[v]) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

/* marks vertex as visited */
void graph_mark_visited(Graph *G, uint32_t v) {
    if (v < G->vertices) {
        G->visited[v] = true;
    }
}

/* marks vertex as unvisited */
void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (v < G->vertices) {
        G->visited[v] = false;
    }
}

/* prints graph matrix (debugger function) */
void graph_print(Graph *G) {
    for (uint32_t i = 0; i < G->vertices; i++) {
        for (uint32_t j = 0; j < G->vertices; j++) {
            printf("%d, ", G->matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
