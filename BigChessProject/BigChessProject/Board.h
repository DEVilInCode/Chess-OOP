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
	//Cell board[8][8];
	
	void InitializePieces();
	bool IsInBoard(Position pos);
};
