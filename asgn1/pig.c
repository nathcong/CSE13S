#include "names.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define SEED 2021

typedef enum { SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER } Position;
const Position pig[7] = { SIDE, SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER, JOWLER };

int main(void) {
    int players = 0;
    unsigned int seed = 2021;
    int points[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int player_counter = 0;

    fprintf(stderr, "How many players? ");
    scanf("%d", &players);
    if (players < 2 || players > 10) {
        fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
        players = 2;
    }
    fprintf(stderr, "Random seed: ");
    scanf("%d", &seed);
    if (seed < 0 || seed > UINT_MAX) {
        fprintf(stderr, "Invalid random seed. Using 2021 instead.\n");
        seed = 2021;
    }

    srand(seed);

    fprintf(stderr, "%s rolls the pig...", names[player_counter]);

    while (points[player_counter] < 100) {

        int rng = random() % 7;

        if (pig[rng] == SIDE) {
            ++player_counter;
            if (player_counter >= players) {
                player_counter = 0;
            }
            fprintf(stderr, " pig lands on side\n");
	    fprintf(stderr, "%s rolls the pig...", names[player_counter]);
        }
        if (pig[rng] == RAZORBACK) {
            fprintf(stderr, " pig lands on back");
            points[player_counter] = points[player_counter] + 10;
        }
        if (pig[rng] == TROTTER) {
            fprintf(stderr, " pig lands upright");
            points[player_counter] = points[player_counter] + 10;
        }
        if (pig[rng] == SNOUTER) {
            fprintf(stderr, " pig lands on snout");
            points[player_counter] = points[player_counter] + 15;
        }
        if (pig[rng] == JOWLER) {
            fprintf(stderr, " pig lands on ear");
            points[player_counter] = points[player_counter] + 5;
        }
    }
    fprintf(stderr, "\n%s wins with %d points!\n", names[player_counter], points[player_counter]);
    return 0;
}
