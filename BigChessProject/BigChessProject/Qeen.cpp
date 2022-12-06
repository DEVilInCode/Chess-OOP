#include "Qeen.h"


Qeen::Qeen(PieceColor color, Position pos)
{
	//this->color = color;
	//this->type = "Q";
	//this->pos = pos;
}

Qeen::~Qeen() {};

bool Qeen::validMove(Position moveTo)
{
	Bishop::validMove(moveTo);
	return Bishop::validMove(moveTo) || Rook::validMove();

	return false;
}