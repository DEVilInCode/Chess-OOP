#include <iostream>
#include "Cell.h"

Cell::Cell()
{
	this->piece = NULL;
}

Cell::~Cell() {
	delete this->piece;
}

void Cell::SetPiece(BasePiece* piece)
{
	this->piece = piece;
}

BasePiece* Cell::GetPiece()
{
	return this->piece;
}

void Cell::Clear()
{
	if (this->piece != nullptr)
		delete this->piece;
	this->piece = nullptr;
}