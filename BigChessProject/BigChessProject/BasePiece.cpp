#include "BasePiece.h"
#include <iostream>

BasePiece::BasePiece() {
	this->type = " ";
}
BasePiece::~BasePiece() {
	std::cout << "Destroyed" << std::endl;
}

Color BasePiece::GetColor()
{
	return this->color;
}

void BasePiece::Draw()
{
	std::cout << this->type;// << std::endl;	
}

void BasePiece::SetPosition(Position pos)
{
	this->pos = pos;
}

bool BasePiece::validMove()
{
	//virtual
	return false;
}