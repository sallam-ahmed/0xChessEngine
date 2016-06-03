#include "MoveGeneration.h"
#include "bitboard.h"
#include "extrasbitboard.h"
#include "pattern.h"
#include "base.hpp"
#include "Agent.h"
using namespace std;
using namespace BASE;
#define vec vector
#define mov_msg(p,t,i) std::cout << "A " << p << " moved from " << t << " to " << i <<endl
#define show_moves(M) for(int i=0;i<M.size();i++){cout<<i+1 << "- From " << M[i].from << " to " << M[i].to << " flag " << M[i].flag<<endl;}
#define pause system("pause")
#define mk_mov(m,p,c) gen.MakeMove(m,p,c)
#define msg(m) cout << m << endl
#define show_board cout << gen.GameBoard().getOccupied() << endl

int main()
{
	MoveGenerator gen;
	vec<Move> PawnMoves, KnightMoves, RookMoves, BishopMoves, KingMoves, QueenMoves;
	Color _turn = white;
	Agent* a = new Agent();
	a->setColor(black);
	a->setMoveGenerator(gen);

	while (cin)
	{
		//if (_turn == white)
		//cout << "White turn " << endl;
		//else
		//cout << "Black turn " << endl;

		msg("Pawn : p\nKnight: k\nRook: r\nBishop: b\nKing: n\nQueen: q\n");
		PawnMoves = gen.GetPieceMoveList(_turn, pawn);
		KnightMoves = gen.GetPieceMoveList(_turn, knight);
		RookMoves = gen.GetPieceMoveList(_turn, rook);
		BishopMoves = gen.GetPieceMoveList(_turn, bishop);
		KingMoves = gen.GetPieceMoveList(_turn, king);
		QueenMoves = gen.GetPieceMoveList(_turn, queen);
		msg("Possible Moves:");
		msg("Pawn:");
		show_moves(PawnMoves);
		msg("Knight:");
		show_moves(KnightMoves);
		msg("Rook:");
		show_moves(RookMoves);
		msg("Bishop:");
		show_moves(BishopMoves);
		msg("King:");
		show_moves(KingMoves);
		msg("Queen:");
		show_moves(QueenMoves);
		char t;
		cin >> t;

		int move;
		cin >> move;

		switch (t)
		{

		case 'p':
			if (validForPromotion(Square(PawnMoves[move - 1].from), _turn))
			{
				gen.MakePromotion(PawnMoves[move - 1], _turn, Promotion::Queen);
			}
			else
				mk_mov(PawnMoves[move - 1], pawn, _turn); msg("Move made");
			break;
		case 'k':
			mk_mov(KnightMoves[move - 1], knight, _turn); msg("Move made");
			break;
		case 'r':
			mk_mov(RookMoves[move - 1], rook, _turn); msg("Move made");
			break;
		case 'b':
			mk_mov(BishopMoves[move - 1], bishop, _turn); msg("Move made");
			break;
		case 'n':
			mk_mov(KingMoves[move - 1], king, _turn); msg("Move made");
			break;
		case 'q':
			mk_mov(QueenMoves[move - 1], queen, _turn); msg("Move made");
			break;
		}
		show_board;

		Move m = a->make_move();
		std::vector<Move> all = gen.generateAllPiecesMove(black);
		show_moves(all);
		mk_mov(m, whatPiece(gen.GameBoard(), Square(m.to), black), black);
		msg("AI take turn\n");
		msg(m.from);
		msg(m.to);
		msg("All Moves");


		show_board;
		msg("Nodes ");

	}

	pause;
}