#include "Chess.h"

Chess::Chess()
{
	generatorInstance = new MoveGenerator();
	AIIsWhite = false;
	playerColor = Color::white;
	Move m = Move(8, 16);
	m.flag = MoveFlag::Double_Pawn_Push;
	generatorInstance->MakeMove(m, pawn, white);
	_agent = new Agent();
	_agent->setMoveGenerator(*generatorInstance);
	_agent->setColor(Color::black);
}

Chess::Chess(int lvl, bool isWhite)
{
	generatorInstance = new MoveGenerator();
	AIIsWhite = isWhite;
	playerColor = (isWhite) ? black : white;
	_agent = new Agent();
	_agent->setMoveGenerator(*generatorInstance);
	_agent->setColor(opposite(playerColor));
	//INIT Level for ABPruning
}

Chess::~Chess()
{
	delete generatorInstance;
}

u64 Chess::GameBoard() const
{
	return generatorInstance->GameBoard().getOccupied();
}

void Chess::makeAIMove(int* xFrom, int* yFrom, int* xTo, int* yTo)
{
	Move _m = Move();
	_m = _agent->make_move();
	/*_m = AIInstance->MakeMove();*/
	*xFrom = _m.FromVector.x;
	*yFrom = _m.FromVector.y;
	*xTo = _m.ToVector.x;
	*yTo = _m.ToVector.y;
}

int Chess::getPieceAtSquare(int i)
{
	Color c = Color::white;
	Piece p = whatPiece(generatorInstance->GameBoard(), Square(i), c);
	if (p == none)
	{
		c = Color::black;
		p = whatPiece(generatorInstance->GameBoard(), Square(i), c);
		if (p == none)
			return 0;
		else
			return p;
	}
	else
	{
		return p;
	}
}

bool Chess::isEndOfGame()
{
	return (
		generatorInstance->gameState == GameState::CheckBlack ||
		generatorInstance->gameState == GameState::CheckMateWhite ||
		generatorInstance->gameState == GameState::Draw);
}

void Chess::MovePiece(int from, int to, int moveFlag, int _color)
{
	Move _m = Move(from, to);
	_m.flag = MoveFlag(moveFlag);
	Piece _p = whatPiece(generatorInstance->GameBoard(), Square(from), Color(_color));
	generatorInstance->MakeMove(_m, _p, Color(_color));
}

void Chess::MakePromotion(int from, int to, int color, int flag)
{
	Move _move = Move(from, to);
	_move.flag = MoveFlag(flag);
	generatorInstance->MakePromotion(_move, Color(color), Promotion(flag));
}

std::vector<Move> Chess::GetPieceMoveList(int piecePos, int _color)
{
	return generatorInstance->GetPieceMoveList(Color(_color), whatPiece(generatorInstance->GameBoard(), Square(piecePos), Color(_color)));
}
