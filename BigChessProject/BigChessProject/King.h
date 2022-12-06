#pragma once
#include "BasePiece.h"

class King :public BasePiece
{
public:
	King(PieceColor color, Position pos);
	virtual ~King();

	bool validMove(Position moveTo) override;
private:
	bool notDangerCell(Position);
};