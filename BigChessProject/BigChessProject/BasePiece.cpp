#include "Includes.h"
#include "BasePiece.h"

bool operator<(const Position& p1, const Position& p2)
{
	if (p1.x == p2.x)
		return p1.y < p2.y;
	else
		return p1.x < p2.x;
}

Position operator-(const Position& p1, const Position& p2)
{
	return Position{ p1.x - p2.x, p1.y - p2.y };
}

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

bool BasePiece::isWhite()
{
	return this->color == PieceColor::white;
}

void BasePiece::SetPosition(Position pos)
{
	this->pos = pos;
}