#pragma once
#include <string.h>
#include "Position.h"

class Board;

enum class PieceColor
{
	black,
	white
}; 

class BasePiece{
public:
	BasePiece();
	virtual ~BasePiece();

	PieceColor GetColor();
	std::string GetType();
	void SetPosition(Position position);
	bool IsWhite();

	virtual bool validMove(Position moveTo) = 0;

protected:
	std::string type;
	PieceColor color;
	Position position;
};