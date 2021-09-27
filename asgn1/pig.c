#include "names.h"
#include <stdio.h>
#include <stdlib.h>

#define SEED 2021

int main(void) {
	int player = 0;
	int seed = 0;
	fprintf(stderr, "How many players? ");
	scanf("%d", &player);
	if (player < 2 || player > 10) {
		fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
		player = 2;
	}
	fprintf(stderr, "Set the random seed. ");
	scanf("%d", &seed);
	if (seed < 0 || seed > RAND_MAX) {
		fprintf(stderr, "Invalid random seed. Using 2021 instead.\n");
		seed = 2021;
	}

	return 0;
}
