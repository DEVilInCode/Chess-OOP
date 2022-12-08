#pragma once
#include <map>
#include "Pieces.h"

class Board
{
	friend bool UndoLastMove();
	friend void Load();
	friend void TryMove();
	friend class King;
public:
	Board();
	virtual ~Board();

	void Draw();
	bool MovePiece(Position moveFrom, Position moveTo);
	BasePiece* GetPiece(Position piecePosition);

protected:
	std::map<Position, BasePiece*> board;

	bool IsCheckmate(bool turn);
	King* GetKing(PieceColor);

	void SetPiece(Position position, BasePiece* piece);
	void InitializePieces();
};
