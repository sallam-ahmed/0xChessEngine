#include "MoveGeneration.h"


MoveGenerator::~MoveGenerator()
{
}

std::vector<Move> MoveGenerator::GetPiecesAttackingKing() const
{
	return m_AttackingKing;
}

std::vector<Move> MoveGenerator::generateAllPiecesMove(Color c)
{
	{
		vec<Move> _moves = GetPieceMoveList(c, pawn);
		for (auto I : GetPieceMoveList(c, knight))
		{
			_moves.push_back(I);
		}
		for (auto I : GetPieceMoveList(c, rook))
		{
			_moves.push_back(I);
		}
		for (auto I : GetPieceMoveList(c, bishop))
		{
			_moves.push_back(I);
		}
		for (auto I : GetPieceMoveList(c, queen))
		{
			_moves.push_back(I);
		}
		for (auto I : GetPieceMoveList(c, king))
		{
			_moves.push_back(I);
		}
		return _moves;
	}
}

void MoveGenerator::_UpdateBoard(Move x, Piece p, Color c)
{
	{
		Piece pCaptured;

		m_GameBoard.setEmpty(set(m_GameBoard.getEmpty(), Square(x.from)));
		m_GameBoard.setEmpty(reset(m_GameBoard.getEmpty(), Square(x.to)));

		m_GameBoard.setOccubied(set(m_GameBoard.getOccupied(), Square(x.to)));
		m_GameBoard.setOccubied(reset(m_GameBoard.getOccupied(), Square(x.from)));

		m_GameBoard.setPiece(c, none, set(m_GameBoard.getPiece(c, none), Square(x.to))); //FILL NEW PLACE
		m_GameBoard.setPiece(c, none, reset(m_GameBoard.getPiece(c, none), Square(x.from))); // OLD PLACE EMPTY
		switch (x.flag)
		{
		case 0:
		case 1:
			m_GameBoard.setPiece(c, p, set(m_GameBoard.getPiece(c, p), Square(x.to))); //FILL NEW PLACE
			m_GameBoard.setPiece(c, p, toggle(m_GameBoard.getPiece(c, p), Square(x.from))); // OLD PLACE EMPTY
			break;
		case 2:
			pCaptured = whatPiece(m_GameBoard, x.to, opposite(c));
			if (isItPromotion(m_GameBoard, x.to, pCaptured, opposite(c)))
			{
				m_GameBoard.removePromotionWithSquare(opposite(c), pCaptured, x.to);
			}
			else
			{
				m_GameBoard.setPiece(opposite(c), pCaptured, reset(m_GameBoard.getPiece(opposite(c), pCaptured), Square(x.to)));
			}
			m_GameBoard.setPiece(opposite(c), none, reset(m_GameBoard.getPiece(opposite(c), none), Square(x.to)));


			m_GameBoard.setPiece(c, p, set(m_GameBoard.getPiece(c, p), Square(x.to))); //FILL NEW PLACE
			m_GameBoard.setPiece(c, p, toggle(m_GameBoard.getPiece(c, p), Square(x.from))); // OLD PLACE EMPTY
			break;
		case 3:
			m_GameBoard.setPromotionWithSquare(c, knight, x.to);
			m_GameBoard.setPiece(c, p, toggle(m_GameBoard.getPiece(c, p), Square(x.from))); // OLD PLACE EMPTY
			break;
		case 4:
			m_GameBoard.setPromotionWithSquare(c, bishop, x.to);
			m_GameBoard.setPiece(c, p, toggle(m_GameBoard.getPiece(c, p), Square(x.from))); // OLD PLACE EMPTY
			break;
		case 5:
			m_GameBoard.setPromotionWithSquare(c, rook, x.to);
			m_GameBoard.setPiece(c, p, toggle(m_GameBoard.getPiece(c, p), Square(x.from))); // OLD PLACE EMPTY
			break;
		case 6:
			m_GameBoard.setPromotionWithSquare(c, queen, x.to);
			m_GameBoard.setPiece(c, p, toggle(m_GameBoard.getPiece(c, p), Square(x.from))); // OLD PLACE EMPTY
			break;
		case 7:
			pCaptured = whatPiece(m_GameBoard, x.to, opposite(c));
			if (isItPromotion(m_GameBoard, x.to, pCaptured, opposite(c)))
			{
				m_GameBoard.removePromotionWithSquare(opposite(c), pCaptured, x.to);
			}
			else
			{
				m_GameBoard.setPiece(opposite(c), pCaptured, reset(m_GameBoard.getPiece(opposite(c), pCaptured), Square(x.to)));
			}
			m_GameBoard.setPiece(opposite(c), none, reset(m_GameBoard.getPiece(opposite(c), none), Square(x.to)));

			m_GameBoard.setPiece(c, p, toggle(m_GameBoard.getPiece(c, p), Square(x.from))); // OLD PLACE EMPTY
			m_GameBoard.setPromotionWithSquare(c, queen, x.to);
			break;
		case 8:
			pCaptured = whatPiece(m_GameBoard, x.to, opposite(c));
			if (isItPromotion(m_GameBoard, x.to, pCaptured, opposite(c)))
			{
				m_GameBoard.removePromotionWithSquare(opposite(c), pCaptured, x.to);
			}
			else
			{
				m_GameBoard.setPiece(opposite(c), pCaptured, reset(m_GameBoard.getPiece(opposite(c), pCaptured), Square(x.to)));
			}
			m_GameBoard.setPiece(opposite(c), none, reset(m_GameBoard.getPiece(opposite(c), none), Square(x.to)));

			m_GameBoard.setPiece(c, p, toggle(m_GameBoard.getPiece(c, p), Square(x.from))); // OLD PLACE EMPTY
			m_GameBoard.setPromotionWithSquare(c, knight, x.to);
			break;
		case 9:
			pCaptured = whatPiece(m_GameBoard, x.to, opposite(c));
			if (isItPromotion(m_GameBoard, x.to, pCaptured, opposite(c)))
			{
				m_GameBoard.removePromotionWithSquare(opposite(c), pCaptured, x.to);
			}
			else
			{
				m_GameBoard.setPiece(opposite(c), pCaptured, reset(m_GameBoard.getPiece(opposite(c), pCaptured), Square(x.to)));
			}
			m_GameBoard.setPiece(opposite(c), none, reset(m_GameBoard.getPiece(opposite(c), none), Square(x.to)));

			m_GameBoard.setPiece(c, p, toggle(m_GameBoard.getPiece(c, p), Square(x.from))); // OLD PLACE EMPTY
			m_GameBoard.setPromotionWithSquare(c, bishop, x.to);
			break;
		case 10:
			pCaptured = whatPiece(m_GameBoard, x.to, opposite(c));
			if (isItPromotion(m_GameBoard, x.to, pCaptured, opposite(c)))
			{
				m_GameBoard.removePromotionWithSquare(opposite(c), pCaptured, x.to);
			}
			else
			{
				m_GameBoard.setPiece(opposite(c), pCaptured, reset(m_GameBoard.getPiece(opposite(c), pCaptured), Square(x.to)));
			}
			m_GameBoard.setPiece(opposite(c), none, reset(m_GameBoard.getPiece(opposite(c), none), Square(x.to)));

			m_GameBoard.setPiece(c, p, toggle(m_GameBoard.getPiece(c, p), Square(x.from))); // OLD PLACE EMPTY
			m_GameBoard.setPromotionWithSquare(c, rook, x.to);
		default:
			break;
		}
	}
}

void MoveGenerator::_UpdateBoard(Bitboard& bBoard, Move x, Piece p, Color c)
{
	{
		Piece pCaptured;

		bBoard.setEmpty(set(bBoard.getEmpty(), Square(x.from)));
		bBoard.setEmpty(reset(bBoard.getEmpty(), Square(x.to)));

		bBoard.setOccubied(set(bBoard.getOccupied(), Square(x.to)));
		bBoard.setOccubied(reset(bBoard.getOccupied(), Square(x.from)));

		bBoard.setPiece(c, none, set(bBoard.getPiece(c, none), Square(x.to))); //FILL NEW PLACE
		bBoard.setPiece(c, none, reset(bBoard.getPiece(c, none), Square(x.from))); // OLD PLACE EMPTY
		switch (x.flag)
		{
		case 0:
		case 1:
			bBoard.setPiece(c, p, set(bBoard.getPiece(c, p), Square(x.to))); //FILL NEW PLACE
			bBoard.setPiece(c, p, toggle(bBoard.getPiece(c, p), Square(x.from))); // OLD PLACE EMPTY
			break;
		case 2:
			pCaptured = whatPiece(bBoard, x.to, opposite(c));
			if (isItPromotion(bBoard, x.to, pCaptured, opposite(c)))
			{
				bBoard.removePromotionWithSquare(opposite(c), pCaptured, x.to);
			}
			else
			{
				bBoard.setPiece(opposite(c), pCaptured, reset(bBoard.getPiece(opposite(c), pCaptured), Square(x.to)));
			}
			bBoard.setPiece(opposite(c), none, reset(bBoard.getPiece(opposite(c), none), Square(x.to)));


			bBoard.setPiece(c, p, set(bBoard.getPiece(c, p), Square(x.to))); //FILL NEW PLACE
			bBoard.setPiece(c, p, toggle(bBoard.getPiece(c, p), Square(x.from))); // OLD PLACE EMPTY
			break;
		case 3:
			bBoard.setPromotionWithSquare(c, knight, x.to);
			bBoard.setPiece(c, p, toggle(bBoard.getPiece(c, p), Square(x.from))); // OLD PLACE EMPTY
			break;
		case 4:
			bBoard.setPromotionWithSquare(c, bishop, x.to);
			bBoard.setPiece(c, p, toggle(bBoard.getPiece(c, p), Square(x.from))); // OLD PLACE EMPTY
			break;
		case 5:
			bBoard.setPromotionWithSquare(c, rook, x.to);
			bBoard.setPiece(c, p, toggle(bBoard.getPiece(c, p), Square(x.from))); // OLD PLACE EMPTY
			break;
		case 6:
			bBoard.setPromotionWithSquare(c, queen, x.to);
			bBoard.setPiece(c, p, toggle(bBoard.getPiece(c, p), Square(x.from))); // OLD PLACE EMPTY
			break;
		case 7:
			pCaptured = whatPiece(bBoard, x.to, opposite(c));
			if (isItPromotion(bBoard, x.to, pCaptured, opposite(c)))
			{
				bBoard.removePromotionWithSquare(opposite(c), pCaptured, x.to);
			}
			else
			{
				bBoard.setPiece(opposite(c), pCaptured, reset(bBoard.getPiece(opposite(c), pCaptured), Square(x.to)));
			}
			bBoard.setPiece(opposite(c), none, reset(bBoard.getPiece(opposite(c), none), Square(x.to)));

			bBoard.setPiece(c, p, toggle(bBoard.getPiece(c, p), Square(x.from))); // OLD PLACE EMPTY
			bBoard.setPromotionWithSquare(c, queen, x.to);
			break;
		case 8:
			pCaptured = whatPiece(bBoard, x.to, opposite(c));
			if (isItPromotion(bBoard, x.to, pCaptured, opposite(c)))
			{
				bBoard.removePromotionWithSquare(opposite(c), pCaptured, x.to);
			}
			else
			{
				bBoard.setPiece(opposite(c), pCaptured, reset(bBoard.getPiece(opposite(c), pCaptured), Square(x.to)));
			}
			bBoard.setPiece(opposite(c), none, reset(bBoard.getPiece(opposite(c), none), Square(x.to)));

			bBoard.setPiece(c, p, toggle(bBoard.getPiece(c, p), Square(x.from))); // OLD PLACE EMPTY
			bBoard.setPromotionWithSquare(c, knight, x.to);
			break;
		case 9:
			pCaptured = whatPiece(bBoard, x.to, opposite(c));
			if (isItPromotion(bBoard, x.to, pCaptured, opposite(c)))
			{
				bBoard.removePromotionWithSquare(opposite(c), pCaptured, x.to);
			}
			else
			{
				bBoard.setPiece(opposite(c), pCaptured, reset(bBoard.getPiece(opposite(c), pCaptured), Square(x.to)));
			}
			bBoard.setPiece(opposite(c), none, reset(bBoard.getPiece(opposite(c), none), Square(x.to)));

			bBoard.setPiece(c, p, toggle(bBoard.getPiece(c, p), Square(x.from))); // OLD PLACE EMPTY
			bBoard.setPromotionWithSquare(c, bishop, x.to);
			break;
		case 10:
			pCaptured = whatPiece(bBoard, x.to, opposite(c));
			if (isItPromotion(bBoard, x.to, pCaptured, opposite(c)))
			{
				bBoard.removePromotionWithSquare(opposite(c), pCaptured, x.to);
			}
			else
			{
				bBoard.setPiece(opposite(c), pCaptured, reset(bBoard.getPiece(opposite(c), pCaptured), Square(x.to)));
			}
			bBoard.setPiece(opposite(c), none, reset(bBoard.getPiece(opposite(c), none), Square(x.to)));

			bBoard.setPiece(c, p, toggle(bBoard.getPiece(c, p), Square(x.from))); // OLD PLACE EMPTY
			bBoard.setPromotionWithSquare(c, rook, x.to);
		default:
			break;
		}
	}
}

std::vector<Move> MoveGenerator::GetPieceMoveList(Color c, Piece p)
{
	{
		//50-Move Rule
		if (m_Counter >= 50)
		{
			gameState = GameState::Draw;
			return vec<Move>(0);
		}
		vec<Move> _results = vec<Move>();
		vec<Move> temp;

		switch (p)
		{
		case none:
			_results = vec<Move>(0);
			break;
		case pawn:
			if (m_GameBoard.getPiece(c, p) != 0)
			{
				_results = generatePawnAttacks(c);
				temp = generatePawnPushes(c);
				for (size_t i = 0; i < temp.size(); i++)
				{
					_results.push_back(temp[i]);
				}
			}
			break;
		case knight:
			if (m_GameBoard.getPiece(c, p) != 0)
			{
				_results = generateKnightAttacks(c);
				if (m_GameBoard.getPromotion(c, p) != 0)
				{
					temp = generateKnightPromotionAttacks(c);
					for (size_t i = 0; i < temp.size(); i++)
					{
						_results.push_back(temp[i]);
					}
				}
			}
			break;
		case bishop:
			if (m_GameBoard.getPiece(c, p) != 0)
			{
				_results = generateBishopAttack(c);
				if (m_GameBoard.getPromotion(c, p) != 0)
				{
					temp = generateBishopPromotionAttacks(c);
					for (size_t i = 0; i < temp.size(); i++)
					{
						_results.push_back(temp[i]);
					}
				}
			}
			break;
		case rook:
			if (m_GameBoard.getPiece(c, p) != 0)
			{
				_results = generateRookAttacks(c);
				if (m_GameBoard.getPromotion(c, p) != 0)
				{
					temp = generateRookPromotionAttacks(c);
					for (size_t i = 0; i < temp.size(); i++)
					{
						_results.push_back(temp[i]);
					}
				}
			}
			break;
		case queen:

			if (m_GameBoard.getPiece(c, p) != 0)
			{
				_results = generateQueenAttacks(c);
				if (m_GameBoard.getPromotion(c, p) != 0)
				{
					temp = generateQueenPromotionAttacks(c);
					for (size_t i = 0; i < temp.size(); i++)
					{
						_results.push_back(temp[i]);
					}
				}
			}
			break;
		case king:
			_results = generateKingAttacks(c);
			break;
		}
		if (gameState == GameState::CheckBlack || gameState == GameState::CheckWhite)
		{
			//std::cout << "SOMEONE ATTACKING KING " << std::endl;
			_results = filterAttacks(_results, c);
			//gameState = GameState::Normal;
		}

		//isKingUnderThreat(_results, c);

		return _results;
	}
}

std::vector<Move> MoveGenerator::GetPieceMoveList(Color c, Piece p, Square piece_square)
{
	{
		vec<Move> result = GetPieceMoveList(c, p);
		vec<Move> filterd_result;
		for (int i = 0; i < result.size(); i++)
		{
			if (result[i].from == piece_square)
				filterd_result.push_back(result[i]);
		}
		return filterd_result;
	}
}

void MoveGenerator::MakeMove(Move mov, Piece p, Color c)
{
	{
		(
			mov.flag == MoveFlag::Capture ||
			mov.flag == MoveFlag::Double_Pawn_Push ||
			(whatPiece(GameBoard(), Square(mov.from), c) == Piece::pawn)) ? m_Counter = 0 : m_Counter++;

		_UpdateBoard(mov, p, c);
		if (isKingAttacked(GameBoard(), c))
		{
			std::cout << "A check " << std::endl;

			gameState = (c == white) ? GameState::CheckBlack : GameState::CheckWhite;
		}
		else
		{
			gameState = GameState::Normal;
		}
	}
}

void MoveGenerator::MakePromotion(Move mov, Color c, Promotion flag)
{
	{
		mov.flag = MoveFlag(pickPromotion(flag));
		_UpdateBoard(mov, Piece::pawn, c);
	}
}

void MoveGenerator::UndoMove(Move x, Piece p, Color c)
{
	{
		Move undo = x;
		std::swap(undo.to, undo.from);
		_UpdateBoard(undo, p, c);
	}
}

std::vector<Move> MoveGenerator::_GenerateMovesList(u64 possibleMoveBB, int source, short flagf)
{
	std::vector<Move> result;
	int idx = 0;
	do
	{
		if (possibleMoveBB & 1)
		{// found 1
			Move m = Move(source, idx);
			/*m.from = source;
			m.to = idx;*/
			m.flag = MoveFlag(flagf);
			result.push_back(m);
		}
		possibleMoveBB >>= 1;
		idx++;
	}
	while (possibleMoveBB);
	return result;
}

std::vector<Move> MoveGenerator::_GeneratePawnAttackList(u64 possibleMoveBB, int source, Color c)
{
	std::vector<Move> result;
	int idx = 0;
	do
	{
		if (possibleMoveBB & 1)
		{// found 1
			Move m = Move(source, idx);
			/*m.from = source;
			m.to = idx;*/
			if (validForPromotion(Square(m.to), c))
				m.flag = MoveFlag(7);
			else
				m.flag = MoveFlag(2);
			result.push_back(m);
		}
		possibleMoveBB >>= 1;
		idx++;
	}
	while (possibleMoveBB);
	return result;
}

std::vector<Move> MoveGenerator::_GeneratePawnPushesList(u64 possibleMoveBB, int source, Color c, bool doublePush)
{
	std::vector<Move> result;
	int idx = 0;
	do
	{
		if (possibleMoveBB & 1)
		{// found 1
			Move m = Move(source, idx);
			/*m.from = source;
			m.to = idx;*/
			if (validForPromotion(Square(m.to), c))
				m.flag = MoveFlag(2);
			else
			{
				if (isPushable(c, Square(m.from)))
					m.flag = MoveFlag(1);
				else
					m.flag = MoveFlag(0);
			}
			result.push_back(m);
		}
		possibleMoveBB >>= 1;
		idx++;
	}
	while (possibleMoveBB);
	return result;
}

std::vector<int> MoveGenerator::Serialize(u64 t)
{
	if (t)
	{
		std::vector<int> result;
		int i;
		do
		{
			i = firstBit(t); // square index from 0..63
			result.push_back(i);
		}
		while (t &= t - 1);
		return result;
	}
	std::vector<int> result(0);
	return result;
}

std::vector<Move> MoveGenerator::generateBishopAttack(Color c)
{
	u64 board = m_GameBoard.getPiece(c, bishop);
	vec<int> sources = Serialize(board);

	vec<Move> quietMoves;
	vec<Move> captureMoves;
	Color cOfEnemy = opposite(c);

	vec<Move> result;
	u64 attack;

	for (auto i : sources)
	{
		attack = bishopAttackWithoutBlockers(singleBitSet(Square(i)), m_GameBoard.getEmpty());
		attack = dontAttackAllay(attack, m_GameBoard.getPiece(c, none));
		quietMoves = _GenerateMovesList(quietMove(attack, m_GameBoard.getPiece(cOfEnemy, none)), i, 0);
		captureMoves = _GenerateMovesList(attackEnemy(attack, m_GameBoard.getPiece(cOfEnemy, none)), i, 2);
		result.insert(result.end(), quietMoves.begin(), quietMoves.end());
		result.insert(result.end(), captureMoves.begin(), captureMoves.end());
	}
	return result;
}

std::vector<Move> MoveGenerator::generateKnightAttacks(Color c)
{
	u64 board = m_GameBoard.getPiece(c, knight);
	vec<int> sources = Serialize(board);

	vec<Move> quietMoves;
	vec<Move> captureMoves;
	Color cOfEnemy = opposite(c);

	vec<Move> result;
	u64 attack;

	for (auto i : sources)
	{
		attack = knightAttack(singleBitSet(Square(i)));

		attack = dontAttackAllay(attack, m_GameBoard.getPiece(c, none));
		quietMoves = _GenerateMovesList(quietMove(attack, m_GameBoard.getPiece(cOfEnemy, none)), i, 0);
		captureMoves = _GenerateMovesList(attackEnemy(attack, m_GameBoard.getPiece(cOfEnemy, none)), i, 2);
		result.insert(result.end(), quietMoves.begin(), quietMoves.end());
		result.insert(result.end(), captureMoves.begin(), captureMoves.end());
	}
	return result;
}

std::vector<Move> MoveGenerator::generateRookAttacks(Color c)
{
	u64 board = m_GameBoard.getPiece(c, rook);
	vec<int> sources = Serialize(board);

	vec<Move> quietMoves;
	vec<Move> captureMoves;
	Color cOfEnemy = opposite(c);

	vec<Move> result;
	u64 attack;

	for (auto i : sources)
	{
		//std::cout << whatPiece(m_GameBoard, Square(i), c) << std::endl;
		attack = rookAttackWithoutBlockers(singleBitSet(Square(i)), m_GameBoard.getEmpty());

		attack = dontAttackAllay(attack, m_GameBoard.getPiece(c, none));
		quietMoves = _GenerateMovesList(quietMove(attack, m_GameBoard.getPiece(cOfEnemy, none)), i, 0);
		captureMoves = _GenerateMovesList(attackEnemy(attack, m_GameBoard.getPiece(cOfEnemy, none)), i, 2);
		result.insert(result.end(), quietMoves.begin(), quietMoves.end());
		result.insert(result.end(), captureMoves.begin(), captureMoves.end());
	}
	return result;
}

std::vector<Move> MoveGenerator::generateKingAttacks(Color c)
{
	u64 board = m_GameBoard.getPiece(c, king);

	int source = firstBit(board);

	std::vector<Move> quietMoves;
	std::vector<Move> captureMoves;
	Color cOfEnemy = opposite(c);

	std::vector<Move> result;
	u64 attack;
	attack = kingAttacks(singleBitSet(Square(source)));
	attack = dontAttackAllay(attack, m_GameBoard.getPiece(c, none));
	quietMoves = _GenerateMovesList(quietMove(attack, m_GameBoard.getPiece(cOfEnemy, none)), source, 0);
	captureMoves = _GenerateMovesList(attackEnemy(attack, m_GameBoard.getPiece(cOfEnemy, none)), source, 2);
	result.insert(result.end(), quietMoves.begin(), quietMoves.end());
	result.insert(result.end(), captureMoves.begin(), captureMoves.end());
	return result;
}

std::vector<Move> MoveGenerator::generateQueenAttacks(Color c)
{
	u64 board = m_GameBoard.getPiece(c, queen);

	int source = firstBit(board);

	std::vector<Move> quietMoves;
	std::vector<Move> captureMoves;
	Color cOfEnemy = opposite(c);

	std::vector<Move> result;
	u64 attack;
	attack = queenAttacksWithoutBlockers(singleBitSet(Square(source)), m_GameBoard.getEmpty());
	attack = dontAttackAllay(attack, m_GameBoard.getPiece(c, none));
	quietMoves = _GenerateMovesList(quietMove(attack, m_GameBoard.getPiece(cOfEnemy, none)), source, 0);
	captureMoves = _GenerateMovesList(attackEnemy(attack, m_GameBoard.getPiece(cOfEnemy, none)), source, 2);

	result.insert(result.end(), quietMoves.begin(), quietMoves.end());


	result.insert(result.end(), captureMoves.begin(), captureMoves.end());

	return result;
}

std::vector<Move> MoveGenerator::generatePawnAttacks(Color c)
{
	u64 board = m_GameBoard.getPiece(c, pawn);

	std::vector<int> sources = Serialize(board);

	std::vector<Move> captureMoves; // could have capture or promotion
	Color cOfEnemy = opposite(c);

	std::vector<Move> result;
	u64 attack;

	for (auto i : sources)
	{
		attack = allPawnLegalAttacks(singleBitSet(Square(i)), m_GameBoard.getPiece(cOfEnemy, none), c);

		captureMoves = _GeneratePawnAttackList(attack, i, c);
		result.insert(result.end(), captureMoves.begin(), captureMoves.end());
	}
	return result;
}

std::vector<Move> MoveGenerator::generatePawnPushes(Color c)
{
	u64 board = m_GameBoard.getPiece(c, pawn);
	bool doublePush;
	std::vector<int> sources = Serialize(board);

	std::vector<Move> quietMove;

	std::vector<Move> result;
	u64 attack;

	for (auto i : sources)
	{
		if (isPushable(c, Square(i)))
		{
			attack = allPawnPushesWithoutBlockers(singleBitSet(Square(i)), c, m_GameBoard.getOccupied())
				| allPawnDoublePushesWithoutBlockers(singleBitSet(Square(i)), c, m_GameBoard.getOccupied());
			doublePush = true;
		}
		else
		{
			attack = allPawnPushesWithoutBlockers(singleBitSet(Square(i)), c, m_GameBoard.getOccupied());
			doublePush = false;
		}
		quietMove = _GeneratePawnPushesList(attack, i, c, doublePush);
		result.insert(result.end(), quietMove.begin(), quietMove.end());
	}
	return result;
}

std::vector<Move> MoveGenerator::generateQueenPromotionAttacks(Color c)
{
	u64 board = GameBoard().getQueenPromotion(c);

	vec<int> sources = Serialize(board);

	vec<Move> quietMoves;
	vec<Move> captureMoves;
	Color cOfEnemy = opposite(c);

	vec<Move> result;
	u64 attack;

	for (auto i : sources)
	{
		attack = queenAttacksWithoutBlockers(Square(i), m_GameBoard.getEmpty());

		attack = dontAttackAllay(attack, m_GameBoard.getPiece(c, none));
		quietMoves = _GenerateMovesList(quietMove(attack, m_GameBoard.getPiece(cOfEnemy, none)), i, 0);
		captureMoves = _GenerateMovesList(attackEnemy(attack, m_GameBoard.getPiece(cOfEnemy, none)), i, 2);
		result.insert(result.end(), quietMoves.begin(), quietMoves.end());
		result.insert(result.end(), captureMoves.begin(), captureMoves.end());
	}
	return result;
}

std::vector<Move> MoveGenerator::generateKnightPromotionAttacks(Color c)
{
	u64 board;
	board = GameBoard().getKnightPromotion(c);

	std::vector<int> sources = Serialize(board);

	std::vector<Move> quietMoves;
	std::vector<Move> captureMoves;
	Color cOfEnemy = opposite(c);

	std::vector<Move> result;
	u64 attack;
	for (auto i : sources)
	{
		attack = knightAttack(singleBitSet(Square(i)));
		attack = dontAttackAllay(attack, GameBoard().getPiece(c, none));
		quietMoves = _GenerateMovesList(quietMove(attack, GameBoard().getPiece(cOfEnemy, none)), i, 0);
		captureMoves = _GenerateMovesList(attackEnemy(attack, GameBoard().getPiece(cOfEnemy, none)), i, 2);
		result.insert(result.end(), quietMoves.begin(), quietMoves.end());
		result.insert(result.end(), captureMoves.begin(), captureMoves.end());
	}
	return result;
}

std::vector<Move> MoveGenerator::generateBishopPromotionAttacks(Color c)
{
	u64 board;
	board = GameBoard().getBishopPromotion(c);

	vec<int> sources = Serialize(board);

	vec<Move> quietMoves;
	vec<Move> captureMoves;
	Color cOfEnemy = opposite(c);

	vec<Move> result;
	u64 attack;
	for (auto i : sources)
	{
		attack = bishopAttackWithoutBlockers(Square(i), GameBoard().getEmpty());

		attack = dontAttackAllay(attack, GameBoard().getPiece(c, none));
		quietMoves = _GenerateMovesList(quietMove(attack, GameBoard().getPiece(cOfEnemy, none)), i, 0);
		captureMoves = _GenerateMovesList(attackEnemy(attack, GameBoard().getPiece(cOfEnemy, none)), i, 2);
		result.insert(result.end(), quietMoves.begin(), quietMoves.end());
		result.insert(result.end(), captureMoves.begin(), captureMoves.end());
	}
	return result;
}

std::vector<Move> MoveGenerator::generateRookPromotionAttacks(Color c)
{
	u64 board = GameBoard().getRookPromotion(c);
	std::vector<int> sources = Serialize(board);

	std::vector<Move> quietMoves;
	std::vector<Move> captureMoves;
	Color cOfEnemy = opposite(c);

	std::vector<Move> result;
	u64 attack;
	for (int i : sources)
	{
		attack = rookAttackWithoutBlockers(Square(i), GameBoard().getEmpty());

		attack = dontAttackAllay(attack, GameBoard().getPiece(c, none));
		quietMoves = _GenerateMovesList(quietMove(attack, GameBoard().getPiece(cOfEnemy, none)), i, 0);
		captureMoves = _GenerateMovesList(attackEnemy(attack, GameBoard().getPiece(cOfEnemy, none)), i, 2);
		result.insert(result.end(), quietMoves.begin(), quietMoves.end());
		result.insert(result.end(), captureMoves.begin(), captureMoves.end());
	}
	return result;
}

void MoveGenerator::isKingUnderThreat(vec<Move> _list, Color c)
{
	m_AttackingKing.clear();
	for (auto I : _list)
	{
		if (whatPiece(GameBoard(), I.to, opposite(c)) == Piece::king)
		{
			std::cout << "Check is true " << std::endl;
			//Check on ~c color
			m_AttackingKing.push_back(I);
		}
	}
	if (m_AttackingKing.size() != 0)
	{
		gameState = c == black ? GameState::CheckWhite : GameState::CheckBlack;
	}

}

Bitboard MoveGenerator::GameBoard()
{
	//User needn't set game board, a getter is enough
	return m_GameBoard;
	gameState = GameState::Normal;
}

std::vector<Move> MoveGenerator::filterAttacks(vec<Move> _attackList, Color c)
{
	{
		vec<Move> legalMoves;
		Bitboard test;

		for (auto I : _attackList)
		{
			test = m_GameBoard;
			_UpdateBoard(test, I, whatPiece(test, I.from, c), c);
			if (!isKingAttacked(test, opposite(c)))
			{
				legalMoves.push_back(I);
			}
		}
		return legalMoves;
	}
}

int MoveGenerator::pickPromotion(Promotion _choice)
{
	return int(_choice);
}

MoveGenerator::MoveGenerator()
{
	gameState = GameState::Normal;
	m_Counter = 0;
}
