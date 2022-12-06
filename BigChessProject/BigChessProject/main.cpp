#include <iostream>
#include <conio.h>
#include <stack>
#include "Board.h"
#include "BasePiece.h"

Board board;

void checkValidPos(int num)
{
	if (num < 1 || num > 8)
		throw std::exception("\nInvalid position");
	
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

		std::cout << board.MovePiece({ fromPosLetter, fromPosNum}, { toPosLetter, toPosNum }) << std::endl;
		std::cout << fromPosLetter << fromPosNum << "->" << toPosLetter << toPosNum << std::endl;
		//std::cout << board.MovePiece({ fromPosNum, fromPosLetter }, { toPosNum, toPosLetter }) << std::endl;

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
			std::cout << "Enter move(example: a1 - a2):" << std::endl;
			tryMove();
			
			//std::cout << letter << num << std::endl;
			system("pause");
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