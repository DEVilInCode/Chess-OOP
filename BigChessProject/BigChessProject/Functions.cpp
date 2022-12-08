#include "Includes.h"
#include "Board.h"
#include "Pieces.h"
#include "Functions.h"

extern Board board;
extern std::stack<std::string> lastMove;
extern bool whiteTurn;

const std::string location = "D:\\file.txt";

void Save()
{
	std::ofstream file(location);
	std::string info;
	
	file << lastMove.size() << std::endl;
	while (!lastMove.empty())
	{
		std::stringstream strm;
		strm << lastMove.top();
		lastMove.pop();

		strm >> info;
		while (strm)
		{
			file << info << " ";
			strm >> info;
		}
		file << std::endl;
	}

	for (int i = 1; i < 9; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			BasePiece* p = board.GetPiece(Position{ i, j });
			if (p == nullptr)
				file << "Null ";
			else
				file << (p->IsWhite() ? "w" : "b") << " " << p->GetType() << " ";
		}
		file << std::endl;
	}

	file.close();
	Load();
}

void Load()
{
	std::ifstream file(location);

	if (!file.is_open())
		throw std::exception("Can't open file");

	while (!lastMove.empty())
		lastMove.pop();

	int stackSize;
	std::stringstream strm;
	std::string str, tmp;
	std::getline(file, tmp);
	stackSize = std::stoi(tmp);
	
	for (int i = 0; i < stackSize; i++) {
		std::getline(file, tmp);
		str = tmp + str;
	}

	strm.clear();
	strm << str;

	std::string fromX, fromY, toX, toY, pColor1, piece1, pColor2, piece2;
	for(int i = 0; i < stackSize && strm; i++)
	{
		strm >> fromX >> fromY >> pColor1 >> piece1 >> toX >> toY >> pColor2;
		
		tmp = fromX + " " + fromY + " " + pColor1 + " " + piece1 + " " + toX + " " + toY + " " + pColor2 + " ";
		if (pColor2 != "Null") {
			strm >> piece2;
			lastMove.push(tmp + piece2);
		}
		else
			lastMove.push(tmp);
	}
	if (pColor1 == "b")
		whiteTurn = true;
	else if(pColor1 == "w")
		whiteTurn = false;


	std::string color,
				piece;
	for(int i = 1; i < 9;i++)
	{
		std::stringstream stream;
		std::getline(file, tmp);
		stream << tmp;
	
		for (int j = 1; stream && j < 9; j++)
		{
			bool dJump = false;
			Position current = Position{ i,j };
			stream >> color;
			if (color == "Null")
			{
				board.SetPiece(current, nullptr);
			}
			else {
				PieceColor pieceColor = color == "w" ? PieceColor::white : PieceColor::black;
				stream >> piece;
				switch (piece[0])
				{
				case 'P':
					if (pieceColor == PieceColor::white && j == 2 || //Double jump available
						pieceColor == PieceColor::black && j == 6)
						dJump = true;

					board.SetPiece(current, new Pawn(pieceColor, current, dJump));
					break;
				case 'Q':
					board.SetPiece(current, new Queen(pieceColor, current));
					break;
				case 'B':
					board.SetPiece(current, new Bishop(pieceColor, current));
					break;
				case 'N':
					board.SetPiece(current, new Knight(pieceColor, current));
					break;
				case 'R':
					board.SetPiece(current, new Rook(pieceColor, current));
					break;
				case 'K':
					board.SetPiece(current, new King(pieceColor, current));
					break;
				default:
					board.SetPiece(current, nullptr);
					break;
				}
			}
		}

	}

	file.close();
}

bool UndoLastMove()
{
	try {
		if (lastMove.empty() == true)
			throw std::exception("No one move was");

		std::string moveFromX, moveFromY, pieceColor1, piece1, moveToX, moveToY, piece2, pieceColor2;
		std::stringstream strm;
		strm << lastMove.top();
		strm >> moveFromX >> moveFromY >> pieceColor1 >> piece1 >> moveToX >> moveToY >> pieceColor2 >> piece2;
		lastMove.pop();

		Position position[2] = { { std::stoi(moveFromX), std::stoi(moveFromY) },//From position
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
				if (pColor[i] == PieceColor::white && position[i].y == 2 || //Double jump available
					pColor[i] == PieceColor::black && position[i].y == 6)
					dJump = true;

				p[i] = new Pawn(pColor[i], position[i], dJump);
				break;
			case 'Q':
				p[i] = new Queen(pColor[i], position[i]);
				break;
			case 'B':
				p[i] = new Bishop(pColor[i], position[i]);
				break;
			case 'N':
				p[i] = new Knight(pColor[i], position[i]);
				break;
			case 'R':
				p[i] = new Rook(pColor[i], position[i]);
				break;
			case 'K':
				p[i] = new King(pColor[i], position[i]);
				break;
			default:
				p[i] = nullptr;
				break;
			}

			board.SetPiece(position[i], p[i]);
		}
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
		return false;
	}

	whiteTurn = whiteTurn == false ? true : false;
	return true;
}

bool ValidPosition(Position position)
{
	if (position.x < 1 || position.y < 1 || position.x > 8 || position.y > 8)
	{
		std::cout << "\b\b";
		return false;
	}
	return true;
}

void EnterPosition(Position& position)
{
	do {
		rewind(stdin);
		position.x = _getche() - 'a' + 1;
		position.y = _getche() - '0';
	} while(!ValidPosition(position));
}

std::string MoveToString(Position from, Position to)
{
	std::string string;
	string = std::to_string(from.x) + " " + std::to_string(from.y) + " " + (board.GetPiece(from)->GetColor() == PieceColor::white ? "w" : "b")
		+ " " + board.GetPiece(from)->GetType() + " " + std::to_string(to.x) + " " + std::to_string(to.y) + " ";

	if (board.GetPiece(to) != nullptr)
		string += (board.GetPiece(to)->GetColor() == PieceColor::white ? "w" : "b");
	else
		string += "Null";
	string += " " + board.GetPiece(to)->GetType();

	return string;
}

void TryMove()
{
	Position from, to;

	//get from position
	EnterPosition(from);

	if (board.GetPiece(from) == nullptr || board.GetPiece(from)->IsWhite() != whiteTurn)
		throw std::exception("Pick another piece");

	std::cout << "->";

	//get to position
	EnterPosition(to);

	//save move
	lastMove.push(MoveToString(from, to));

	//try move piece
	if (board.MovePiece(from, to)) {

		//check
		if (board.GetKing(whiteTurn ? PieceColor::white : PieceColor::black)->inDanger())
			UndoLastMove();
		board.Draw();

		//check mate
		if (board.IsCheckmate(whiteTurn))
		{
			std::cout << "Check mate! " << (whiteTurn ? "White win!" : "Black win!") << std::endl;
			exit(0);
		}
		board.Draw();

		whiteTurn = whiteTurn == false ? true : false;
		board.Draw();
		return;
	}
	else
	{
		lastMove.pop();
		throw std::exception("Wrong move");
	}

}

