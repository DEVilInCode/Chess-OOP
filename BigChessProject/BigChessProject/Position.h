#pragma once
#include <iostream>

typedef struct Position {
	int x, y;

	inline friend bool operator<(const Position& p1, const Position& p2)
	{

		if (p1.x == p2.x)
			return p1.y < p2.y;
		else
			return p1.x < p2.x;

	}

	inline friend Position operator-(const Position& p1, const Position& p2)
	{
		return Position{ p1.x - p2.x, p1.y - p2.y };
	}

	inline friend std::ostream& operator<<(std::ostream& os, const Position& p)
	{
		os << "x: " << p.x << " y: " << p.y;
		return os;
	}

}Position;