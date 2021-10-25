#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define OPTIONS "hvui:o:"

static uint32_t recursive_calls = 0;
bool verbose = false;

/* depth first search algorithm */
void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile) {
    uint32_t hold = 0;
    recursive_calls++;

    graph_mark_visited(G, v);
    path_push_vertex(curr, v, G);
    for (uint32_t c = 0; c < graph_vertices(G); c++) {
        if (graph_has_edge(G, v, c) == true) {
            if (graph_visited(G, c) == false) {
                dfs(G, c, curr, shortest, cities, outfile);
            } else if ((c == START_VERTEX) && (path_vertices(curr) == graph_vertices(G))) {
                path_push_vertex(curr, c, G);
                if (path_length(curr) == 0 || path_length(curr) < path_length(shortest)) {
                    path_copy(shortest, curr);
                }
                if (verbose == true) {
                    path_print(curr, outfile, cities);
                }
            }
            path_pop_vertex(curr, &hold, G);
        }
    }
    path_pop_vertex(curr, &hold, G);
    graph_mark_unvisited(G, v);
}

int main(int argc, char **argv) {
    int opt = 0;
    bool help = false;
    bool undirected = false;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    int hold = 0;
    uint32_t total_vertices = 0;
    uint32_t i, j, k = 0;
    char buf[1024];

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        /* switch statement to add functions to the set for them to be run */
        switch (opt) {
        case 'h': {
            help = true;
            break;
        }
        case 'v': {
            verbose = true;
            break;
        }
        case 'u': {
            undirected = true;
            break;
        }
        case 'i': {
            infile = fopen(optarg, "r");
            if (infile == NULL) {
                fprintf(stderr, "Error: File could not be opened.\n");
                exit(0);
            }
            break;
        }
        case 'o': {
            outfile = fopen(optarg, "w");
            if (outfile == NULL) {
                fprintf(stderr, "Error: File could not be opened.\n");
                exit(0);
            }
            break;
        }
        default: {
            help = true;
            break;
        }
        }
    }
    /* if help command is inputted or no input is detected */
    if (help == true) {
        fprintf(outfile, "SYNOPSIS\n");
        fprintf(outfile, "  Traveling Salesman Problem using Depth-First Search\n");
        fprintf(outfile, "USAGE\n");
        fprintf(outfile, "  ./tsp [-uvhi:o:] [-i infile] [-o outfile]\n\n");
        fprintf(outfile, "OPTIONS\n");
        fprintf(outfile, "  -u		Use undirected graph.\n");
        fprintf(outfile, "  -v		Enable verbose printing.\n");
        fprintf(outfile, "  -h		Program help message.\n");
        fprintf(outfile, "  -i infile	Input file containing graph. Default is stdin.\n");
        fprintf(outfile, "  -o outfile 	Output file containing graph. Default is stdout.\n");
        exit(0);
    }

    total_vertices = fscanf(infile, "%" SCNu32 "\n", &total_vertices);

    /* checks if vertices are within bounds */
    if (total_vertices > VERTICES) {
        fprintf(stderr, "Error: Number of vertices malformed.\n");
        exit(0);
    }

    /* cities array memory allocation */
    char *cities = (char *) calloc(total_vertices, sizeof(char *));

    /* storing cities in array */
    for (uint32_t c = 0; c < total_vertices; c++) {
        if (fgets(buf, 1024, infile) != NULL) {
            strtok(buf, "\n");
            cities[c] = *strdup(buf);
        }
    }
    hold = 0;

    /* graph creation */
    Graph *G = graph_create(total_vertices, undirected);

    /* reads vertices and edge weights and checks if valid */
    while (hold != EOF) {
        hold = fscanf(infile, "%" SCNu32 "%" SCNu32 "%" SCNu32 "\n", &i, &j, &k);
        if (hold == EOF) {
            break;
        } else if (hold == 3 && hold != EOF) {
            graph_add_edge(G, i, j, k);
        } else {
            fprintf(stderr, "Error: Vertex edge is malformed");
            exit(0);
        }
    }
    /* create paths for DFS */
    Path *current_path = path_create();
    Path *shortest_path = path_create();

    /* execute DFS */
    dfs(G, START_VERTEX, current_path, shortest_path, &cities, outfile);

    fprintf(outfile, "Total recursive calls: %u\n", recursive_calls);

    /* memory freeing */
    graph_delete(&G);
    path_delete(&current_path);
    path_delete(&shortest_path);

    free(cities);
    fclose(infile);
    fclose(outfile);

    return 0;
}
