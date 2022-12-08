#pragma once
#include "BasePiece.h"

class King :public BasePiece
{
	friend class Board;
public:
	King(PieceColor color, Position position);
	virtual ~King();

	bool inDanger();

	bool validMove(Position moveTo) override;
private:
	bool notDangerCell(Position);
};