#pragma once
#include "base.hpp"
#include "MoveGeneration.h"
#include <vector>
#include "Agent.h"

class Chess
{
private:
	Color playerColor;
public:
	bool AIIsWhite;
	MoveGenerator* generatorInstance;
	Agent* _agent;
	//CTOR for Chess Game
	Chess();

	//CTOR for Chess Game that takes game difficulty and color that AI plays with
	Chess(int lvl, bool isWhite);

	// DTOR for Chess Game
	~Chess();

	u64 GameBoard() const;

	// Logic for making computer play a turn
	void makeAIMove(int* xFrom, int* yFrom, int* xTo, int* yTo);

	// Return int representing piece type at pos I on board
	int getPieceAtSquare(int i);

	// Check is game has ended (Stalemate, checkmate, draw, king killed, 50 move rule,  etc...)
	bool isEndOfGame();

	// move piece at from  to position to
	void MovePiece(int from, int to, int moveFlag, int _color);

	void MakePromotion(int from, int to, int color, int flag);

	// return list of moves valid for a piece on board
	std::vector<Move> GetPieceMoveList(int piecePos, int _color);
};

