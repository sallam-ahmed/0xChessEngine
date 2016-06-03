#include "Move.h"
using namespace BASE;
Move::Move()
{
	value = from = to = -1;
	flag = MoveFlag::Quiet;
}


Move::~Move()
{
}

Move::Move(int from, int to)
{
	this->to = to;
	this->from = from;
	this->FromVector = from;
	this->ToVector = to;
}

