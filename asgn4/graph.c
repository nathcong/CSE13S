#include "graph.h"

#include <stdbool.h>
#include <stdint.h>

struct Graph {
	uint32_t vertices;
	bool undirected;
	bool visited[VERTICES];
	uint32_t matrix[VERTICES][VERTICES];
};

Graph *graph_create(uint32_t vertices, bool undirected) {
	Graph *G = (Graph *)calloc(1, sizeof(Graph));
	G->vertices = vertices;
	G->undirected = undirected;
	return G;
}
void graph_delete(Graph **G) {
	free(*G);
	*G = NULL;
	return;
}
uint32_t graph_vertices(Graph *G) {
	return G->vertices;
}
bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
	if (0 <= i < G->vertices && 0 <= j < G->vertices) {
		G->matrix[i][j] = k;
		if (G->undirected) {
			G->matrix[j][i] = k;
		}
		return true;
	}
	else {
		return false;
	}
}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
	if (0 <= i < G->vertices && 0 <= j < G->vertices) {
		if (G->matrix[i][j] > 0) {
			return true;
		}
	}
	else {
		return false;
	}
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
	if (0 <= i < G->vertices && 0 <= j < G->vertices) {
		if (G->matrix[i][j] > 0) {
			return G->matrix[i][j];
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
}
bool graph_visited(Graph *G, uint32_t v) {
	if (v < G->vertices) {
		if (G->visited[v]) {
			return true;
		else {
			return false;
		}
	}
	return false;
}
void graph_mark_visited(Graph *G, uint32_t v) {
	if (v < G->vertices) {	
		G->visited[v] = true;
	}
}
void graph_mark_unvisited(Graph *G, uint32_t v) {
	if (v < G->vertices) {
		G->visited[v] = false;
	}
}
void graph_print(Graph *G) {

}

