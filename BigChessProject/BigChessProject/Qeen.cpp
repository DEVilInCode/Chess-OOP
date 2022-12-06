#include "Qeen.h"
#include "Bishop.h"
#include "Rook.h"

Qeen::Qeen(PieceColor color, Position pos):Bishop(color, pos), Rook(color, pos)
{
	this->color = color;
	this->type = "Q";
	this->pos = pos;
}

Qeen::~Qeen() {}

bool Qeen::validMove(Position moveTo)
{
	return Bishop::validMove(moveTo) || Rook::validMove(moveTo);
}