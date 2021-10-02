#include "names.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SEED 2021

typedef enum {SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER} Position;
const Position pig[7] = {
	SIDE,
	SIDE,
	RAZORBACK,
	TROTTER,
	SNOUTER,
	JOWLER,
	JOWLER
};

int main(void) {
	int players = 0;
	unsigned int seed = 0;
	int toppoint = 0;


	fprintf(stderr, "How many players? ");
	scanf("%d", &players);
	if (players < 2 || players > 10) {
		fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
		players = 2;
	}
	fprintf(stderr, "Set the random seed. ");
	scanf("%d", &seed);
	if (seed < 0 || seed > INT_MAX) {
		fprintf(stderr, "Invalid random seed. Using 2021 instead.\n");
		seed = 2021;
	}
	
	while (toppoint < 100) {
		srand(seed);
	}
	return 0;
}
