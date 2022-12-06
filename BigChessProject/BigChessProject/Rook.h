#pragma once
#include "BasePiece.h"

class Rook :public BasePiece
{
public:
	Rook(PieceColor color, Position pos);
	virtual ~Rook();

	bool validMove(Position moveTo) override;
};