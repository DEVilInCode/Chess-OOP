#include <iostream>
#include <Windows.h>
#include "ConsoleColor.h"
#include "Cell.h"
#include "Board.h"
#include "Pawn.h"

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
	ConsoleColor current;

	std::cout << " a  b  c  d  e  f  g  h " << std::endl;
	for (size_t i = 0; i < 8; i++)
	{
		std::cout << " --";
	}
	std::cout << std::endl;
	
	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++)
		{
			if ((column + row) % 2 == 0)
				current = DarkGray;
			else
				current = Black;
			BasePiece* currentPiece = board[row][column].GetPiece();
			if (currentPiece == NULL)
			{
				std::cout << "|";
				SetColor(White, current);
				std::cout << "  ";
			}
			else
			{
				
				std::cout << '|';
				if (currentPiece->GetColor() == PieceColor::black)
					SetColor(Red, current);
				else
					SetColor(White, current); 
				std::cout << currentPiece->GetType();
			}
			SetColor(White, Black);
				
		}

		std::cout << '|' << (1 + row) << std::endl;
		for (size_t i = 0; i < 8; i++)
		{
			std::cout << " --";
		}
		std::cout << std::endl;
	}
}

bool Board::MovePiece(Position moveFrom, Position moveTo)
{
	return false;
}

void Board::InitializePieces()
{
	//Pawns
	for (int i = 0; i < 8; i++)
	{
		Position blackPawnPos = { i, 6 };
		board[blackPawnPos.y][blackPawnPos.x].SetPiece(new Pawn(PieceColor::black, blackPawnPos));

		Position whitePawnPos = { i, 1 };
		board[whitePawnPos.y][whitePawnPos.x].SetPiece(new Pawn(PieceColor::white, whitePawnPos));
	}

	//Bishops

}

BasePiece* Board::GetPiece(Position pos)
{
	return this->board[pos.x][pos.y].GetPiece();
}