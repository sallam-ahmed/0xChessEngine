#pragma once
#include "base.hpp"
#include "Vector2.h"
namespace BASE {
	class Move
	{
	public:
		Move();
		~Move();
		Move(int from, int to);
		int value;//for evaluating
		int from, to;
		MoveFlag flag;
		Vector2 FromVector;
		Vector2 ToVector;
	};



}