#pragma once
#include <map>
#include "BasePiece.h"

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
	std::map<Position, BasePiece*> board;
	
	void InitializePieces();
	bool IsInBoard(Position pos);
};
