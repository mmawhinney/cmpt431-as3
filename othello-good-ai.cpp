#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <iostream>
#include <cilk/cilk.h>

#include <cilk/reducer_min_max.h>
#include "othello.h"

#define DEPTH 5
int minMax(Board *b, int depth, int colour);
ull doMove(Board *b, ull move, int colour);

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
//	if (nflips == 0) {
//		printf("Illegal move: no disks flipped!!\n");
//	}
	PlaceOrFlip(m, b, colour);
	return move;
}

int minMax(Board *b, int depth, int colour) {
	Board legal_moves;
	int num_moves = EnumerateLegalMoves(*b, colour, &legal_moves);
//	printf("moves: %d, depth: %d\n", num_moves, depth);
	if (depth == DEPTH && num_moves == 0) {
		return 0;
	} else if (depth == 0 || num_moves == 0) {
		return CountBitsOnBoard(b, colour);
	}
	Board potentialBoards[num_moves];
	ull best;
	if (colour) {
		best = 0;
	} else {
		best = ULLONG_MAX;
	}
	ull moves = legal_moves.disks[colour];

	for (int i = 0; i < num_moves; i++) {
		potentialBoards[i] = *b;
		moves = doMove(&potentialBoards[i], moves, colour);

		if (colour) {
			cilk::reducer < cilk::op_max_index<int, int> > maxMove;
			maxMove->calc_max(i,
					minMax(&potentialBoards[i], depth - 1, !colour));
			*b = potentialBoards[maxMove.get_value().first];
			return 1;
		} else {
			cilk::reducer < cilk::op_min_index<int, int> > minMove;
			minMove->calc_min(i,
					minMax(&potentialBoards[i], depth - 1, colour));
		}
	}
	return best;
}

// printf("%d\n", toUse);
// *b = potentialBoards[toUse];
// PrintBoard(*b);
// printf("Post AI: black: %llu, White %llu\n", b->disks[X_BLACK],
// b->disks[O_WHITE]);