#pragma once
#include <map>
#include "Pieces.h"

class Board
{
	friend bool undoLastMove();
	friend void load();
	friend void tryMove();
	friend class King;
public:
	Board();
	virtual ~Board();

	void Draw();
	bool MovePiece(Position moveFrom, Position moveTo);
	BasePiece* GetPiece(Position piecePos);

protected:
	std::map<Position, BasePiece*> board;

	void SetPiece(Position pos, BasePiece* piece);
	void InitializePieces();
};
