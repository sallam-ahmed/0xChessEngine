#pragma once
#include "base.hpp"
namespace BASE {
	class Bitboard
	{
		u64 allpieces[Colorend][Pieceend];
		u64 empty;
		u64 occupied;
		u64 knightPromotion[Colorend];
		u64 bishopPromotion[Colorend];
		u64 rookPromotion[Colorend];
		u64 queenPromotion[Colorend];

	public:
		Bitboard();
		~Bitboard();
		u64 getPiece(Color c, Piece p);
		u64 getPromotion(Color c, Piece p);
		u64 getKnightPromotion(Color c);
		u64 getBishopPromotion(Color c);
		u64 getRookPromotion(Color c);
		u64 getQueenPromotion(Color c);
		u64 getEmpty() const;
		u64 getOccupied() const;

		void setPiece(Color c, Piece p, u64 b);
		void setPromotionWithSquare(Color c, Piece p, int sq);
		void removePromotionWithSquare(Color c, Piece p, int sq);
		void setPromotionWithBoard(Color c, Piece p, u64 t);
		void setEmpty(u64 t);
		void setOccubied(u64 t);
		
	};

}