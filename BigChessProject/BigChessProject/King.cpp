#include "King.h"
#include "Board.h"

extern Board board;

King::King(PieceColor color, Position position)
{
	this->color = color;
	this->type = "K";
	this->position = position;
}

King::~King() {}

bool King::inDanger()
{
	return !notDangerCell(this->position);
}

bool King::notDangerCell(Position position)
{
	bool res = true;

	BasePiece* piece, * savePiece;

	savePiece = board.GetPiece(position);
	board.SetPiece(position, nullptr);

	//check other
	for (int i = 1; i < 9; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			piece = board.GetPiece(Position{i, j});
			if (piece != nullptr && piece->GetColor() != this->GetColor())
			{
				if (piece->GetType() != "P" && piece->GetType() != "K" && piece->validMove(position)) {
					board.SetPiece(position, savePiece);
					return false;
				}
			}
		}
	}

	//check potential king
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if ((position.x + i) < 1 || (position.x + i) > 8 || (position.y + j) < 1 || (position.y + j) > 8)
				continue;
			piece = board.GetPiece(Position{ position.x + i, position.y + j });
			if (piece != nullptr && piece->GetType() == "K" && piece->GetColor() != this->GetColor())
			{ 
				board.SetPiece(position, savePiece);
				return false;
			}
		}
	}

	//check pawn attack
	int pMov;

	pMov = this->GetColor() == PieceColor::white ? 1 : -1;
	Position p1 = { position.x + 1, position.y + pMov  },
			 p2 = { position.x - 1, position.y + pMov };
	BasePiece* piece1, * piece2; 

	//std::cout << pos.x + 1 << pos.x - 1 << pos.y + pMov << std::endl;
	piece1 = position.x + 1 < 9 && position.y + pMov > 0 && position.y + pMov < 9 ? board.GetPiece(p1) : nullptr;
	piece2 = position.x - 1 > 0 && position.y + pMov > 0 && position.y + pMov < 9 ? board.GetPiece(p2) : nullptr;

	if ((piece1 != nullptr &&
		piece1->GetType() == "P" &&
		piece1->GetColor() != this->GetColor() ) ||
		(piece2 != nullptr && 
		piece2->GetType() == "P" &&
		piece2->GetColor() != this->GetColor() ))
		res = false;

	board.SetPiece(position, savePiece);
	return res;
}

bool King::validMove(Position moveTo)
{
	Position delta = moveTo - this->position;
	delta.x = abs(delta.x);
	delta.y = abs(delta.y);

	if(delta.y <= 1 && delta.x <= 1)
		if ((board.GetPiece(moveTo) == nullptr || board.GetPiece(moveTo)->GetColor() != this->GetColor())
			&& notDangerCell(moveTo))
		{

			return true;
		}

	return false;
}