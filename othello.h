#ifdef SERIALIZE

#include <cilk/cilk_stub.h>

#endif

#define BIT 0x1

#define X_BLACK 0
#define O_WHITE 1
#define OTHERCOLOR(c) (1-(c))

/*
  represent game board squares as a 64-bit unsigned integer.
  these macros index from a row,column position on the board
  to a position and bit in a game board bitvector
*/
#define BOARD_BIT_INDEX(row,col) ((8 - (row)) * 8 + (8 - (col)))
#define BOARD_BIT(row,col) (0x1LL << BOARD_BIT_INDEX(row,col))
#define MOVE_TO_BOARD_BIT(m) BOARD_BIT(m.row, m.col)
#define BIT_TO_MOVE(bit) {bit/8+1, bit%8+1}

/* all of the bits in the row 8 */
#define ROW8 \
  (BOARD_BIT(8,1) | BOARD_BIT(8,2) | BOARD_BIT(8,3) | BOARD_BIT(8,4) |  \
   BOARD_BIT(8,5) | BOARD_BIT(8,6) | BOARD_BIT(8,7) | BOARD_BIT(8,8))

/* all of the bits in column 8 */
#define COL8 \
  (BOARD_BIT(1,8) | BOARD_BIT(2,8) | BOARD_BIT(3,8) | BOARD_BIT(4,8) |  \
   BOARD_BIT(5,8) | BOARD_BIT(6,8) | BOARD_BIT(7,8) | BOARD_BIT(8,8))

/* all of the bits in column 1 */
#define COL1 (COL8 << 7)

#define IS_MOVE_OFF_BOARD(m) (m.row < 1 || m.row > 8 || m.col < 1 || m.col > 8)
#define IS_DIAGONAL_MOVE(m) (m.row != 0 && m.col != 0)
#define MOVE_OFFSET_TO_BIT_OFFSET(m) (m.row * 8 + m.col)

typedef unsigned long long ull;

/*
  game board represented as a pair of bit vectors:
  - one for x_black disks on the board
  - one for o_white disks on the board
*/
typedef struct { ull disks[2]; } Board;

typedef struct { int row; int col; } Move;

//char diskcolor[];

/* Players */
int HumanTurn(Board *b, int color);
int SimpleAITurn(Board *b, int color);
int GoodAITurn(Board *b, int color);

/* Auxilary functions exported from othello.c */
int EnumerateLegalMoves(Board b, int color, Board *legal_moves);
void PrintBoard(Board b);
Board NeighborMoves(Board b, int color);
int CountBitsOnBoard(const Board *b, int color);
int FlipDisks(Move m, Board *b, int color, int verbose, int domove);
void PlaceOrFlip(Move m, Board *b, int color);
