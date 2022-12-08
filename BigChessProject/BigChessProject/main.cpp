#include "Includes.h"
#include "Functions.h"
#include "Board.h"
#include "Pieces.h"

Board board;
std::stack<std::string> lastMove;
bool whiteTurn = true;

int main()
{
	std::cout << "M - menu\
					\nU - undo last move\
					\nN - nobody wins(for perpetual check)\
					\nS - save game\
					\nL - load game\
					\nE - exit\n";
	while (true) {
		try {
			rewind(stdin);
			switch (_getch())
			{
			case 'n':
			case 'N':
				std::cout << "Nobody wins" << std::endl;
				exit(0);
				break;

			case 'm':
			case 'M':
				system("cls");
				std::cout << "M - menu\
					\nU - undo last move\
					\nN - nobody wins(for perpetual check)\
					\nS - save game\
					\nL - load game\
					\nE - exit\n";
				break;

			case 'u':
			case 'U':
				if(UndoLastMove())
					board.Draw();
				break;

			case 's':
			case 'S':
				Save();
				break;

			case 'l':
			case 'L':
				Load();
				break;

			case 'e':
			case 'E':
				exit(0);
				break;

			case 'd':
			case 'D':
			default:
				do {
					system("cls");
					board.Draw();
					std::cout << "Enter move(example: a2-a3):" << std::endl;
					TryMove();
				} while (true);

				break;
			}
		}
		catch (std::exception& ex)
		{
			std::cout << "\b\b\b\b\b\b" << ex.what() << std::endl;
		}
	}

	return 0;
}