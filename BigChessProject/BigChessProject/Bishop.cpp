#include <iostream>
#include "Bishop.h"

Bishop::Bishop(PieceColor color, Position pos)
{
	this->color = color;
	if (this->color == PieceColor::black)
		this->type = "bB";//L'♟';
	else
		this->type = "wB";//L'♙';
	this->pos = pos;
}
Bishop::~Bishop(){}

bool Bishop::validMove(Position moveTo)
{
	return false;
}