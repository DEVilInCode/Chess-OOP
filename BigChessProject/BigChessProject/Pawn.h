#pragma once
#include "BasePiece.h"

class Pawn: public BasePiece {
	friend class Board;
public:
	Pawn(PieceColor color, Position position, bool doubleJump = true);
	virtual ~Pawn();

	bool validMove(Position moveTo) override;
	void setDoubleJump(bool);

protected:
	void transformation();

	bool doubleJumpAvailable;
};
