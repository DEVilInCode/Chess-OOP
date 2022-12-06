#include "Includes.h"
#include "Board.h"
#include "BasePiece.h"
#include "Qeen.h"

Board board;
std::stack<std::string> lastMove;

void checkValidPos(int num)
{
	if (num < 1 || num > 8)
		throw std::exception("Invalid position");
	
}

void undoLastMove()
{
	if (lastMove.empty() == true)
		throw std::exception("No one move was");

	std::string moveFrom, piece1, moveTo, piece2;
	std::stringstream strm;
	strm << lastMove.top();
	strm >> moveFrom >> piece1 >> moveTo >> piece2;
	std::cout << moveFrom << " " << piece1 << " " << moveTo << " " << piece2 << std::endl;
	lastMove.pop();
}

void tryMove()
{
	int fromPosNum, fromPosLetter, toPosNum, toPosLetter;

	//get from position
	checkValidPos(fromPosLetter = _getche() - 'a' + 1);
	checkValidPos(fromPosNum = _getche() - '0');

	std::cout << "->";

	//get to position
	checkValidPos(toPosLetter = _getche() - 'a' + 1);
	checkValidPos(toPosNum = _getche() - '0');
	std::cout << std::endl;

	//save last move
	std::string str;
	Position from = { fromPosLetter, fromPosNum }, 
			 to = { toPosLetter, toPosNum };

	str = std::to_string(fromPosLetter) + std::to_string(fromPosNum) + " " + (board.GetPiece(from)->GetColor() == PieceColor::white ? "w" : "b") + board.GetPiece(from)->GetType() + " " +
		std::to_string(toPosLetter) + std::to_string(toPosNum) + " ";

	if (board.GetPiece(to) != nullptr)
		str += (board.GetPiece(to)->GetColor() == PieceColor::white ? "w" : "b");

	str += board.GetPiece(to)->GetType();
	
	if (board.MovePiece(from, to))
		lastMove.push(str);

	std::cout << fromPosLetter << fromPosNum << "->" << toPosLetter << toPosNum << std::endl;
}

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
				board.Draw();
				//std::cout << letter << num << std::endl;
				system("pause");
				break;

			case 'u':
			case 'U':
				undoLastMove();
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
		catch (std::exception& ex)
		{
			std::cout << "\nException: " << ex.what() << std::endl;
			system("pause");
		}
	}

	return 0;
}