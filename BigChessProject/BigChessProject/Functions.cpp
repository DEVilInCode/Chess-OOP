#include "Includes.h"
#include "Board.h"
#include "Pieces.h"
#include "Functions.h"

extern Board board;

bool ValidPosition(Position position)
{
	if (position.x < 1 || position.y < 1 || position.x > 8 || position.y > 8)
	{
		std::cout << "\b\b";
		return false;
	}
	return true;
}

void EnterPosition(Position& position)
{
	do {
		rewind(stdin);
		position.x = _getche() - 'a' + 1;
		position.y = _getche() - '0';
	} while (!ValidPosition(position));
}

std::string MoveToString(Position from, Position to)
{
	std::string string;
	string = std::to_string(from.x) + " " + std::to_string(from.y) + " " + (board.GetPiece(from)->GetColor() == PieceColor::white ? "w" : "b")
		+ " " + board.GetPiece(from)->GetType() + " " + std::to_string(to.x) + " " + std::to_string(to.y) + " ";

	if (board.GetPiece(to) != nullptr)
		string += (board.GetPiece(to)->GetColor() == PieceColor::white ? "w" : "b");
	else
		string += "Null";
	string += " " + board.GetPiece(to)->GetType();

	return string;
}



