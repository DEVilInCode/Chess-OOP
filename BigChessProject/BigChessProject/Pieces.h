#pragma once
#include "BasePiece.h"

class Pawn: public BasePiece {
public:
	Pawn(Color color, Position pos);
	~Pawn();

	bool validMove(Position moveTo);

protected:
	bool doubleJumpAvailable;
};
