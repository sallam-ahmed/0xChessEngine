#pragma once
#include "MoveGeneration.h"
using namespace BASE;
#define Score u64
#define Infinity 999999999

struct ScoreTable {
	Score pawnScore = 1;
	Score knightScore = 3;
	Score bishobScore = 3;
	Score rookScore = 5;
	Score queenScore = 9;
	Score kingScore = 1000;

};

struct Node {
	Move move;
	Bitboard bitboard;
	std::vector<Node> childs;
	Score value;
	Color color;
	Node(Move m, Color c, MoveGenerator gameState);

	Node();
};

class Agent {
	Color color;

	MoveGenerator movegen;

	ScoreTable scoreTable;

	Color getOppenentColor(Color c) const;

	void addPossibleMovesNodes(Node& n);

	Score getPosValue(int arr[], Piece type, Node n) const;

	Score getPawnScore(Node n);

	Score getKnightScore(Node n);

	Score getBishobScore(Node n);

	Score getRookScore(Node n);

	Score getQueenScore(Node n);

	Score getKingScore(Node n);

	int PiecesCount(u64 bitboard);

	Score getMaterialScore(Node n);

	Node findNodewithValue(Node n, Score v);

	Node AlphaBeta(Node node, Score alpha, Score beta, bool maxmizing, int depth);


public:
	int nodescount;
	void setMoveGenerator(MoveGenerator m);

	Move make_move();

	void setColor(Color c);

	Score evaluate(Node node);
};