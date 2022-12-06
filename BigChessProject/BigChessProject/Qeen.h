#pragma once
#include "BasePiece.h"
#include "Bishop.h"
#include "Rook.h"

class Qeen:public BasePiece
{
public:
	Qeen(PieceColor color, Position pos);
	virtual ~Qeen();

	bool validMove(Position moveTo) override;
};