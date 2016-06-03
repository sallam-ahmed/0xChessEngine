#pragma once
#include "bitboard.h"
#include <bitset>
#include <stdint.h>  //because not sure that unsigned long will be 32 bit
unsigned __int64 _byteswap_uint64(unsigned __int64 value); // flipping [ _bswap has been replaced with this long one :v ]
using namespace	BASE;

inline u64 singleBitSet(Square s)
{
	return C64(1) << s;
}

inline u64 set(u64 t, Square s)
{
	u64 sbs = singleBitSet(s);
	t |= sbs;
	return t;
}

inline u64 toggle(u64 t, Square s)
{

	u64 sbs = singleBitSet(s);
	t ^= sbs;
	return t;
}

inline u64 reset(u64 t, Square s)
{
	u64 sbs = singleBitSet(s);
	t |= sbs;
	t ^= sbs;
	return t;
}

inline Piece whatPiece(Bitboard b, int sq, Color c)
{
	u64 boardOfPiece = singleBitSet(Square(sq));
	for (Piece p = pawn; p != Pieceend; p++)
		if ((boardOfPiece & b.getPiece(c, p)) != 0)
			return p;

	if ((boardOfPiece & b.getQueenPromotion(c)) != 0)
		return queen;
	else if ((boardOfPiece & b.getKnightPromotion(c)) != 0)
		return knight;
	else if ((boardOfPiece & b.getRookPromotion(c)) != 0)
		return rook;
	else if ((boardOfPiece & b.getBishopPromotion(c)) != 0)
		return bishop;
	return none;
}

inline bool isItPromotion(Bitboard b, int sq, Piece p, Color c)
{
	u64 boardOfPiece = singleBitSet(Square(sq));
	switch (p)
	{
	case knight:
		if ((boardOfPiece & b.getKnightPromotion(c)) != 0)
			return true;
		return false;
		break;
	case bishop:
		if ((boardOfPiece & b.getBishopPromotion(c)) != 0)
			return true;
		return false;
		break;
	case rook:
		if ((boardOfPiece & b.getRookPromotion(c)) != 0)
			return true;
		return false;
		break;
	case queen:
		if ((boardOfPiece & b.getQueenPromotion(c)) != 0)
			return true;
		return false;
		break;
	default:
		return false;
		break;
	}
}

inline u64 upperSquares(Square s)
{
	return C64(~1) << s;
}

inline u64 lowerSquares(Square s)
{
	return (C64(1) << s) - 1;
}

inline int popCounting(u64 t)
{
	int count = 0;
	while (t)
	{
		count++;
		t &= t - 1;
	}
	return count;
}


//serialization


/*
* for rotating:
northwest    north   northeast
noWe         nort         noEa
+7    +8    +9
\  |  /
west    -1 <-  0 -> +1    east
/  |  \
-9    -8    -7
soWe         sout         soEa
southwest    south   southeast

+ : >>
- : <<
_rotl64:
https://msdn.microsoft.com/en-us/library/5cc576c4.aspx
!!!!!!  **** not sure _rotl64 would work with unity
_rotl64 will be implemented but commented
& another function will be used
*/

//shifting
inline u64 soutOne(u64 t) { return  t >> 8; }

inline u64 nortOne(u64 t) { return  t << 8; }

// post shift
//Note: shifting left in computer means shifting right in board

inline u64 eastOne(u64 t)
{
	return (t << 1) & BASE::notAFile;
}

inline u64 noEaOne(u64 t)
{
	return (t << 9) & BASE::notAFile;
}

inline u64 soEaOne(u64 t)
{
	return (t >> 7) & BASE::notAFile;
}

inline u64 westOne(u64 t)
{
	return (t >> 1) & BASE::notHFile;
}

inline u64 soWeOne(u64 t)
{
	return (t >> 9) & BASE::notHFile;
}

inline u64 noWeOne(u64 t)
{
	return (t << 7) & BASE::notHFile;
}
//Rotation
// source : http://www.codeproject.com/Tips/423258/Faster-Bit-Rotation
inline u64 rotateLeft(u64 t, int x)
{
	return ((t >> (~x)) >> 1) | (t << x);
}

inline u64 rotateRight(u64 t, int x)
{
	return ((t << (~x)) << 1) | (t >> x);
}

//general shifting

inline u64 shiftOne(u64 t, int dir8)
{
	int r = BASE::shift[dir8]; // {+-1,7,8,9}
	return rotateLeft(t, r) & BASE::avoidWrap[dir8];
}

//    u64 rotateLeft(u64 t, int x) {return _rotl64(t, x);}
//    u64 rotateRight(u64 t, int x) {return _rotr64(t, x);}


inline u64 flipVertical(u64 t)
{
	return _byteswap_uint64(t);
}


//u64 flipVertical(u64 t) {
//    return  ( (t << 56)                           ) |
//            ( (t << 40) & C64(0x00ff000000000000) ) |
//            ( (t << 24) & C64(0x0000ff0000000000) ) |
//            ( (t <<  8) & C64(0x000000ff00000000) ) |
//            ( (t >>  8) & C64(0x00000000ff000000) ) |
//            ( (t >> 24) & C64(0x0000000000ff0000) ) |
//            ( (t >> 40) & C64(0x000000000000ff00) ) |
//            ( (t >> 56) );
//}

// horizontal mirroring

inline u64 mirrorHorizontal(u64 t) {
	t ^= BASE::k1 & (t ^ rotateLeft(t, 8));
	t ^= BASE::k2 & (t ^ rotateLeft(t, 4));
	t ^= BASE::k3 & (t ^ rotateLeft(t, 2));
	return rotateRight(t, 7);
}

//flip or mirror
inline void DisplayBinary(u64 n)
{
	std::cout << "Displaying binary data: " << std::endl;
	while (n)
	{
		std::cout << n % 2 << " ";
		n %= 2;
	}
	std::cout << "Done" << std::endl;
}

inline u64 GetValidAttack(u64 b)
{
	return b;
}

inline u64 flipOrMirror(u64 t, bool flip, bool mirror)
{
	for (uint32_t i = 3 * (1 - mirror); i < 3 * (1 + flip); i++)
	{
		int s = 1 << i;
		u64 f = C64(1) << s;
		u64 m = universe / (f + 1);
		t = ((t >> s) & m) + f*(t & m);
		/*
		* those are just formulas to get the delta swap constants
		*        delta swap:
		*            To swap any none overlapping pairs we can shift
		*            by the difference (j-i, with j>i) and supply an
		*            explicit mask with a '1' on the least significant
		*            position for each pair supposed to be swapped.
		*
		*/
	}
	return t;
}

//flip over diagonal

inline u64 flipDiagA1H8(u64 t) {
	u64 x;
	x = BASE::k6 & (t ^ (t << 28));
	t ^= x ^ (x >> 28);
	x = BASE::k5 & (t ^ (t << 14));
	t ^= x ^ (x >> 14);
	x = BASE::k4 & (t ^ (t << 7));
	t ^= x ^ (x >> 7);
	return t;
}

//flip anti diagonal

inline u64 flipDiagA8H1(u64 t) {
	u64 x;
	x = t ^ (t << 36);
	t ^= BASE::k9 & (x ^ (t >> 36));
	x = BASE::k8 & (t ^ (t << 18));
	t ^= x ^ (x >> 18);
	x = BASE::k7 & (t ^ (t << 9));
	t ^= x ^ (x >> 9);
	return t;
}

//Rotating
/*
* Need:
*      rotate by 180 :
*              fliping vertically then mirroring
*      rotate by 90 (counter & clockwise) :
*              flipping vertically then flip over anti diagonal (clockwise) or diagonal (counter)
*      rotate by 45 (counter & clockwise) :
*              gather all flipping & mirroring functions ...they r useless here... shit
*              another masking
*/

inline u64 rotate180(u64 t)
{
	return mirrorHorizontal(flipVertical(t));
}

inline u64 rotate90clockwise(u64 t)
{
	return flipVertical(flipDiagA1H8(t));
}

inline u64 rotate90Counter(u64 t)
{
	return flipVertical(flipDiagA8H1(t));
}

inline u64 rotate45Clockwise(u64 t)
{
	t ^= BASE::k10 & (t ^ rotateRight(t, 8));
	t ^= BASE::k11 & (t ^ rotateRight(t, 16));
	t ^= BASE::k12 & (t ^ rotateRight(t, 32));
	return t;
}

inline u64 rotate45Counter(u64 t)
{
	t ^= BASE::k1 & (t ^ rotateRight(t, 8));
	t ^= BASE::k2 & (t ^ rotateRight(t, 16));
	t ^= BASE::k3 & (t ^ rotateRight(t, 32));
	return t;
}


//bitscan forward
// Using de Bruijn Sequences

// ! DON'T USE THIS FUNCTION WITH EMPTY BITBOARD
inline Square firstBit(u64 t)
{
	u64 deb = C64(0x03f79d71b4cb0a89);
	return Square(BASE::index64[((t & (universe - t + 1)) * deb) >> 58]);
}

#ifdef USE_X86INTRINSICS
#include <intrin.h>
#pragma intrinsic(_BitScanForward64)
#pragma intrinsic(_BitScanReverse64)

int bitScanForward(u64 x) {
	unsigned long index;
	_BitScanForward64(&index, x);
	return (int)index;
}

int bitScanReverse(u64 x) {
	unsigned long index;
	_BitScanReverse64(&index, x);
	return (int)index;
}
#endif
