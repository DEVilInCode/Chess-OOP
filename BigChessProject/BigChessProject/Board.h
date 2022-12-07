#pragma once
#include <map>
#include "Pieces.h"

class Board
{
	friend bool undoLastMove();
	friend bool King::notDangerCell(Position pos);
public:
	Board();
	virtual ~Board();

	void Draw();
	bool MovePiece(Position moveFrom, Position moveTo);
	bool GameOver();
	BasePiece* GetPiece(Position piecePos);

protected:

	std::map<Position, BasePiece*> board;
	
	void SetPiece(Position pos, BasePiece* piece);
	void InitializePieces();
};
