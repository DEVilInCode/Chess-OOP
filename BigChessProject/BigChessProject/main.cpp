#include "Includes.h"
#include "Functions.h"
#include "Board.h"
#include "Pieces.h"

Board board;
std::stack<std::string> lastMove;

bool whiteTurn = true;

int main()
{
	std::cout << "D - draw board\
					\nM - move piece\
					\nU - undo last move\
					\nS - save game\
					\nL - load game\
					\nE - exit\n";
	while (true) {
		try {
			rewind(stdin);
			switch (_getch())
			{
			case 'd':
			case 'D':
				board.Draw();
				break;
			case 'm':
			case 'M':
				board.Draw();
				std::cout << "Enter move(example: a2-a3):" << std::endl;
				tryMove();
				break;

			case 'u':
			case 'U':
				if(undoLastMove())
					board.Draw();
				break;

			case 's':
			case 'S':
				save();
				exit(0);
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
				system("cls");
				std::cout << "D - draw board\
					\nM - move piece\
					\nU - undo last move\
					\nS - save game\
					\nL - load game\
					\nE - exit\n";
				break;
			}
		}
		catch (std::exception& ex)
		{
			std::cout << "Exception: " << ex.what() << std::endl;
		}
	}

	return 0;
}