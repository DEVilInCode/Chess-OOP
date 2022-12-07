#include "Includes.h"
#include "Board.h"
#include "Pieces.h"
#include "Functions.h"

extern Board board;
extern std::stack<std::string> lastMove;

const std::string location = "D:\\file.txt";

void save()
{
	std::ofstream file(location);
	std::string info;
	std::stringstream strm;
	for(int i = 0; !lastMove.empty(); i++)
	{
		info = lastMove.top();
		strm << info;

		strm >> info;
		std::cout << info << std::endl;
		system("pause");
		while (strm)
		{
			file << info << " ";
			strm >> info;
		}

		file << std::endl;
		lastMove.pop();
	}
	for (int i = 1; i < 9; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			BasePiece* p = board.GetPiece(Position{ i, j });
			if (p == nullptr)
				file << "Null ";
			else
				file << (p->isWhite() ? "w" : "b") << " " << p->GetType() << " ";
		}
		file << std::endl;
	}
	file.close();
}

void load()
{

}

void checkValidPos(int num)
{
	if (num < 1 || num > 8)
		throw std::exception("Invalid position");

}

bool undoLastMove()
{
	try {
		if (lastMove.empty() == true)
			throw std::exception("No one move was");

		std::string moveFromX, moveFromY, pieceColor1, piece1, moveToX, moveToY, piece2, pieceColor2;
		std::stringstream strm;
		strm << lastMove.top();
		strm >> moveFromX >> moveFromY >> pieceColor1 >> piece1 >> moveToX >> moveToY >> pieceColor2 >> piece2;
		lastMove.pop();

		Position pos[2] = { { std::stoi(moveFromX), std::stoi(moveFromY) },//From position
							{ std::stoi(moveToX), std::stoi(moveToY) } };//To position

		PieceColor pColor[2] = { pieceColor1 == "w" ? PieceColor::white : PieceColor::black,
								 pieceColor2 == "w" ? PieceColor::white : PieceColor::black };
		std::string pStr[2] = { piece1, piece2 };
		BasePiece* p[2];

		for (int i = 0; i < 2; i++) {
			bool dJump = false;
			switch (pStr[i][0])
			{
			case 'P':
				if (pColor[i] == PieceColor::white && pos[i].y == 2 || //Double jump available
					pColor[i] == PieceColor::black && pos[i].y == 6)
					dJump = true;

				p[i] = new Pawn(pColor[i], pos[i], dJump);
				break;
			case 'Q':
				p[i] = new Qeen(pColor[i], pos[i]);
				break;
			case 'B':
				p[i] = new Bishop(pColor[i], pos[i]);
				break;
			case 'N':
				p[i] = new Knight(pColor[i], pos[i]);
				break;
			case 'R':
				p[i] = new Rook(pColor[i], pos[i]);
				break;
			case 'K':
				p[i] = new King(pColor[i], pos[i]);
				break;
			default:
				p[i] = nullptr;
				break;
			}

			board.SetPiece(pos[i], p[i]);
		}
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
		return false;
	}

	return true;
}

bool tryMove()
{
	Position from, to;

	//get from position
	checkValidPos(from.x = _getche() - 'a' + 1);
	checkValidPos(from.y = _getche() - '0');

	if (board.GetPiece(from) == nullptr)
		throw std::exception("Wrong coordinates");

	std::cout << "->";

	//get to position
	checkValidPos(to.x = _getche() - 'a' + 1);
	checkValidPos(to.y = _getche() - '0');
	std::cout << std::endl;


	//save last move
	std::string str;
	str = std::to_string(from.x) + " " + std::to_string(from.y) + " " + (board.GetPiece(from)->GetColor() == PieceColor::white ? "w" : "b")
		+ " " + board.GetPiece(from)->GetType() + " " + std::to_string(to.x) + " " + std::to_string(to.y) + " ";

	if (board.GetPiece(to) != nullptr)
		str += (board.GetPiece(to)->GetColor() == PieceColor::white ? "w" : "b");

	str += " " + board.GetPiece(to)->GetType();

	if (board.MovePiece(from, to)) {
		lastMove.push(str);
		return true;
	}

	return false;
}
