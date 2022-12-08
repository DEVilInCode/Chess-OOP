#pragma once
#include "BasePiece.h"

class Bishop :virtual public BasePiece
{
public:
	Bishop(PieceColor color, Position position);
	virtual ~Bishop();

	bool validMove(Position moveTo) override;
};