#include "Knight.h"
#include "Board.h"

extern Board board;

Knight::Knight(PieceColor color, Position pos)
{
	this->color = color;
	this->type = "K";
	this->pos = pos;
}

Knight::~Knight() {}

bool Knight::validMove(Position moveTo)
{
	Position delta = moveTo - this->pos;
	delta.x = abs(delta.x);
	delta.y = abs(delta.y);
	if ((delta.x == 2 && delta.y == 1) || (delta.x == 1 && delta.y == 2))
		if (board.GetPiece(moveTo) == nullptr || board.GetPiece(moveTo)->GetColor() != this->GetColor())
			return true;

	return false;
}