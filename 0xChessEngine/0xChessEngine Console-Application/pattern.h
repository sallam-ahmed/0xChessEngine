#pragma once


#include "bitboard.h"
#include "extrasbitboard.h"
using namespace BASE;

//pawn fills
/* A pawn may be a :
*  1) passer : no piece infornt of it (open)
*  2) candidate : force itself to be a passer (half open)
*  3) isolated : has no friendly pawn on files around it
*/
/* heavy pieces :
*  king, queen, rock
*/

// front fill & rear fill
/* example : a white pawn on a4
* a front fill would be : 1 on squares : a5, a6, a7, a8
* a rear fill: 1 on squares: a3, a2, a1
*  (fill the file)
*/

//those also used for filling empty bitboards

inline u64 northFill(u64 pawns) //pawns -> white or black
{
	pawns |= (pawns << 8);
	pawns |= (pawns << 16);
	pawns |= (pawns << 32);
	return pawns;
}

inline u64 southFill(u64 pawns)
{
	pawns |= (pawns >> 8);
	pawns |= (pawns >> 16);
	pawns |= (pawns >> 32);
	return pawns;
}

//other fills for ray attack
// remember for wrapping we use masks notAFile for east & notHFile for west
inline u64 eastFill(u64 t)
{
	u64 x1 = BASE::notAFile & (BASE::notAFile << 1);
	u64 x2 = x1 & (x1 << 2);
	t |= BASE::notAFile & (t << 1);
	t |= x1 & (t << 2);
	t |= x2 & (t << 4);
	return t;
}

inline u64 westFill(u64 t)
{
	u64 x1 = BASE::notHFile & (BASE::notHFile >> 1);
	u64 x2 = x1 & (x1 >> 2);
	t |= BASE::notHFile & (t >> 1);
	t |= x1 & (t >> 2);
	t |= x2 & (t >> 4);
	return t;
}

// the following fills needs you to revise the compass rose in bitboard.cpp

//(9, 18, 36)
inline u64 noEaFill(u64 t)
{
	u64 x1 = BASE::notAFile & (BASE::notAFile << 9);
	u64 x2 = x1 & (x1 << 18);
	t |= BASE::notAFile & (t << 9);
	t |= x1 & (t << 18);
	t |= x2 & (t << 36);
	return t;
}

inline u64 soWeFill(u64 t) // note: south not north
{
	u64 x1 = BASE::notHFile & (BASE::notHFile >> 9);
	u64 x2 = x1 & (x1 >> 18);
	t |= BASE::notHFile & (t >> 9);
	t |= x1 & (t >> 18);
	t |= x2 & (t >> 36);
	return t;
}

// noWe & soEa : (7, 14, 28)

inline u64 noWeFill(u64 t)
{
	u64 x1 = BASE::notHFile & (BASE::notHFile << 7);
	u64 x2 = x1 & (x1 << 14);
	t |= BASE::notHFile & (t << 7);
	t |= x1 & (t << 14);
	t |= x2 & (t << 28);
	return t;
}

inline u64 soEaFill(u64 t)
{
	u64 x1 = BASE::notAFile & (BASE::notAFile >> 7);
	u64 x2 = x1 & (x1 >> 14);
	t |= BASE::notAFile & (t >> 7);
	t |= x1 & (t >> 14);
	t |= x2 & (t >> 28);
	return t;
}

// occluded fill : still using the same compass rose in bitboard.cpp
// can't be used with blockers
// blockers -> king, pawn, knight

inline u64 northOccluded(u64 t, u64 empty)
{
	t |= empty & (t << 8);
	empty &= (empty << 8);
	t |= empty & (t << 16);
	empty &= (empty << 16);
	t |= empty & (t << 32);
	return t;
}

inline u64 southOccluded(u64 t, u64 empty)
{
	t |= empty & (t >> 8);
	empty &= (empty >> 8);
	t |= empty & (t >> 16);
	empty &= (empty >> 16);
	t |= empty & (t >> 32);
	return t;
}

// Note for me: don't forget wrapping
inline u64 eastOccluded(u64 t, u64 empty)
{
	empty &= BASE::notAFile;
	t |= empty & (t << 1);
	empty &= (empty << 1);
	t |= empty & (t << 2);
	empty &= empty << 2;
	t |= empty & (t << 4);
	return t;
}

inline u64 westOccluded(u64 t, u64 empty)
{
	empty &= BASE::notHFile;
	t |= empty & (t >> 1);
	empty &= (empty >> 1);
	t |= empty & (t >> 2);
	empty &= empty >> 2;
	t |= empty & (t >> 4);
	return t;
}

inline u64 noEaOccluded(u64 t, u64 empty)
{
	empty &= BASE::notAFile;
	t |= empty & (t << 9);
	empty &= (empty << 9);
	t |= empty & (t << 18);
	empty &= (empty << 18);
	t |= empty & (t << 36);
	return t;
}

inline u64 noWeOccluded(u64 t, u64 empty)
{
	empty &= BASE::notHFile;
	t |= empty & (t << 7);
	empty &= (empty << 7);
	t |= empty & (t << 14);
	empty &= (empty << 14);
	t |= empty & (t << 28);
	return t;
}

inline u64 soEaOccluded(u64 t, u64 empty)
{
	empty &= BASE::notAFile;
	t |= empty & (t >> 7);
	empty &= (empty >> 7);
	t |= empty & (t >> 14);
	empty &= (empty >> 14);
	t |= empty & (t >> 28);
	return t;
}

inline u64 soWeOccluded(u64 t, u64 empty)
{
	empty &= BASE::notHFile;
	t |= empty & (t >> 9);
	empty &= (empty >> 9);
	t |= empty & (t >> 18);
	empty &= (empty >> 18);
	t |= empty & (t >> 36);
	return t;
}

inline u64 occludedFill(u64 t, u64 pro, int dir8)
{
	int r = BASE::shift[dir8]; // {+-1,7,8,9}
	pro &= BASE::avoidWrap[dir8];
	t |= pro & rotateLeft(t, r);
	pro &= rotateLeft(pro, r);
	t |= pro & rotateLeft(t, 2 * r);
	pro &= rotateLeft(pro, 2 * r);
	t |= pro & rotateLeft(t, 4 * r);
	return t;
}

// file fill : north fill union south fill

inline u64 fileFill(u64 t)
{
	return northFill(t) | southFill(t);
}

// pawn span : span is distance either to promotion or to rear

// span = north or south fill shifted one step in the fill direction
//          (remember nortOne & soutOne in shifting in bitboard.cpp)

// white
inline u64 wFrontSpan(u64 wPawns)
{
	return nortOne(northFill(wPawns));
}

inline u64 wRearSpan(u64 wPawns)
{
	return soutOne(southFill(wPawns));
}

//black
inline u64 bFrontSpan(u64 bPawns)
{
	return soutOne(southFill(bPawns));
}

inline u64 bRearSpan(u64 bPawns)
{
	return nortOne(northFill(bPawns));
}

//interspans : the intersection of white & black front spans

inline u64 interSpan(u64 wPawns, u64 bPawns)
{
	return wFrontSpan(wPawns) & bFrontSpan(bPawns);
}

// stop square : pawn can get to in one non_capturing move

inline u64 wStop(u64 wPawns)
{
	return nortOne(wPawns);
}

inline u64 bStop(u64 bPawns)
{
	return soutOne(bPawns);
}

//Telestop squares: squares further the stop square

inline u64 wTeleStops(u64 wPawns)
{
	return wFrontSpan(wStop(wPawns)) ^ wStop(wPawns);
}

inline u64 bTeleStops(u64 bPawns)
{
	return bFrontSpan(bStop(bPawns)) ^ bStop(bPawns);
}

//attack span of a pawn (ex : on square b2) is the front span (or rear span) of squares a2 & c2
// a2 is west, c2 is east

//white
inline u64 wEastFrontAttackSpan(u64 wPawn)
{
	return eastOne(wFrontSpan(wPawn));
}

inline u64 wWestFrontAttackSpan(u64 wPawn)
{
	return westOne(wFrontSpan(wPawn));
}

inline u64 wEastRearAttackSpan(u64 wPawn)
{
	return eastOne(wRearSpan(wPawn));
}

inline u64 wWestRearAttackSpan(u64 wPawn)
{
	return westOne(wRearSpan(wPawn));
}

//black
inline u64 bEastFrontAttackSpan(u64 bPawn)
{
	return eastOne(bFrontSpan(bPawn));
}

inline u64 bWestFrontAttackSpan(u64 bPawn)
{
	return westOne(bFrontSpan(bPawn));
}

inline u64 bEastRearAttackSpan(u64 bPawn)
{
	return eastOne(bRearSpan(bPawn));
}

inline u64 bWestRearAttackSpan(u64 bPawn)
{
	return westOne(bRearSpan(bPawn));
}

//file attack is the same for both colors

inline u64 eastFileAttack(u64 pawn)
{
	return eastOne(fileFill(pawn));
}

inline u64 westFileAttack(u64 pawn)
{
	return westOne(fileFill(pawn));
}


//knight
/* all attacking directions
(notH)     (notA)

noNoWe    noNoEa
+15  +17
|     |
(notGH)   noWeWe  +6 __|     |__+10  noEaEa   (notAB)
\   /
>0<
__ /   \ __
(notGH)   soWeWe -10   |     |   -6  soEaEa   (notAB)
|     |
-17  -15
soSoWe    soSoEa

(notH)     (notA)
+ : <<
- : >>
*/

inline u64 noNoWe(u64 t)
{
	return (t << 15) & BASE::notHFile;
}

inline u64 noNOEa(u64 t)
{
	return (t << 17) & BASE::notAFile;
}

inline u64 noWeWe(u64 t)
{
	return (t << 6) & BASE::notGHFile;
}

inline u64 noEaEa(u64 t)
{
	return (t << 10) & BASE::notABFile;
}

inline u64 soWeWe(u64 t)
{
	return (t >> 10) & BASE::notGHFile;
}

inline u64 soEaEa(u64 t)
{
	return (t >> 6) & BASE::notABFile;
}

inline u64 soSoWe(u64 t)
{
	return (t >> 17) & BASE::notHFile;
}

inline u64 soSoEa(u64 t)
{
	return (t >> 15) & BASE::notAFile;
}

//knights attack

inline u64 knightAttack(u64 knights)
{
	return
		noNOEa(knights) | noEaEa(knights) | soEaEa(knights)
		| soSoEa(knights) | noNoWe(knights) | noWeWe(knights)
		| soWeWe(knights) | soSoWe(knights);
}

SELECT_ANY u64 allknightAttacks[Squareend];

inline void initKnightAttack()
{
	u64 board = C64(1);
	allknightAttacks[0] = knightAttack(C64(1));
	for (int I = 1; I < 64; I++)
	{
		board <<= 1;
		allknightAttacks[I] = knightAttack((board));
	}
}

//so what's a fill
//let's say there's a knight on square a1
//it can move to c2 or b3
//if we apply another fill knight on c2 can move to valid knight squares & b3 too
// we keep applying till there's no empty square (that's why it's called fill)

inline u64 knightFill(u64 knights)
{
	return knightAttack(knights) | knights;
}

// knight fork
// it's a knight pattern (winning the queen is most important)
// it's the union of all intersections of all direction attacks
// it uses greater one set :
//      The value of the operation is true if more than one argument is true, false otherwise

inline u64 forkTargetSquare(u64 targets)
{
	u64 east, west, attack, forks;
	east = eastOne(targets);
	west = westOne(targets);
	attack = east << 16;
	forks = (west << 16) & attack;
	attack |= west << 16;
	forks |= (east >> 16) & attack;
	attack |= (east >> 16);
	forks |= (west >> 16) & attack;
	attack |= west >> 16;
	east = eastOne(targets);
	west = westOne(targets);
	forks |= (east << 8) & attack;
	attack |= (east << 8);
	forks |= (west << 8) & attack;
	attack |= (west << 8);
	forks |= (east >> 8) & attack;
	attack |= (east >> 8);
	forks |= (west >> 8) & attack;
	return forks;
}

//knight distance
// we will knight attacks to determine distance
// once a board become becomes a subset of the onther then we reached the distance
// we will count how many times we used fill algorithm

inline int calKnightDistance(u64 a, u64 b)
{
	int count = 0;
	while ((a & b) == 0)
	{
		a = knightAttack(a);
		count++;
	}
	return count;
}

// using index (0-63)

inline int knightDistance(int a, int b)
{
	return calKnightDistance(C64(1) << a, C64(1) << b);
}

// King

// easier than knight :D

inline u64 kingAttacks(u64 king)
{
	//u64 attacks = eastOne(king) | westOne(king);
	//attacks |= king;
	//attacks |= (nortOne(king) | soutOne(king));
	//return attacks ^ king;
	return eastOne(king) | westOne(king) | (nortOne(king) | soutOne(king)) | noEaOne(king) | noWeOne(king) | soWeOne(king) | soEaOne(king);
}

// then we store an array of precalculated attacks for every square

SELECT_ANY u64 allKingAttacks[64];

inline void generateKingAttacks()
{
	u64 sq = 1;

	for (int i = 0; i < 64; i++)
	{
		allKingAttacks[i] = kingAttacks(sq);
		sq <<= 1;
	}
}

// sliding piece

//Ray wise attack

//kogge-stone algorithm
// rook -> north south east west

inline u64 northAttacks(u64 rook, u64 empty)
{
	return nortOne(northOccluded(rook, empty));
}

inline u64 southAttacks(u64 rook, u64 empty)
{
	return soutOne(southOccluded(rook, empty));
}

inline u64 eastAttacks(u64 rook, u64 empty)
{
	return eastOne(eastOccluded(rook, empty)); //&constants::notAFile;
}

inline u64 westAttacks(u64 rook, u64 empty)
{
	return westOne(westOccluded(rook, empty));// &constants::notHFile;
}

inline u64 slidingAttacks(u64 slider, u64 empty, int dir8)
{
	u64 fill = occludedFill(slider, empty, dir8);
	return shiftOne(fill, dir8);
}

inline u64 rookAttackWithoutBlockers(u64 rook, u64 empty)
{
	return northAttacks(rook, empty) | southAttacks(rook, empty) | eastAttacks(rook, empty) | westAttacks(rook, empty);
}

//bishop - > noEa noWe soEa soWe

inline u64 noEaAttacks(u64 bishop, u64 empty)
{
	return noEaOne(noEaOccluded(bishop, empty)) & (BASE::avoidWrap[0]);
}

inline u64 noWeAttacks(u64 bishop, u64 empty)
{
	return noWeOne(noWeOccluded(bishop, empty)) & (BASE::avoidWrap[6]);
}

inline u64 soEaAttacks(u64 bishop, u64 empty)
{
	return soEaOne(soEaOccluded(bishop, empty)) & (BASE::avoidWrap[2]);
}

inline u64 soWeAttacks(u64 bishop, u64 empty)
{
	return soWeOne(soWeOccluded(bishop, empty)) & (BASE::avoidWrap[4]);
}

inline u64 bishopAttackWithoutBlockers(u64 bishop, u64 empty)
{
	return noEaAttacks(bishop, empty) | noWeAttacks(bishop, empty) | soEaAttacks(bishop, empty) | soWeAttacks(bishop, empty);
}

inline u64 queenAttacksWithoutBlockers(u64 queen, u64 empty)
{
	return bishopAttackWithoutBlockers(queen, empty) | rookAttackWithoutBlockers(queen, empty);
}

// pawn attack

inline u64 wPawnEastAttacks(u64 wPawns)
{
	return noEaOne(wPawns) & BASE::avoidWrap[0];
}

inline u64 wPawnWesttAttacks(u64 wPawns)
{
	return noWeOne(wPawns) & BASE::avoidWrap[6];
}

inline u64 bPawnEastAttacks(u64 bPawns)
{
	return soEaOne(bPawns) & BASE::avoidWrap[2];
}

inline u64 bPawnWestAttacks(u64 bPawns)
{
	return soWeOne(bPawns) & BASE::avoidWrap[4];
}

inline u64 wPawnAllAttacks(u64 t)
{
	return
		wPawnEastAttacks(t) | wPawnWesttAttacks(t);
}

inline u64 bPawnAllAttacks(u64 t)
{
	return
		bPawnEastAttacks(t) | bPawnWestAttacks(t);
}

inline u64 allPawnAttacks(u64 t, Color c)
{
	return (c == white) ? wPawnAllAttacks(t) : bPawnAllAttacks(t);
}


// pawn pushes

inline u64 wPawnPushes(u64 pawns)
{
	return nortOne(pawns);
}

inline u64 bPawnPushes(u64 pawns)
{
	return soutOne(pawns);
}

inline u64 wPawnPushesWithoutBlockers(u64 pawns, u64 occupied)
{
	return wPawnPushes(pawns) & (~occupied);
}

inline u64 bPawnPushesWithoutBlockers(u64 pawns, u64 occupied)
{
	return bPawnPushes(pawns) & (~occupied);
}

inline u64 allPawnPushesWithoutBlockers(u64 t, Color c, u64 occupied)
{
	return (c == white) ? wPawnPushesWithoutBlockers(t, occupied) : bPawnPushesWithoutBlockers(t, occupied);
}

// double pushes

inline bool isPushable(Color c, Square sq)
{
	if (c == white)
	{
		if ((sq > 7) && (sq < 16))
			return true;
		return false;
	}
	else
	{
		if ((sq > 47) && (sq < 56))
			return true;
		return false;
	}
}

/*/
u64 wPawnDoublePushes(u64 pawns)
{
return nortOne(nortOne(pawns) & constants::row3);
}
u64 bPawnDoublePushes(u64 pawns)
{
return soutOne(soutOne(pawns) & constants::row6);
}

u64 wPawnDoublePushesWithoutBlockers(u64 pawns, u64 occupied)
{
return wPawnDoublePushes(pawns) & (~occupied);
}

u64 bPawnDoublePushesWithoutBlockers(u64 pawns, u64 occupied)
{
return bPawnDoublePushes(pawns) & (~occupied);
}
*/
inline u64 wPawnDoublePushes(u64 pawns, u64 occupied)
{
	return nortOne((nortOne(pawns) & (~occupied)) & BASE::row3);
}

inline u64 bPawnDoublePushes(u64 pawns, u64 occupied)
{
	return soutOne((soutOne(pawns) & (~occupied)) & BASE::row6);
}

inline u64 wPawnDoublePushesWithoutBlockers(u64 pawns, u64 occupied)
{
	return wPawnDoublePushes(pawns, occupied) & (~occupied);
}

inline u64 bPawnDoublePushesWithoutBlockers(u64 pawns, u64 occupied)
{
	return bPawnDoublePushes(pawns, occupied) & (~occupied);
}

inline u64 allPawnDoublePushesWithoutBlockers(u64 t, Color c, u64 occupied)
{
	return (c == white) ? wPawnDoublePushesWithoutBlockers(t, occupied) : bPawnDoublePushesWithoutBlockers(t, occupied);
}

// pawn promotions 

// in current ply

inline bool checkWhitePromotion(u64 pawns)
{
	return ((pawns & BASE::row8) != 0) ? true : false;
}

inline bool checkBlackPromotion(u64 pawns)
{
	return ((pawns & BASE::row1) != 0) ? true : false;
}

inline bool validForPromotion(Square sq, Color c)
{
	if (c == white)
	{
		if ((sq > 55) && (sq < 64))
			return true;
		return false;
	}
	else
	{
		if ((sq > 0) && (sq < 8))
			return true;
		return false;
	}
}

// in coming ply

inline bool checkWhiteWillPromote(u64 pawns, u64 occupied)
{
	return ((wPawnPushesWithoutBlockers(pawns, occupied) & BASE::row8) != 0) ? true : false;
}

inline bool checkBlackWillPromote(u64 pawns, u64 occupied)
{
	return ((bPawnPushesWithoutBlockers(pawns, occupied) & BASE::row1) != 0) ? true : false;
}

//for ray attacks we'll use precalculated bitboards

//a-file             0x0101010101010101
//h-file             0x8080808080808080
//1st rank           0x00000000000000FF
//8th rank           0xFF00000000000000
//a1-h8 diagonal     0x8040201008040201
//h1-a8 antidiagonal 0x0102040810204080
//light squares      0x55AA55AA55AA55AA
//dark squares       0xAA55AA55AA55AA55


inline u64 rankMask(int sq)
{
	return C64(0xff) << (sq & 56);
}

inline u64 fileMask(int sq)
{
	return C64(0x0101010101010101) << (sq & 7);
}

inline u64 diagonalMask(int sq)
{
	const u64 mask = C64(0x8040201008040201);
	int diag = 8 * (sq & 7) - (sq & 56);
	int nort = -diag & (diag >> 31);
	int sout = diag & (-diag >> 31);
	return (mask >> sout) << nort;
}

inline u64 antiDiagMask(int sq)
{
	const u64 mask = C64(0x0102040810204080);
	int diag = 56 - 8 * (sq & 7) - (sq & 56);
	int nort = -diag & (diag >> 31);
	int sout = diag & (-diag >> 31);
	return (mask >> sout) << nort;
}

//exclude piece square
inline u64 rookMaskEx(int sq)
{
	return rankMask(sq) ^ fileMask(sq);
}

inline u64 bishopMaskEx(int sq)
{
	return diagonalMask(sq) ^ antiDiagMask(sq);
}

inline u64 queenMaskEx(int sq)
{
	return rookMaskEx(sq) ^ bishopMaskEx(sq);
}

inline u64 isAttackedByColor(Square sq, Color c)
{
	u64 z = 10;
	return z;
}

inline u64 dontAttackAllay(u64 attack, u64 boardOfAlly)
{
	return attack &= (~boardOfAlly);
}

inline u64 attackEnemy(u64 attack, u64 boardOfEnemy)
{
	return attack &= boardOfEnemy;
}

inline u64 quietMove(u64 attack, u64 boardOfEnemy)
{
	return attack &= (~boardOfEnemy);
}

inline u64 wPawnLegalAttack(u64 pawns, u64 boardOfEnemy)
{
	return attackEnemy(wPawnAllAttacks(pawns), boardOfEnemy);
}

inline u64 bPawnLegalAttack(u64 pawns, u64 boardOfEnemy)
{
	return attackEnemy(bPawnAllAttacks(pawns), boardOfEnemy);
}

inline u64 allPawnLegalAttacks(u64 pawn, u64 boardOfEnemy, Color c)
{
	return attackEnemy(allPawnAttacks(pawn, c), boardOfEnemy);
}

inline bool isKingAttacked(Bitboard b, Color c) // color of enemy
{
	u64 k = b.getPiece(opposite(c), king);
	if ((attackEnemy(rookAttackWithoutBlockers(b.getPiece(c, rook), b.getEmpty()), b.getPiece(opposite(c), none)) & k) != 0)
		return true;
	else if ((attackEnemy(bishopAttackWithoutBlockers(b.getPiece(c, bishop), b.getEmpty()), b.getPiece(opposite(c), none)) & k) != 0)
		return true;
	else if ((attackEnemy(queenAttacksWithoutBlockers(b.getPiece(c, queen), b.getEmpty()), b.getPiece(opposite(c), none)) & k) != 0)
		return true;
	else if ((attackEnemy(knightAttack(b.getPiece(c, knight)), b.getPiece(opposite(c), none)) & k) != 0)
		return true;
	else if ((allPawnLegalAttacks(b.getPiece(c, pawn), b.getPiece(opposite(c), none), c) & k) != 0)
		return true;
	else if ((attackEnemy(kingAttacks(b.getPiece(c, king)), b.getPiece(opposite(c), none)) & k) != 0)
		return true;
	else if ((attackEnemy(rookAttackWithoutBlockers(b.getRookPromotion(c), b.getEmpty()), b.getPiece(opposite(c), none)) & k) != 0)
		return true;
	else if ((attackEnemy(bishopAttackWithoutBlockers(b.getBishopPromotion(c), b.getEmpty()), b.getPiece(opposite(c), none)) & k) != 0)
		return true;
	else if ((attackEnemy(queenAttacksWithoutBlockers(b.getQueenPromotion(c), b.getEmpty()), b.getPiece(opposite(c), none)) & k) != 0)
		return true;
	else if ((attackEnemy(knightAttack(b.getKnightPromotion(c)), b.getPiece(opposite(c), none)) & k) != 0)
		return true;
	return false;
}

