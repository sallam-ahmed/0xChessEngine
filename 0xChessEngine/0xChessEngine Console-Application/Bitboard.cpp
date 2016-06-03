#define MAINFILE
#include "Bitboard.h"
#include "base.hpp"

using namespace BASE;
Bitboard::Bitboard()
{
	Color c = white;
	Piece p = pawn;
	allpieces[c][p] = C64(0xff00);
	c = black;
	allpieces[c][p] = C64(0xff000000000000); // black

	p = knight;
	allpieces[c][p] = C64(0x4200000000000000); // black
	c = white;
	allpieces[c][p] = C64(0x42); // white

	p = bishop;
	allpieces[c][p] = C64(0x24); // white
	c = black;
	allpieces[c][p] = C64(0x2400000000000000); // black

	p = rook;
	allpieces[c][p] = C64(0x8100000000000000); // black
	c = white;
	allpieces[c][p] = C64(0x81); // white

	p = queen;
	allpieces[c][p] = C64(0x8); // white
	c = black;
	allpieces[c][p] = C64(0x800000000000000); // black

	p = king;
	allpieces[c][p] = C64(0x1000000000000000); // black
	c = white;
	allpieces[c][p] = C64(0x10); // white

	p = none;
	allpieces[c][p] = C64(0xffff); // white
	c = black;
	allpieces[c][p] = C64(0xffff000000000000); // black

	empty = C64(0xffffffff0000);
	occupied = C64(0xffff00000000ffff);

	// black
	knightPromotion[c] = C64(0);
	bishopPromotion[c] = C64(0);
	rookPromotion[c] = C64(0);
	queenPromotion[c] = C64(0);

	// white
	c = white;
	knightPromotion[c] = C64(0);
	bishopPromotion[c] = C64(0);
	rookPromotion[c] = C64(0);
	queenPromotion[c] = C64(0);

}


Bitboard::~Bitboard()
{

}

u64 Bitboard::getPiece(Color c, Piece p)
{
	return allpieces[c][p];
}
void Bitboard::setPiece(Color c, Piece p, u64 b)
{
	allpieces[c][p] = b;

}
u64 Bitboard::getBishopPromotion(Color c)
{
	return bishopPromotion[c];
}
u64 Bitboard::getEmpty() const
{
	return empty;
}
u64 Bitboard::getKnightPromotion(Color c)
{
	return knightPromotion[c];
}
u64 Bitboard::getOccupied() const
{
	return occupied;
}
u64 Bitboard::getPromotion(Color c, Piece p)
{
	switch (p)
	{
	case knight:
		return knightPromotion[c];
		break;
	case bishop:
		return bishopPromotion[c];
		break;
	case rook:
		return rookPromotion[c];
		break;
	case queen:
		return queenPromotion[c];
		break;
	}

	return u64(0);
}
u64 Bitboard::getQueenPromotion(Color c)
{
	return  queenPromotion[c];
}
u64 Bitboard::getRookPromotion(Color c)
{
	return  rookPromotion[c];
}
void Bitboard::setEmpty(u64 t)
{
	empty = t;
}
void Bitboard::setOccubied(u64 t)
{
	occupied = t;
}
void Bitboard::removePromotionWithSquare(Color c, Piece p, int sq)
{
	switch (p)
	{
	case knight:
		knightPromotion[c] ^= (C64(1) << sq);
		break;
	case bishop:
		bishopPromotion[c] ^= (C64(1) << sq);
		break;
	case rook:
		rookPromotion[c] ^= (C64(1) << sq);
		break;
	case queen:
		queenPromotion[c] ^= (C64(1) << sq);
		break;
	default:
		break;
	}
}
void Bitboard::setPromotionWithBoard(Color c, Piece p, u64 t)
{
	switch (p)
	{
	case knight:
		knightPromotion[c] = t;
		break;
	case bishop:
		bishopPromotion[c] = t;
		break;
	case rook:
		rookPromotion[c] = t;
		break;
	case queen:
		queenPromotion[c] = t;
		break;
	default:
		break;
	}

}

void Bitboard::setPromotionWithSquare(Color c, Piece p, int sq)
{
	switch (p)
	{
	case knight:
		knightPromotion[c] |= (C64(1) << sq);
		break;
	case bishop:
		bishopPromotion[c] |= (C64(1) << sq);
		break;
	case rook:
		rookPromotion[c] |= (C64(1) << sq);
		break;
	case queen:
		queenPromotion[c] |= (C64(1) << sq);
		break;
	default:
		break;
	}

}











