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
	
	unsigned int points[10];
	int top_points = 0;
	int top_points_holder = 0;
	int player_counter = 0;
	int rng = 0;	

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
	
	while (top_points < 100) {
		srand(seed);
		rng = rand() % 7;
		fprintf(stderr, "%d points", points[player_counter]);


		fprintf(stderr, "%s rolls the pig...", names[player_counter]);
		if (points[player_counter] > top_points) {
			top_points = points[player_counter];
			top_points_holder = player_counter;
		}
		if (pig[rng] == SIDE) {
			fprintf(stderr, " pig lands on side\n");
			++player_counter;
		}
		if (pig[rng] == RAZORBACK) {
			fprintf(stderr, " pig lands on back");
			points[player_counter] += 10;
		}
		if (pig[rng] == TROTTER) {
			fprintf(stderr, " pig lands upright");
			points[player_counter] += 10;
		}
		if (pig[rng] == SNOUTER) {
			fprintf(stderr, " pig lands on snout");
			points[player_counter] += 15;
		}
		if (pig[rng] == JOWLER) {
			fprintf(stderr, " pig lands on ear");
			points[player_counter] += 5;
		}
		fprintf(stderr, "%d points", points[player_counter]);
		fprintf(stderr, "%s wins with %d points!\n", names[player_counter], points[player_counter]);
	}
	return 0;
}
