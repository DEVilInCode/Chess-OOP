#pragma once
#include "BasePiece.h"

class Cell
{
public:
	Cell();
	~Cell();
	BasePiece* GetPiece();
	void SetPiece(BasePiece* piece);
	void Clear();
protected:
	BasePiece* piece;
};