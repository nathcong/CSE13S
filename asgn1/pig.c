#include "names.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    SIDE,
    RAZORBACK,
    TROTTER,
    SNOUTER,
    JOWLER
} Position; /* declaration of names of enumerated positions of array below */
const Position pig[7] = { SIDE, SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER,
    JOWLER }; /* enumerated array for pig positions */

int main(void) {
    int players = 0;
    unsigned int seed = 2021;
    int points[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0 }; /* points array for logging points accumulated by players */
    int player_counter = 0;

    printf("How many players? ");
    scanf("%d", &players);
    if (players < 2 || players > 10) { /* checks for a valid number of players */
        fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
        players = 2;
    }
    printf("Random seed: ");
    scanf("%d", &seed);
    if (seed < 0 || seed > UINT_MAX) { /* checks if seed is in the valid range */
        fprintf(stderr, "Invalid random seed. Using 2021 instead.\n");
        seed = 2021;
    }

    srand(seed);

    printf("%s rolls the pig...", names[player_counter]);

    while (points[player_counter] < 100) { /* while any player's score is under 100 points */

        int rng = random()
                  % 7; /* usage of modulus operations to keep number generated between 0 and 6 */

        /* conditionals check position correspondence to number generated */

        if (pig[rng] == SIDE) { /* moves to the next player's turn */
            ++player_counter;
            if (player_counter >= players) {
                player_counter = 0;
            }
            printf(" pig lands on side\n");
            printf("%s rolls the pig...", names[player_counter]);
        }
        if (pig[rng] == RAZORBACK) {
            printf(" pig lands on back");
            points[player_counter] = points[player_counter] + 10;
        }
        if (pig[rng] == TROTTER) {
            printf(" pig lands upright");
            points[player_counter] = points[player_counter] + 10;
        }
        if (pig[rng] == SNOUTER) {
            printf(" pig lands on snout");
            points[player_counter] = points[player_counter] + 15;
        }
        if (pig[rng] == JOWLER) {
            printf(" pig lands on ear");
            points[player_counter] = points[player_counter] + 5;
        }
    }
    printf("\n%s wins with %d points!\n", names[player_counter],
        points[player_counter]); /* triggers when 100 or more points are reached */
    return 0;
}
