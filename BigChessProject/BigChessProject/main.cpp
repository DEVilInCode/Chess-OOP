#include <iostream>
#include <conio.h>
#include <stack>
#include <string>
#include "Board.h"
#include "BasePiece.h"

Board board;
std::stack<std::string> lastMove;

void checkValidPos(int num)
{
	if (num < 1 || num > 8)
		throw std::exception("\nInvalid position");
	
}

void undoLastMove()
{
	std::cout << lastMove.top() << std::endl;
	lastMove.pop();
}

void tryMove()
{
	int fromPosNum, fromPosLetter, toPosNum, toPosLetter;
	try
	{
		checkValidPos(fromPosLetter = _getche() - 'a' + 1);
		checkValidPos(fromPosNum = _getche() - '0');

		std::cout << "->";

		checkValidPos(toPosLetter = _getche() - 'a' + 1);
		checkValidPos(toPosNum = _getche() - '0');
		std::cout << std::endl;

		std::string str = std::to_string(fromPosLetter) + std::to_string(fromPosNum) + board.GetPiece({ fromPosLetter, fromPosNum })->GetType() +
			std::to_string(toPosLetter) + std::to_string(toPosNum) + board.GetPiece({ toPosLetter, toPosNum })->GetType();

		if (board.MovePiece({ fromPosLetter, fromPosNum }, { toPosLetter, toPosNum }))
			lastMove.push(str);

		std::cout << fromPosLetter << fromPosNum << "->" << toPosLetter << toPosNum << std::endl;
		
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

int main()
{

	while (true) {
		system("cls");
		std::cout << "D - draw board\nM - move piece\nS - save game\nL - load game\nE - exit\n";

		switch (_getch())
		{
		case 'd':
		case 'D':
			board.Draw();
			system("pause");
			break;
		case 'm':
		case 'M':
			std::cout << "Enter move(example: a2-a3):" << std::endl;
			board.Draw();
			tryMove();
			
			//std::cout << letter << num << std::endl;
			system("pause");
			break;

		case 'u':
		case 'U':
			undoLastMove();
			break;

		case 's':
		case 'S':
			//Save();
			break;

		case 'l':
		case 'L':
			//Load();
			break;

		case 'e':
		case 'E':
			exit(0);
			break;

		default:
			break;
		}
	}

	return 0;
}