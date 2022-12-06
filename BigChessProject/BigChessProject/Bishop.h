#pragma once
#include "BasePiece.h"

class Bishop :virtual public BasePiece
{
public:
	Bishop(PieceColor color, Position pos);
	virtual ~Bishop();

	bool validMove(Position moveTo) override;
};