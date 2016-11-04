#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "othello.h"

#define DEPTH 4

int GoodAITurn(Board *b, int color) {
	// Put your code for minimax here
	Board legal_moves;
	int num_moves = EnumerateLegalMoves(*b, color, &legal_moves);
	if (num_moves > 0) {
//		// do a random move (rand is seeded in main)
//		int moveNum = rand() % num_moves;
//		ull moves = legal_moves.disks[color];
//		// clz returns the bit number of the first bit set counting from the msb
//		int highestBit = __builtin_clzll(moves);
//		for (int i = 0; i < moveNum; i++) {
//			// Remove the highest bit from possible moves
//			moves -= ((ull) 1) << (63 - highestBit);
//			// Get the next highest bit
//			highestBit = __builtin_clzll(moves);
//		}
//		Move m = BIT_TO_MOVE(highestBit);
//		// Set the third parameter to 1 to echo disks flipped
//		int nflips = FlipDisks(m, b, color, 1, 1);
//		if (nflips == 0) {
//			printf("Illegal move: no disks flipped!!\n");
//		}
//		PlaceOrFlip(m, b, color);
//		PrintBoard(*b);
//		return 1;
	} else
		return 0;
	return 0;
}

int minMax(ull move, int depth, int color) {
	// TODO: terminal node
	if (depth <= 0) {
		return costHeur(move);
	}
	// max
	if (color) {
		ull best = 0;
		for (int i = 0; i < num_moves; i++) {
			int value = i;
			if (best < i) {
				best = i;
			}
		}
		return best;
		// min
	} else {
		ull best = ULLONG_MAX;
		for (int i = 0; i < num_moves; i++) {
			int value = i;
			if (best > i) {
				best = i;
			}
		}
		return best;
	}
}

int costHeur(ull move) {
	return 0;
}
