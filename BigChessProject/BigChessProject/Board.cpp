#include <iostream>
#include <Windows.h>
#include "ConsoleColor.h"
#include "Board.h"
#include "Pawn.h"

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
	for (size_t i = 1; i < 9; i++)
	{
		std::cout << " --";
	}
	std::cout << std::endl;
	
	for (int row = 1; row < 9; row++)
	{
		for (int column = 1; column < 9; column++)
		{
			if ((column + row) % 2 == 0)
				current = DarkGray;
			else
				current = Black;
			BasePiece* currentPiece = board.at({ column, row });
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

		std::cout << '|' << (row) << std::endl;
		for (size_t i = 1; i < 9; i++)
		{
			std::cout << " --";
		}
		std::cout << std::endl;
	}
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
	std::cout << "moveFrom is null" << std::endl;
	return false;
}

void Board::InitializePieces()
{
	//Pawns
	for (int i = 1; i < 9; i++)
	{


		Position blackPawnPos = { i, 7 };
		board.insert(std::pair<Position, BasePiece*>({ blackPawnPos.x, blackPawnPos.y }, new Pawn(PieceColor::black, blackPawnPos)));


		Position whitePawnPos = { i, 2 };
		board.insert(std::pair<Position, BasePiece*>({ whitePawnPos.x, whitePawnPos.y }, new Pawn(PieceColor::white, whitePawnPos)));

		for (int j = 1; j < 9; j++)
		{
			board.insert(std::pair<Position, BasePiece*>(Position{ i, j }, nullptr));
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