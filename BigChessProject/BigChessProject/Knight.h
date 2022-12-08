#pragma once
#include "BasePiece.h"

class Knight :public BasePiece
{
public:
	Knight(PieceColor color, Position position);
	virtual ~Knight();

	bool validMove(Position moveTo) override;
};