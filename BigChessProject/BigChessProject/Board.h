#pragma once
#include "BasePiece.h"
#include "Cell.h"

class Board
{
public:
	Board();
	virtual ~Board();

	void Draw();
	bool MovePiece(Position moveFrom, Position moveTo);
	bool GameOver();
	BasePiece* GetPiece(Position piecePos);

protected:
	Cell board[8][8];
	
	void InitializePieces();
	bool IsInBoard(Position pos);
};
