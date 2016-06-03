#pragma once
#include "base.hpp"
#include <vector>
#include "pattern.h"
#include "Move.h"

using namespace BASE;
#define vec std::vector

class MoveGenerator
{
private:
	vec<Move> _GenerateMovesList(u64 possibleMoveBB, int source, short flagf);
	vec<Move> _GeneratePawnAttackList(u64 possibleMoveBB, int source, Color c);
	vec<Move> _GeneratePawnPushesList(u64 possibleMoveBB, int source, Color c, bool doublePush);
	//Serialize the bitboard into vector of integers for easy sourcing.
	vec<int> Serialize(u64 t);
	vec<Move> generateBishopAttack(Color c);
	vec<Move> generateKnightAttacks(Color c);
	vec<Move> generateRookAttacks(Color c);
	vec<Move> generateKingAttacks(Color c);
	vec<Move> generateQueenAttacks(Color c);
	vec<Move> generatePawnAttacks(Color c);
	vec<Move> generatePawnPushes(Color c);

	vec<Move> generateQueenPromotionAttacks(Color c);
	vec<Move> generateKnightPromotionAttacks(Color c);
	vec<Move> generateBishopPromotionAttacks(Color c);
	vec<Move> generateRookPromotionAttacks(Color c);


	/*Check if opposite king under threat.*/
	void isKingUnderThreat(vec<Move> _list, Color c);
	/*Filters attacks if king under threat, shows only valid king-saviour moves.*/
	vec<Move> filterAttacks(vec<Move> _attackList, Color c);

	int pickPromotion(Promotion _choice);
	Bitboard m_GameBoard;

	vec<Move> m_AttackingKing;
	short m_Counter;

public:
	MoveGenerator();
	~MoveGenerator();
	GameState gameState;
	Bitboard GameBoard();
	vec<Move> GetPiecesAttackingKing() const;
#pragma endregion
	vec<Move> generateAllPiecesMove(Color c);

	void _UpdateBoard(Move x, Piece p, Color c);
	void _UpdateBoard(Bitboard& bBoard, Move x, Piece p, Color c);

	/*Get a list of all possible moves for a piece p with color c.
	Think of getting moves list for all white pawns.*/
	vec<Move> GetPieceMoveList(Color c, Piece p);

	/*Get a list of all possible moves for a piece p with color c standing on specific square.
	Think of getting moves for a pawn standing on A1 without getting all othe pawn moves.*/
	vec<Move> GetPieceMoveList(Color c, Piece p, Square piece_square);
	/*Makes a game move.*/
	void MakeMove(Move mov, Piece p, Color c);
	void MakePromotion(Move mov, Color c, Promotion flag);
	/*Undos the last move and updates game board.*/
	void UndoMove(Move x, Piece p, Color c);
};

