#pragma once
#include <string>

class Board;

enum class Color
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

	Color GetColor();
	void Draw();
	void SetPosition(Position pos);
	virtual bool validMove();

protected:
	std::string type;
	Color color;
	Position pos;
};