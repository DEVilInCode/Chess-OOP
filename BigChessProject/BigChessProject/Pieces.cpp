#include <iostream>
#include "Board.h"
#include "BasePiece.h"
#include "Pieces.h"

Pawn::Pawn(Color color, Position pos)
{
	this->color = color;
	if (this->color == Color::black)
		this->type = "bP";//L'♟';
	else
		this->type = "wP";//L'♙';
	this->pos = pos;
	this->doubleJumpAvailable = true;
}
Pawn::~Pawn(){}

bool Pawn::validMove(Position moveTo)
{
	bool validMove = false;
		
	if (moveTo.x == pos.x && moveTo.y == pos.y + 1)//if cell have no any piece
		return true;
	else if (moveTo.x == pos.x && moveTo.y == pos.y + 2 && doubleJumpAvailable == true)
		return true;
	return false;
		
}	
