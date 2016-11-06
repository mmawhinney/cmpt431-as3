#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "othello.h"

#define DEPTH 1

int GoodAITurn(Board *b, int colour) {
	// Put your code for minimax here
	// int depth = 2;
	printf("Turn O\n");
	printf("Pre AI: black: %llu, White %llu\n", b->disks[X_BLACK],
			b->disks[O_WHITE]);
	int turnScore = minMax(b, 0, DEPTH, colour);
	printf("Turn score: %d\n", turnScore);
	return turnScore;//minMax(b, 0, DEPTH, colour);
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
	int toUse = 0;
	// TODO: terminal node
	printf("moves: %d, depth: %d\n", num_moves, depth);
	if (depth == 0 || num_moves == 0) {
		
		return CountBitsOnBoard(b, colour);
	}
	// if (num_moves > 0) {
		Board potentialBoards[num_moves];
		// int toUse = 0;
		ull best;
		// max
		if (colour) {
			best = 0;
			ull moves = legal_moves.disks[colour];

			for (int i = 0; i < num_moves; i++) {
				potentialBoards[i] = *b;
				moves = doMove(&potentialBoards[i], moves, colour);
				// int count = CountBitsOnBoard(&potentialBoards[i], colour);
				int recurse = minMax(&potentialBoards[i], move, depth - 1, colour);
				if (recurse > best) {
					best = recurse;
					toUse = i;
				}
			}
			return best;
			// min
		} else {
			best = ULLONG_MAX;
			ull moves = legal_moves.disks[!colour];

			for (int i = 0; i < num_moves; i++) {
				potentialBoards[i] = *b;
				moves = doMove(&potentialBoards[i], moves, !colour);
				// int count = CountBitsOnBoard(&potentialBoards[i], !colour);
				int recurse = minMax(&potentialBoards[i], move, depth - 1, colour);
				if (recurse < best) {
					best = recurse;
					toUse = i;
				}
			}
			return best;
		}
		
		printf("%d\n", toUse);
		*b = potentialBoards[toUse];
		PrintBoard(*b);
		printf("Post AI: black: %llu, White %llu\n", b->disks[X_BLACK],
		b->disks[O_WHITE]);
		// return best;
	// } else {
		// return 0;
	// }
}

int costHeur(ull move) {
	return 0;
}
