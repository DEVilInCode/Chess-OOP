#pragma once
#include "BasePiece.h"

class Rook :virtual public BasePiece
{
public:
	Rook(PieceColor color, Position position);
	virtual ~Rook();

	bool validMove(Position moveTo) override;
};