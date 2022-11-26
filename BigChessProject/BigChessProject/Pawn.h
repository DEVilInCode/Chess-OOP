#pragma once
#include "BasePiece.h"

class Pawn: public BasePiece {
public:
	Pawn(PieceColor color, Position pos);
	virtual ~Pawn();

	bool validMove(Position moveTo) override;

protected:
	bool doubleJumpAvailable;
};
