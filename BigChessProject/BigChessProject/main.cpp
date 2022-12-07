#include "Includes.h"
#include "Functions.h"
#include "Board.h"
#include "Pieces.h"

Board board;
std::stack<std::string> lastMove;

int main()
{
	while (true) {
		system("cls");
		std::cout << "D - draw board\
					\nM - move piece\
					\nU - undo last move\
					\nS - save game\
					\nL - load game\
					\nE - exit\n";
		try {
			rewind(stdin);
			switch (_getch())
			{
			case 'd':
			case 'D':
				board.Draw();
				system("pause");
				break;
			case 'm':
			case 'M':
				board.Draw();
				std::cout << "Enter move(example: a2-a3):" << std::endl;
				if(tryMove())
					board.Draw();
				system("pause");
				break;

			case 'u':
			case 'U':
				if(undoLastMove())
					board.Draw();
				system("pause");
				break;

			case 's':
			case 'S':
				save();
				break;

			case 'l':
			case 'L':
				load();
				break;

			case 'e':
			case 'E':
				exit(0);
				break;

			default:
				break;
			}
		}
		catch (std::exception& ex)
		{
			std::cout << "\nException: " << ex.what() << std::endl;
			system("pause");
		}
	}

	return 0;
}