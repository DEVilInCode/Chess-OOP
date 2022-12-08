#pragma once
#include "BasePiece.h"
#include "Bishop.h"
#include "Rook.h"

class Queen: public Bishop, public Rook
{
public:
	Queen(PieceColor color, Position position);
	virtual ~Queen();

	bool validMove(Position moveTo) override;
};