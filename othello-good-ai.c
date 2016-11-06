#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "othello.h"

#define DEPTH 4

int GoodAITurn(Board *b, int colour) {
	// Put your code for minimax here
	printf("Turn O\n");
	// printf("Pre AI: black: %llu, White %llu\n", b->disks[X_BLACK],
			// b->disks[O_WHITE]);
	int turnScore = minMax(b, DEPTH, colour);
	// printf("Turn score: %d\n", turnScore);
	PrintBoard(*b);
	return turnScore;	//minMax(b, 0, DEPTH, colour);
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

int minMax(Board *b, int depth, int colour) {
	Board legal_moves;
	int num_moves = EnumerateLegalMoves(*b, colour, &legal_moves);
	int toUse = 0;
	// TODO: terminal node
	// printf("moves: %d, depth: %d\n", num_moves, depth);
	if (depth == 0 ) {

		return CountBitsOnBoard(b, colour);
	} else if (num_moves == 0) {
		return 0;
	}
	Board potentialBoards[num_moves];
	ull best;
	if (colour) {
		// printf("playing white...\n");
		best = 0;
		ull moves = legal_moves.disks[O_WHITE];

		for (int i = 0; i < num_moves; i++) {
			// Board newBoard;
			// newBoard.disks[0] = b->disks[0];
			// newBoard.disks[1] = b->disks[1];
			potentialBoards[i] = *b;
			moves = doMove(&potentialBoards[i], moves, O_WHITE);
			// PrintBoard(potentialBoards[i]);
			// int count = CountBitsOnBoard(&potentialBoards[i], colour);

			int recurse = minMax(&potentialBoards[i], depth - 1, X_BLACK);
			if (recurse > best) {
				// printf("found better...\n");
				best = recurse;
				toUse = i;
				// *b = newBoard;
				// *b = potentialBoards[i];
			}
		}
		*b = potentialBoards[toUse];
		return best;
		// min
	} else {
		// printf("playing black...\n");
		best = ULLONG_MAX;
		ull moves = legal_moves.disks[X_BLACK];

		for (int i = 0; i < num_moves; i++) {
			potentialBoards[i] = *b;
			// Board newBoard;
			// newBoard.disks[0] = b->disks[0];
			// newBoard.disks[1] = b->disks[1];
			moves = doMove(&potentialBoards[i], moves, X_BLACK);
			// PrintBoard(potentialBoards[i]);

			// int count = CountBitsOnBoard(&potentialBoards[i], !colour);
			int recurse = minMax(&potentialBoards[i], depth - 1, O_WHITE);
			if (recurse < best) {
				// printf("found worse...\n");
				best = recurse;
				toUse = i;
				// *b = newBoard;
			}
		}
		// *b = potentialBoards[toUse];
		return best;
	}

	// printf("%d\n", toUse);
	// *b = potentialBoards[toUse];
	// PrintBoard(*b);
	// printf("Post AI: black: %llu, White %llu\n", b->disks[X_BLACK],
			// b->disks[O_WHITE]);
}
