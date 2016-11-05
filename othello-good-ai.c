#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "othello.h"

#define DEPTH 4

int GoodAITurn(Board *b, int colour) {
	// Put your code for minimax here
	int depth = 2;
	printf("Turn O\n");
	printf("Pre AI: black: %llu, White %llu\n", b->disks[X_BLACK],
			b->disks[O_WHITE]);
	return minMax(b, 0, depth, colour);
}

ull doMove(Board *b, ull move, int colour) {
	int highestBit = __builtin_clzll(move);
	Move m = BIT_TO_MOVE(highestBit);
	move -= ((ull) 1) << (63 - highestBit);
//	 Set the third parameter to 1 to echo disks flipped
	int nflips = FlipDisks(m, b, colour, 0, 1);
	if (nflips == 0) {
		printf("Illegal move: no disks flipped!!\n");
	}
	PlaceOrFlip(m, b, colour);
	return move;
}

int minMax(Board *b, ull move, int depth, int colour) {
	Board legal_moves;
	int num_moves = EnumerateLegalMoves(*b, colour, &legal_moves);
	// TODO: terminal node
	printf("moves: %d\n", num_moves);
	if (depth <= 0) {
		return costHeur(move);
	}
	if (num_moves > 0) {
		Board potentialBoards[num_moves];
		int toUse = 0;
		ull best;
		// max
		if (colour) {
			best = 0;
			ull moves = legal_moves.disks[colour];

			for (int i = 0; i < num_moves; i++) {
				potentialBoards[i] = *b;
				moves = doMove(&potentialBoards[i], moves, colour);
				int count = CountBitsOnBoard(&potentialBoards[i], colour);

				if (best < count) {
					best = count;
					toUse = i;
				}
			}
			// min
		} else {
			best = ULLONG_MAX;
			ull moves = legal_moves.disks[!colour];

			for (int i = 0; i < num_moves; i++) {
				potentialBoards[i] = *b;
				moves = doMove(&potentialBoards[i], moves, !colour);
				int count = CountBitsOnBoard(&potentialBoards[i], !colour);

				if (best > count) {
					best = count;
					toUse = i;
				}
			}

		}
		printf("%d\n", toUse);
		*b = potentialBoards[toUse];
		PrintBoard(*b);
		printf("Post AI: black: %llu, White %llu\n", b->disks[X_BLACK],
				b->disks[O_WHITE]);

		return best;
	} else {
		return 0;
	}
}

int costHeur(ull move) {
	return 0;
}
