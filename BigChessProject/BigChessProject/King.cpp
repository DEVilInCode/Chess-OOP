#include "King.h"
#include "Board.h"

extern Board board;

King::King(PieceColor color, Position pos)
{
	this->color = color;
	this->type = "K";
	this->pos = pos;
}

King::~King() {};

bool King::notDangerCell(Position pos)
{
	return false;
}

bool King::validMove(Position moveTo)
{
	Position delta = moveTo - this->pos;
	delta.x = abs(delta.x);
	delta.y = abs(delta.y);

	if(delta.y <= 1 && delta.x <= 1)
		if((board.GetPiece(moveTo) == nullptr || board.GetPiece(moveTo)->GetColor() != this->GetColor())
			&& notDangerCell(moveTo))
			return true;

	return false;
}