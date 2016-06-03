#pragma once
//#include "pattern.h"
/*A point in 2D Space.*/
class Vector2 {
public:
	Vector2(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	Vector2()
	{
		this->x = this->y = -1;
	}
	int x, y;
	void operator=(int square) {
	//	this->x = getFile(Square(square));
		//this->y = getRank(Square(square));
	}
};
