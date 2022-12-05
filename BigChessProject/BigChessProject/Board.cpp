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
			BasePiece* tmp = board.at({ i,j });
			if (tmp != nullptr)
				delete tmp;
			tmp = nullptr;
			board.erase({ i, j });
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
			BasePiece* currentPiece = board.at({ row, column });
			if (currentPiece->GetType() == " ")
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
	return board.at(moveFrom)->validMove(moveTo);
}

void Board::InitializePieces()
{
	//Pawns
	for (int i = 0; i < 8; i++)
	{


		Position blackPawnPos = { i, 6 };
		board.insert(std::pair<Position, BasePiece*>({blackPawnPos.y, blackPawnPos.x }, new Pawn(PieceColor::black, blackPawnPos)));


		Position whitePawnPos = { i, 1 };
		board.insert(std::pair<Position, BasePiece*>({ whitePawnPos.y, whitePawnPos.x }, new Pawn(PieceColor::white, whitePawnPos)));

		for (int j = 0; j < 8; j++)
		{
			board.insert(std::pair<Position, BasePiece*>(Position{ j, i }, nullptr));
		}
	}

	//Bishops

}

bool Board::IsInBoard(Position pos)
{
	return true;
}

BasePiece* Board::GetPiece(Position pos)
{
	return this->board.at(pos);
}