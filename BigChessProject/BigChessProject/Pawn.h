#pragma once
#include "BasePiece.h"

class Pawn: public BasePiece {
public:
	Pawn(PieceColor color, Position position);
	virtual ~Pawn();

	bool validMove(Position moveTo) override;

	void transformation();
};
