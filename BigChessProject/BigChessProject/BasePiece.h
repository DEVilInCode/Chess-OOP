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