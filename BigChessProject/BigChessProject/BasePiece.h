#pragma once
#include <string>

class Board;

enum class PieceColor
{
	black,
	white
}; 

typedef struct Position {
	int x, y;

	friend bool operator==(const Position& p1, const Position& p2)
	{
		return (p1.x == p2.x) && (p1.y == p2.y);
	}

	friend bool operator<(const Position& p1, const Position& p2)
	{
		if (p1.x == p2.x)
			return p1.y < p2.y;
		else
			return p1.x < p2.x;
	}

}Position;

class BasePiece{
public:
	BasePiece();
	~BasePiece();

	PieceColor GetColor();
	std::string GetType();
	void SetPosition(Position pos);
	virtual bool validMove(Position moveTo) = 0;

protected:
	std::string type;
	PieceColor color;
	Position pos;
};