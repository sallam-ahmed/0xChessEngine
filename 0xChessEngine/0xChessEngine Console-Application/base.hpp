#pragma once

#include <iostream>
#include "cstdlib"
#include <iomanip>
#include <algorithm>
#include "enum.h"
typedef unsigned long long int u64;

#define SELECT_ANY __declspec( selectany )
#define C64(t) t##ULL


namespace BASE
{
 const u64 universe = 0xffffffffffffffffULL;


typedef short int MOVE;

#define NO_MOVE (MOVE) - 1
#define special_flag (MOVE)( 1<< 15)

	 const int files = 8;
	 const int ranks = 8;
	 const int squares = files * ranks;
	 const int max_moves = 500;

	//for shifting 1,7,9 (positive & negative)
	 const u64 notAFile = 0xfefefefefefefefe;
	 const u64 notHFile = 0x7f7f7f7f7f7f7f7f; // = ~H

											 // for horizontal wrapping
	 const u64 notABFile = 0xfcfcfcfcfcfcfcfc;
	 const u64 notGHFile = 0x3f3f3f3f3f3f3f3f;

	 const int index64[64] = {               // 64-bit De Bruijn sequence
		0,  1, 48,  2, 57, 49, 28,  3,
		61, 58, 50, 42, 38, 29, 17,  4,
		62, 55, 59, 36, 53, 51, 43, 22,
		45, 39, 33, 30, 24, 18, 12,  5,
		63, 47, 56, 27, 60, 41, 37, 16,
		54, 35, 52, 21, 44, 32, 23, 11,
		46, 26, 40, 15, 34, 20, 31, 10,
		25, 14, 19,  9, 13,  8,  7,  6
	};

	// for generalized shifting
	SELECT_ANY u64 avoidWrap[8] =
	{
		0xfefefefefefefe00,
		0xfefefefefefefefe,
		0x00fefefefefefefe,
		0x00ffffffffffffff,
		0x007f7f7f7f7f7f7f,
		0x7f7f7f7f7f7f7f7f,
		0x7f7f7f7f7f7f7f00,
		0xffffffffffffff00,
	};
	SELECT_ANY int shift[8] = { 9, 1,-7,-8,-9,-1, 7, 8 };

	//      Knuth's magic masks (used for horizontal mirroring)
	//    0x5555555555555555  0x3333333333333333  0x0F0F0F0F0F0F0F0F
	//    1 0 1 0 1 0 1 0     1 1 0 0 1 1 0 0     1 1 1 1 0 0 0 0
	//    1 0 1 0 1 0 1 0     1 1 0 0 1 1 0 0     1 1 1 1 0 0 0 0
	//    1 0 1 0 1 0 1 0     1 1 0 0 1 1 0 0     1 1 1 1 0 0 0 0
	//    1 0 1 0 1 0 1 0     1 1 0 0 1 1 0 0     1 1 1 1 0 0 0 0
	//    1 0 1 0 1 0 1 0     1 1 0 0 1 1 0 0     1 1 1 1 0 0 0 0
	//    1 0 1 0 1 0 1 0     1 1 0 0 1 1 0 0     1 1 1 1 0 0 0 0
	//    1 0 1 0 1 0 1 0     1 1 0 0 1 1 0 0     1 1 1 1 0 0 0 0
	//    1 0 1 0 1 0 1 0     1 1 0 0 1 1 0 0     1 1 1 1 0 0 0 0
	 const u64 k1 = C64(0x5555555555555555);
	 const u64 k2 = C64(0x3333333333333333);
	 const u64 k3 = C64(0x0F0F0F0F0F0F0F0F);

	//  for Diagonal flipping, the used masks :
	//    0x5500550055005500  0x3333000033330000  0x0F0F0F0F00000000
	//    1 . 1 . 1 . 1 .     1 1 . . 1 1 . .     1 1 1 1 . . . .
	//    . . . . . . . .     1 1 . . 1 1 . .     1 1 1 1 . . . .
	//    1 . 1 . 1 . 1 .     . . . . . . . .     1 1 1 1 . . . .
	//    . . . . . . . .     . . . . . . . .     1 1 1 1 . . . .
	//    1 . 1 . 1 . 1 .     1 1 . . 1 1 . .     . . . . . . . .
	//    . . . . . . . .     1 1 . . 1 1 . .     . . . . . . . .
	//    1 . 1 . 1 . 1 .     . . . . . . . .     . . . . . . . .
	//    . . . . . . . .     . . . . . . . .     . . . . . . . .
	 const u64 k4 = C64(0x5500550055005500);
	 const u64 k5 = C64(0x3333000033330000);
	 const u64 k6 = C64(0x0F0F0F0F00000000);

	//for anti diagonal masking
	//    0xAA00AA00AA00AA00  0xCCCC0000CCCC0000  0xF0F0F0F00F0F0F0F
	//    . 1 . 1 . 1 . 1     . . 1 1 . . 1 1     . . . . 1 1 1 1
	//    . . . . . . . .     . . 1 1 . . 1 1     . . . . 1 1 1 1
	//    . 1 . 1 . 1 . 1     . . . . . . . .     . . . . 1 1 1 1
	//    . . . . . . . .     . . . . . . . .     . . . . 1 1 1 1
	//    . 1 . 1 . 1 . 1     . . 1 1 . . 1 1     1 1 1 1 . . . .
	//    . . . . . . . .     . . 1 1 . . 1 1     1 1 1 1 . . . .
	//    . 1 . 1 . 1 . 1     . . . . . . . .     1 1 1 1 . . . .
	//    . . . . . . . .     . . . . . . . .     1 1 1 1 . . . .
	 const u64 k7 = C64(0xAA00AA00AA00AA00);
	 const u64 k8 = C64(0xCCCC0000CCCC0000);
	 const u64 k9 = C64(0xF0F0F0F00F0F0F0F);

	//for 45 degree rotaion clockwise as for counterclockwise Knuth's magic masks will be used
	//    0xAAAAAAAAAAAAAAAA       0xCCCCCCCCCCCCCCCC     0xF0F0F0F0F0F0F0F0
	//    0 1 0 1 0 1 0 1          0 0 1 1 0 0 1 1        0 0 0 0 1 1 1 1
	//    0 1 0 1 0 1 0 1          0 0 1 1 0 0 1 1        0 0 0 0 1 1 1 1
	//    0 1 0 1 0 1 0 1          0 0 1 1 0 0 1 1        0 0 0 0 1 1 1 1
	//    0 1 0 1 0 1 0 1          0 0 1 1 0 0 1 1        0 0 0 0 1 1 1 1
	//    0 1 0 1 0 1 0 1          0 0 1 1 0 0 1 1        0 0 0 0 1 1 1 1
	//    0 1 0 1 0 1 0 1          0 0 1 1 0 0 1 1        0 0 0 0 1 1 1 1
	//    0 1 0 1 0 1 0 1          0 0 1 1 0 0 1 1        0 0 0 0 1 1 1 1
	//    0 1 0 1 0 1 0 1          0 0 1 1 0 0 1 1        0 0 0 0 1 1 1 1
	 const u64 k10 = C64(0xAAAAAAAAAAAAAAAA);
	 const u64 k11 = C64(0xCCCCCCCCCCCCCCCC);
	 const u64 k12 = C64(0xF0F0F0F0F0F0F0F0);

	 const u64 H = 0x8080808080808080;
	 const u64 L = 0x0101010101010101;
	 const u64 row1 = C64(0xff);
	 const u64 row3 = C64(0xFF0000);
	 const u64 row6 = C64(0xff0000000000);
	 const u64 row8 = C64(0xff00000000000000);



/*
Color & Piece enums
will be used in Class bitboard as 14 bitboards will be stored in 2D array
1th D : color
2th D : piece
*/
 enum Color
{
	white, black, Colorbegin = white, Colorend = black + 1
};
declareenumloop(Color)

	inline Color opposite(Color c)
{
	return c == white ? black : white;
}

 enum Piece
{
	none, pawn, knight, bishop, rook, queen, king, Piecebegin = none, Pieceend = king + 1
};
declareenumloop(Piece)

 enum Square
{
	a1, b1, c1, d1, e1, f1, g1, h1,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a8, b8, c8, d8, e8, f8, g8, h8,
	Squarebegin = a1, Squareend = h8 + 1
};
declareenumloop(Square)

 enum File
{
	fileA, fileB, fileC, fileD, fileE, fileF, fileG, fileH,
	Filebegin = fileA, Fileend = fileH + 1
};
declareenumloop(File)

 enum Rank
{
	rank1, rank2, rank3, rank4, rank5, rank6, rank7, rank8,
	Rankbegin = rank1, Rankend = rank8 + 1
};
declareenumloop(Rank)

//directio enum for moves on empty board

 enum Direction
{
	nort, noWe, noEa, east, west, sout, soWe, soEa, Directionbegin = nort, Directionend = soEa + 1
};
declareenumloop(Direction)

 enum Result {
	INVALID = 0, UNKNOWN = 1, DRAW = 2, WIN = 4
};


/* from chessprogramming.com
FileIndex   = squareIndex modulo 8  = squareIndex & 7
RankIndex   = squareIndex div    8  = squareIndex >> 3 */

	inline Square getSquare(File f, Rank r)
{
	return Square(r * 8 + f);
}

	inline File getFile(Square s)
{
	return File(s & 7);
}

	inline Rank getRank(Square s)
{
	return Rank(s >> 3);
}

/*
* https://chessprogramming.wikispaces.com/Score
*/

/*Movement Type Identifier*/
enum MoveFlag {
	/*Quiet ordinary move.*/
	Quiet = 0,
	/*Pawn double push.*/
	Double_Pawn_Push,
	/*Piece captures another piece.*/
	Capture,
	/*Pawn promoted to knight.*/
	Knight_Promotion,
	/*Pawn promoted to bishop.*/
	Bishop_Promotion,
	/*Pawn promoted to rook.*/
	Rook_Promotion,
	/*Pawn promoted to queen.*/
	Queen_Promotion,
	/*Pawn promoted to queen and captured another piece.*/
	Queen_Promotion_with_Capture,
	/*Pawn promoted to knight and captured another piece.*/
	Knight_Promotion_with_Capture,
	/*Pawn promoted to bishop and captured another piece.*/
	Bishop_Promotion_with_Capture,
	/*Pawn promoted to rook and captured another piece.*/
	Rook_Promotion_with_Capture
};
/*Represent promotion types.*/
enum Promotion
{
	Knight = 3,
	Bishop,
	Rook,
	Queen,
	Promote_begin = Knight,
	Promote_end = Queen + 1,
};
/*Represents current game state, needed for king checks and 50 move rule.*/
enum GameState
{
	Normal = 0,
	CheckMateWhite,
	CheckMateBlack,
	CheckWhite,
	CheckBlack,
	StaleMateWhite,
	StaleMateBlack,
	Draw
};
}