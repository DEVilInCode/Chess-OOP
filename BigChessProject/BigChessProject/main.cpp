#include <iostream>
#include <conio.h>
#include "Board.h"
#include "CMatrix.h"
//#include "BasePiece.h"
Board board;

void checkValidPos(char letter, char num)
{
	if (letter < 'a' || letter > 'h' || num < '1' || num > '8')
		throw std::exception("Invalid position");
	
}

void tryMove()
{
	char fromPosNum, fromPosLetter, toPosNum, toPosLetter;
	try
	{
		fromPosLetter = _getche();
		fromPosNum = _getche();
		std::cout << std::endl;

		checkValidPos(fromPosLetter, fromPosNum);

		toPosLetter = _getche();
		toPosNum = _getche();
		std::cout << std::endl;

		checkValidPos(toPosLetter, toPosNum);
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
			return 0;
			break;

		default:
			break;
		}
	}

	return 0;
}