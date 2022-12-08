#include "Board.h"
#include "Bishop.h"

extern Board board;

Bishop::Bishop(PieceColor color, Position position)
{
	this->color = color;
	this->type = "B";
	this->position = position;
}
Bishop::~Bishop(){}

bool Bishop::validMove(Position moveTo)
{
	Position current, delta = moveTo - this->position;

	//if moveTo pos change coordinates in diff values
	if (abs(delta.x) != abs(delta.y))
		return false;

	//if our piece in moveTo cell
	if (board.GetPiece(moveTo) != nullptr && board.GetPiece(moveTo)->GetColor() == this->GetColor())
		return false;
	
	//If cells in diagonal have pieces
	current.x = delta.x < 0 ? this->position.x * -1 : this->position.x;
	current.y = delta.y < 0 ? this->position.y * -1 : this->position.y;

	for (int i = 1; i < abs(delta.x); i++)
	{
		current.x++;
		current.y++;
		if (board.GetPiece(Position{ abs(current.x), abs(current.y) }) != nullptr)
			return false;
	}

	

	return true;
}