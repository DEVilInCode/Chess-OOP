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
					\n~ - exit\n";
	while (true) {
		try {
			rewind(stdin);
			switch (_getch())
			{
			case 'n':
			case 'N':
				std::cout << "Nobody wins or pat" << std::endl;
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
					\n~ - exit\n";
				break;

			case 'u':
			case 'U':
				if(board.UndoLastMove())
					board.Draw();
				break;

			case 's':
			case 'S':
				board.Save();
				break;

			case 'l':
			case 'L':
				board.Load();
				break;

			case '~':
				exit(0);
				break;

			case 'd':
			case 'D':
			default:
				
				system("cls");
				board.Draw();
				std::cout << "Enter move(example: a2-a3):" << std::endl;
				board.TryMove();

				break;
			}
		}
		catch (std::exception& ex)
		{
			std::cout << "\n" << ex.what() << std::endl;
		}
	}

	return 0;
}