#include "Knight.h"
#include "Board.h"

extern Board board;

Knight::Knight(PieceColor color, Position position)
{
	this->color = color;
	this->type = "N";
	this->position = position;
}

Knight::~Knight() {}

bool Knight::validMove(Position moveTo)
{
	Position delta = moveTo - this->position;
	delta.x = abs(delta.x);
	delta.y = abs(delta.y);
	if ((delta.x == 2 && delta.y == 1) || (delta.x == 1 && delta.y == 2))
		if (board.GetPiece(moveTo) == nullptr || board.GetPiece(moveTo)->GetColor() != this->GetColor())
			return true;

	return false;
}