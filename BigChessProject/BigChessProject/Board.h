#pragma once
#include "BasePiece.h"


class Cell
{
public:
	Cell();
	~Cell();
	BasePiece* GetPiece();
	void SetPiece(BasePiece* piece);
	void Clear();
protected:
	BasePiece* piece;
};

class Board
{
public:
	Board();
	~Board();

	void Draw();
	bool MovePiece(Position moveFrom, Position moveTo);
	BasePiece* GetPiece(Position piecePos);

protected:
	Cell board[8][8];
	
	void InitializePieces();
	bool IsInBoard(Position pos);
};
