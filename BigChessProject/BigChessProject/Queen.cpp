#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"

Queen::Queen(PieceColor color, Position pos):Bishop(color, pos), Rook(color, pos)
{
	this->color = color;
	this->type = "Q";
	this->pos = pos;
}

Queen::~Queen() {}

bool Queen::validMove(Position moveTo)
{
	return Bishop::validMove(moveTo) || Rook::validMove(moveTo);
}