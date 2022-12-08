#include "Includes.h"
#include "BasePiece.h"

BasePiece::BasePiece() {
	this->type = " ";
}

BasePiece::~BasePiece() {}


PieceColor BasePiece::GetColor()
{
	return this->color;
}

std::string BasePiece::GetType()
{
	if (this != nullptr)
		return this->type;
	else
		return " ";
}

bool BasePiece::IsWhite()
{
	return this->color == PieceColor::white;
}

void BasePiece::SetPosition(Position position)
{
	this->position = position;
}