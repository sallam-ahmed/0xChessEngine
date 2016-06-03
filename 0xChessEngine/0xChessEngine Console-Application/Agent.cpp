#include "Agent.h"

Node::Node(Move m, Color c, MoveGenerator gameState)
{
	move = m;
	color = c;
	bitboard = gameState.GameBoard();
}

Node::Node(): value(-1), color(white)
{
}

Color Agent::getOppenentColor(Color c) const
{
	if (c == white)
		return black;
	else
		return white;
}

void Agent::addPossibleMovesNodes(Node& n)
{
	//moveG.MakeMove(n.move, whatPiece(moveG.GameBoard(), Square(n.move.from), color), color);
	std::vector<Move> all = movegen.generateAllPiecesMove(color);
	for (Move a : all)
	{
		movegen.MakeMove(a, whatPiece(movegen.GameBoard(), Square(a.to), color), color);
		Node x(a, color, movegen);
		n.childs.push_back(x);
		movegen.UndoMove(a, whatPiece(movegen.GameBoard(), Square(a.to), color), color);
	}
}

u64 Agent::getPosValue(int arr[], Piece type, Node n) const
{
	u64 blackBB = n.bitboard.getPiece(black, type);
	u64 whiteBB = n.bitboard.getPiece(white, type);

	Score whitePos = 0, blackPos = 0;
	int index = 0;
	while (whiteBB)
	{
		if (whiteBB % 2)
			whitePos += arr[63 - index];
		index++;
		whiteBB /= 2;
	}
	index = 0;

	while (blackBB)
	{
		if (blackBB % 2)
			blackPos += -arr[index];
		index++;
		blackBB /= 2;
	}
	return whitePos - blackPos;
}

u64 Agent::getPawnScore(Node n)
{
	int pawnMoveVal[64] =
		{
			0, 0, 0, 0, 0, 0, 0, 0,
			50, 50, 50, 50, 50, 50, 50, 50,
			10, 10, 20, 30, 30, 20, 10, 10,
			5, 5, 10, 25, 25, 10, 5, 5,
			0, 0, 0, 20, 20, 0, 0, 0,
			5, -5,-10, 0, 0,-10, -5, 5,
			5, 10, 10,-20,-20, 10, 10, 5,
			0, 0, 0, 0, 0, 0, 0, 0
		};

	u64 blackPawnBB = n.bitboard.getPiece(black, pawn);
	u64 whitePawnBB = n.bitboard.getPiece(white, pawn);
	Score positionValue = getPosValue(pawnMoveVal, pawn, n);
	//	std::cout << "White Pos    " << whitePos << " Node " << n.move.from << " " << n.move.to << "\n";
	return PiecesCount(whitePawnBB) * scoreTable.pawnScore - PiecesCount(blackPawnBB) * scoreTable.pawnScore + positionValue;
}

u64 Agent::getKnightScore(Node n)
{
	int knightMoveVal[64] =
		{
			-50,-40,-30,-30,-30,-30,-40,-50,
			-40,-20, 0, 0, 0, 0,-20,-40,
			-30, 0, 10, 15, 15, 10, 0,-30,
			-30, 5, 15, 20, 20, 15, 5,-30,
			-30, 0, 15, 20, 20, 15, 0,-30,
			-30, 5, 10, 15, 15, 10, 5,-30,
			-40,-20, 0, 5, 5, 0,-20,-40,
			-50,-40,-30,-30,-30,-30,-40,-50,
		};

	u64 blackknightBB = n.bitboard.getPiece(black, knight);
	u64 whiteknightBB = n.bitboard.getPiece(white, knight);
	Score posVal = getPosValue(knightMoveVal, knight, n);
	return PiecesCount(whiteknightBB) * scoreTable.knightScore - PiecesCount(blackknightBB) * scoreTable.knightScore + posVal;
}

u64 Agent::getBishobScore(Node n)
{
	int bishopMoveVal[64] =
		{
			-20,-10,-10,-10,-10,-10,-10,-20,
			-10, 0, 0, 0, 0, 0, 0,-10,
			-10, 0, 5, 10, 10, 5, 0,-10,
			-10, 5, 5, 10, 10, 5, 5,-10,
			-10, 0, 10, 10, 10, 10, 0,-10,
			-10, 10, 10, 10, 10, 10, 10,-10,
			-10, 5, 0, 0, 0, 0, 5,-10,
			-20,-10,-10,-10,-10,-10,-10,-20,
		};


	u64 blackbishobBB = n.bitboard.getPiece(black, bishop);
	u64 whitebishobBB = n.bitboard.getPiece(white, bishop);
	Score posValue = getPosValue(bishopMoveVal, bishop, n);
	Score x = PiecesCount(whitebishobBB) * scoreTable.bishobScore - PiecesCount(blackbishobBB) * scoreTable.bishobScore + posValue;
	return x;
}

u64 Agent::getRookScore(Node n)
{
	int rookMoveVal[64] =
		{
			0, 0, 0, 0, 0, 0, 0, 0,
			5, 10, 10, 10, 10, 10, 10, 5,
			-5, 0, 0, 0, 0, 0, 0, -5,
			-5, 0, 0, 0, 0, 0, 0, -5,
			-5, 0, 0, 0, 0, 0, 0, -5,
			-5, 0, 0, 0, 0, 0, 0, -5,
			-5, 0, 0, 0, 0, 0, 0, -5,
			0, 0, 0, 5, 5, 0, 0, 0
		};
	u64 blackrookBB = n.bitboard.getPiece(black, rook);
	u64 whiterookBB = n.bitboard.getPiece(white, rook);

	Score posValue = getPosValue(rookMoveVal, rook, n);
	return PiecesCount(whiterookBB) * scoreTable.rookScore - PiecesCount(blackrookBB) * scoreTable.rookScore + posValue;
}

u64 Agent::getQueenScore(Node n)
{
	int queenMoveVal[64] =
		{
			-20,-10,-10, -5, -5,-10,-10,-20,
			-10, 0, 0, 0, 0, 0, 0,-10,
			-10, 0, 5, 5, 5, 5, 0,-10,
			-5, 0, 5, 5, 5, 5, 0, -5,
			0, 0, 5, 5, 5, 5, 0, -5,
			-10, 5, 5, 5, 5, 5, 0,-10,
			-10, 0, 5, 0, 0, 0, 0,-10,
			-20,-10,-10, -5, -5,-10,-10,-20
		};
	u64 blackqueenBB = n.bitboard.getPiece(black, queen);
	u64 whitequeenBB = n.bitboard.getPiece(white, queen);
	Score posValue = getPosValue(queenMoveVal, queen, n);

	return PiecesCount(whitequeenBB) * scoreTable.queenScore - PiecesCount(blackqueenBB) * scoreTable.queenScore + posValue;
}

u64 Agent::getKingScore(Node n)
{
	int kingMoveVal[64] =
		{
			-30,-40,-40,-50,-50,-40,-40,-30,
			-30,-40,-40,-50,-50,-40,-40,-30,
			-30,-40,-40,-50,-50,-40,-40,-30,
			-30,-40,-40,-50,-50,-40,-40,-30,
			-20,-30,-30,-40,-40,-30,-30,-20,
			-10,-20,-20,-20,-20,-20,-20,-10,
			20, 20, 0, 0, 0, 0, 20, 20,
			20, 30, 10, 0, 0, 10, 30, 20
		};
	u64 blackkingBB = n.bitboard.getPiece(black, king);
	u64 whitekingBB = n.bitboard.getPiece(white, king);
	Score posValue = getPosValue(kingMoveVal, king, n);
	return PiecesCount(whitekingBB) * scoreTable.kingScore - PiecesCount(blackkingBB) * scoreTable.kingScore + posValue;
}

int Agent::PiecesCount(u64 bitboard)
{
	int count = 0;

	while (bitboard)
	{
		count += bitboard % 2;
		if (bitboard != 0)
			bitboard = bitboard / 2;
	}
	return count;
}

u64 Agent::getMaterialScore(Node n)
{
	return getPawnScore(n) + getKnightScore(n) + getBishobScore(n) + getQueenScore(n) + getRookScore(n) + getKingScore(n);
}

Node Agent::findNodewithValue(Node n, u64 v)
{
	Node res;
	for (Node x : n.childs)
	{
		if (x.value == v)
		{
			res = x;
		}
	}
	return res;
}

Node Agent::AlphaBeta(Node node, u64 alpha, u64 beta, bool maxmizing, int depth)
{
	Score bestValue;
	nodescount++;
	if (node.childs.size() == 0 || depth == 0)
	{
		node.value = evaluate(node);
		bestValue = node.value;
	}
	else if (maxmizing)
	{
		bestValue = alpha;

		for (Node n : node.childs)
		{
			addPossibleMovesNodes(n);
			Node child = AlphaBeta(n, bestValue, beta, false, depth - 1);
			bestValue = std::max(bestValue, child.value);
			if (beta <= bestValue)
				break;
		}
	}
	else
	{
		bestValue = beta;
		for (Node n : node.childs)
		{
			addPossibleMovesNodes(n);
			Node child = AlphaBeta(n, alpha, bestValue, true, depth - 1);
			bestValue = std::min(bestValue, child.value);
			if (bestValue <= alpha)
				break;
		}
	}
	return findNodewithValue(node, bestValue);
}

void Agent::setMoveGenerator(MoveGenerator m)
{
	movegen = m;
}

Move Agent::make_move()
{
	nodescount = 0;
	//std::cout << "Hereeeeeee"<<std::endl;
	//system("Pause");
	Node root, res;
	root.bitboard = movegen.GameBoard();
	addPossibleMovesNodes(root);
	//std::cout << " Root Size" << root.childs.size() << std::endl;
	//system("Pause");
	res = AlphaBeta(root, Infinity, -Infinity, true, 4);
	return res.move;
}

void Agent::setColor(Color c)
{
	color = c;
}

u64 Agent::evaluate(Node node)
{
	return getMaterialScore(node);
}
