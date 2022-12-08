#include "Rook.h"
#include "Board.h"

extern Board board;

Rook::Rook(PieceColor color, Position position)
{
	this->color = color;
	this->type = "R";
	this->position = position;
}

Rook::~Rook() {}

bool Rook::validMove(Position moveTo)
{
	Position current, delta = moveTo - this->position;
	
	//if moveTo pos change more than one coordinate
	if (delta.x && delta.y)
		return false;

	//check moveTo cell
	if (board.GetPiece(moveTo) != nullptr && board.GetPiece(moveTo)->GetColor() == this->GetColor())
		return false;

	//if in row othe pieces
	int end = abs(delta.x + delta.y);

	current.x = delta.x < 0 ? this->position.x * -1 : this->position.x;
	current.y = delta.y < 0 ? this->position.y * -1 : this->position.y;

	for (int i = 1; i < end; i++)
	{
		abs(current.y) == moveTo.y ? ++current.x : ++current.y;

		if (board.GetPiece({ abs(current.x), abs(current.y) }) != nullptr)
			return false;
	}

	return true;
}