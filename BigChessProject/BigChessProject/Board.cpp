#include <iostream>
#include <Windows.h>
#include "Board.h"
#include "Pieces.h"

Cell::Cell()
{
	this->piece = NULL;
}

Cell::~Cell(){

}

void Cell::SetPiece(BasePiece* piece)
{
	this->piece = piece;
}

BasePiece* Cell::GetPiece()
{
	return this->piece;
}

void Cell::Clear()
{
	this->piece = NULL;
}

Board::Board()
{
	InitializePieces();
}

Board::~Board()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j= 0; j < 8; j++)
		{
			board[i][j].Clear();
		}
	}
}

void Board::Draw()
{
	SetConsoleOutputCP(65001);
	char q[] = "King: \xE2\x99\x94.\n";
	printf(q);

	std::cout << "1 2 3 4 5 6 7 8" << std::endl;
	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++)
		{
			BasePiece* current = board[row][column].GetPiece();
			if (current == NULL)
				std::cout << "  ";
			else
				current->Draw();
		}
		std::cout << (char)('a' + row) << std::endl;
	}
}

void Board::InitializePieces()
{
	//Pawns
	for (int i = 0; i < 8; i++)
	{
		Position blackPawnPos = { i, 6 };
		board[blackPawnPos.y][blackPawnPos.x].SetPiece(new Pawn(Color::black, blackPawnPos));

		Position whitePawnPos = { i, 1 };
		board[whitePawnPos.y][whitePawnPos.x].SetPiece(new Pawn(Color::white, whitePawnPos));
	}

	//Bishops

}

BasePiece* Board::GetPiece(Position pos)
{
	return this->board[pos.x][pos.y].GetPiece();
}