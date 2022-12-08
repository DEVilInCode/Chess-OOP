#pragma once
#include <map>
#include "Pieces.h"

class Board
{
	friend class King;
	friend bool Pawn::validMove(Position);
	friend void Pawn::transformation();
public:
	Board();
	virtual ~Board();

	void Draw();
	void TryMove();
	bool UndoLastMove();
	void Save();
	void Load();
	
	inline BasePiece* GetPiece(Position piecePosition)
	{
		return this->board.at(piecePosition);
	}

protected:
	std::map<Position, BasePiece*> board;

	bool IsCheckmate(bool turn);
	bool MovePiece(Position moveFrom, Position moveTo);
	King* GetKing(PieceColor);

	void InitializePieces();

	inline void SetPiece(Position position, BasePiece* piece)
	{
		board.at(position) = piece;
	}
};
