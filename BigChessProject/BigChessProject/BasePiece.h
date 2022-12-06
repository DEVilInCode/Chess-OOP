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
	friend bool operator<(const Position& p1, const Position& p2);
	friend Position operator-(const Position& p1, const Position& p2);
}Position;

class BasePiece{
public:
	BasePiece();
	virtual ~BasePiece();

	PieceColor GetColor();
	std::string GetType();
	void SetPosition(Position pos);
	bool isWhite();
	virtual bool validMove(Position moveTo) = 0;

protected:
	std::string type;
	PieceColor color;
	Position pos;
};