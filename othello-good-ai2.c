#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include <cilk/reducer.h>
#include <cilk/reducer_min_max.h>
#include "othello.h"

#define DEPTH 2
int minMax(Board *b, int depth, int colour);
ull doMove(Board *b, ull move, int colour);

int GoodAITurn(Board *b, int colour) {
	int turnScore = minMax(b, DEPTH, colour);
	return turnScore;	//minMax(b, 0, DEPTH, colour);
}

ull doMove(Board *b, ull move, int colour) {
	int highestBit = __builtin_clzll(move);
	Move m = BIT_TO_MOVE(highestBit);
	move -= ((ull) 1) << (63 - highestBit);
	int nflips = FlipDisks(m, b, colour, 0, 1);
	PlaceOrFlip(m, b, colour);
	return move;
}

int minMax(Board *b, int depth, int colour) {
	Board legal_moves;
	int num_moves = EnumerateLegalMoves(*b, colour, &legal_moves);
	if (depth == DEPTH && num_moves == 0) {
		return 0;
	} else if (depth == 0 || num_moves == 0) {
		return CountBitsOnBoard(b, colour);
	}
	Board potentialBoards[num_moves];
	for(int i = 0; i < num_moves; i++) {
		potentialBoards[i] = *b;
	}
	ull best;
	CILK_C_REDUCER_MAX_INDEX(maxMove, int, 0);
	CILK_C_REDUCER_MIN_INDEX(minMove, int, 0);
	if (colour) {
		best = 0;
	} else {
		best = ULLONG_MAX;
	}
	ull moves = legal_moves.disks[colour];
	cilk_for (int i = 0; i < num_moves; i++) {
		moves = doMove(&potentialBoards[i], moves, colour);

		if (colour) {
			CILK_C_REGISTER_REDUCER(maxMove);
			CILK_C_REDUCER_MAX_INDEX_CALC(maxMove, i, minMax(&potentialBoards[i], depth - 1, !colour));
			CILK_C_UNREGISTER_REDUCER(maxMove);
		} else {
			CILK_C_REGISTER_REDUCER(minMove);
			CILK_C_REDUCER_MIN_INDEX_CALC(minMove, i, minMax(&potentialBoards[i], depth - 1, colour));
			CILK_C_UNREGISTER_REDUCER(minMove);
		}
	}
	if(colour){
		int index = REDUCER_VIEW(maxMove).index;
		*b = potentialBoards[index];	
	}
}

