#include "Includes.h"
#include "ConsoleColor.h"
#include "Board.h"
#include "King.h"
#include "Queen.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"

extern bool whiteTurn;

Board::Board()
{
	InitializePieces();
}

Board::~Board()
{
	for (int i = 1; i < 9; i++)
	{
		for (int j= 1; j < 9; j++)
		{
			delete board.at(Position{ i,j });
			board.erase(Position{ i, j });
		}
	}
}

void Board::Draw()
{
	ConsoleColor current;

	int	rowS,
		rowE,
		diff;

	if (whiteTurn)
	{
		rowS = 8;
		rowE = 0;
		diff = -1;
	}
	else
	{
		rowS = 1;
		rowE = 9;
		diff = 1;
	}

	std::cout << "    a  b  c  d  e  f  g  h " << std::endl;
	for (int row = rowS; row < 9 && row > 0; row += diff)
	{
		std::cout << " " << row << " ";
		for (int column = 1; column < 9 && column > 0; column++)
		{
			if ((column + row) % 2 == 0)
				current = DarkGray;
			else
				current = Black;
			BasePiece* currentPiece = board.at(Position{ column, row });
			if (currentPiece->GetType() == " ")
			{
				SetColor(White, current);
				std::cout << "   ";
			}
			else
			{
				if (currentPiece->GetColor() == PieceColor::black)
					SetColor(LightRed, current);
				else
					SetColor(White, current); 
				std::cout << " " << currentPiece->GetType() << " ";
			}
			SetColor(White, Black);
				
		}
		std::cout << " " << row << " ";
		std::cout << std::endl;
	}
	std::cout << "    a  b  c  d  e  f  g  h \n\n";
}

bool Board::MovePiece(Position moveFrom, Position moveTo)
{
	if (board.at(moveFrom) != nullptr)
	{
		if (board.at(moveFrom)->validMove(moveTo))
		{
			board[moveTo] = board.at(moveFrom);
			board[moveTo]->SetPosition(moveTo);
			board[moveFrom] = nullptr;
			return true;
		}
		return false;
	}
	return false;
}

void Board::SetPiece(Position pos, BasePiece* piece)
{
	board.at(pos) = piece;
}

void Board::InitializePieces()
{
	//Pawns
	for (int i = 1; i < 9; i++)
	{
		Position blackPawnPos = { i, 7 };
		board.insert(std::pair<Position, BasePiece*>(blackPawnPos, new Pawn(PieceColor::black, blackPawnPos)));


		Position whitePawnPos = { i, 2 };
		board.insert(std::pair<Position, BasePiece*>(whitePawnPos, new Pawn(PieceColor::white, whitePawnPos)));

		for (int j = 3; j < 7; j++)
		{
			board.insert(std::pair<Position, BasePiece*>(Position{ i, j }, nullptr));
		}
	}

	//Kings
	board.insert(std::pair<Position, BasePiece*>({ 4, 1 }, new King(PieceColor::white, {4, 1})));
	board.insert(std::pair<Position, BasePiece*>({ 4, 8 }, new King(PieceColor::black, {4, 8})));


	//Qeens
	board.insert(std::pair<Position, BasePiece*>({ 5, 1 }, new Queen(PieceColor::white, {5, 1})));
	board.insert(std::pair<Position, BasePiece*>({ 5, 8 }, new Queen(PieceColor::black, {5, 8})));

	//Bishops
	board.insert(std::pair<Position, BasePiece*>({ 3, 1 }, new Bishop(PieceColor::white, { 3, 1 })));
	board.insert(std::pair<Position, BasePiece*>({ 6, 1 }, new Bishop(PieceColor::white, { 6, 1 })));

	board.insert(std::pair<Position, BasePiece*>({ 3, 8 }, new Bishop(PieceColor::black, { 3, 8 })));
	board.insert(std::pair<Position, BasePiece*>({ 6, 8 }, new Bishop(PieceColor::black, { 6, 8 })));

	//Knights
	board.insert(std::pair<Position, BasePiece*>({ 2, 1 }, new Knight(PieceColor::white, {2, 1})));
	board.insert(std::pair<Position, BasePiece*>({ 7, 1 }, new Knight(PieceColor::white, {7, 1})));

	board.insert(std::pair<Position, BasePiece*>({ 2, 8 }, new Knight(PieceColor::black, {2, 8})));
	board.insert(std::pair<Position, BasePiece*>({ 7, 8 }, new Knight(PieceColor::black, {7, 8})));

	//Rooks
	board.insert(std::pair<Position, BasePiece*>({ 1, 1 }, new Rook(PieceColor::white, { 1,1 })));
	board.insert(std::pair<Position, BasePiece*>({ 8, 1 }, new Rook(PieceColor::white, { 8,1 })));

	board.insert(std::pair<Position, BasePiece*>({ 1, 8 }, new Rook(PieceColor::black, { 1,8 })));
	board.insert(std::pair<Position, BasePiece*>({ 8, 8 }, new Rook(PieceColor::black, { 8,8 })));
}

BasePiece* Board::GetPiece(Position pos)
{
	return this->board.at(pos);
}