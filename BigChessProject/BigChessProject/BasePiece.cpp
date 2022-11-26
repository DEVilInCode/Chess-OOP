#include "BasePiece.h"
#include <iostream>

BasePiece::BasePiece() {
	this->type = " ";
}
BasePiece::~BasePiece() {
	//std::cout << "Destroyed" << std::endl;
}

PieceColor BasePiece::GetColor()
{
	return this->color;
}

std::string BasePiece::GetType()
{
	return this->type;// << std::endl;	
}

void BasePiece::SetPosition(Position pos)
{
	this->pos = pos;
}