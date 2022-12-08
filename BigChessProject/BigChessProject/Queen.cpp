#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"

Queen::Queen(PieceColor color, Position position):Bishop(color, position), Rook(color, position)
{
	this->color = color;
	this->type = "Q";
	this->position = position;
}

Queen::~Queen() {}

bool Queen::validMove(Position moveTo)
{
	return Bishop::validMove(moveTo) || Rook::validMove(moveTo);
}