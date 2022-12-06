#include "Rook.h"
#include "Board.h"
#include <iostream>

extern Board board;

Rook::Rook(PieceColor color, Position pos)
{
	this->color = color;
	this->type = "R";
	this->pos = pos;
}

Rook::~Rook(){}

bool Rook::validMove(Position moveTo)
{
	Position current, delta = moveTo - this->pos;
	
	//if moveTo pos change more than one coordinate
	if (delta.x && delta.y)
		return false;

	//check cells other pieces
	int end = abs(delta.x + delta.y);

	current.x = delta.x == 0 ? this->pos.x :
		delta.x < 0 ? this->pos.x * -1 : this->pos.x;

	current.y = delta.y == 0 ? this->pos.y :
		delta.y < 0 ? this->pos.y * -1 : this->pos.y;

	if (delta.x == 0)
	{
		for (int i = 1; i < end; i++)
		{
			//std::cout << current.x << current.y << std::endl;
			if (board.GetPiece({ current.x, abs(++current.y) }) != nullptr)
				return false;
		}
	}
	else
	{
		for (int i = 1; i < end; i++)
		{
			//std::cout << current.x << current.y << std::endl;
			if (board.GetPiece({ abs(++current.x), current.y}) != nullptr)
				return false;
		}
	}
	
	//check moveTo cell
	if (board.GetPiece(moveTo) != nullptr && board.GetPiece(moveTo)->GetColor() == this->GetColor())
		return false;
	

	return true;
}