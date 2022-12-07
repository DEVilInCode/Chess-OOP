#pragma once
#include "BasePiece.h"

class Pawn: public BasePiece {
public:
	Pawn(PieceColor color, Position pos, bool doubleJump = true);
	virtual ~Pawn();

	bool validMove(Position moveTo) override;
	void setDoubleJump(bool);

protected:
	void transformation();

	bool doubleJumpAvailable;
};
