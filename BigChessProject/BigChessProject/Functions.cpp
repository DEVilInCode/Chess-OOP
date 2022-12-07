#include "Includes.h"
#include "Board.h"
#include "Pieces.h"
#include "Functions.h"

extern Board board;
extern std::stack<std::string> lastMove;
extern bool whiteTurn;

const std::string location = "D:\\file.txt";

void save()
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
				file << (p->isWhite() ? "w" : "b") << " " << p->GetType() << " ";
		}
		file << std::endl;
	}

	file.close();
	load();
}

void load()
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
				p[i] = new Queen(pColor[i], pos[i]);
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

	whiteTurn = whiteTurn == false ? true : false;
	return true;
}

void checkValidPos(int num)
{
	if (num < 1 || num > 8) {
		throw std::exception("Invalid position");
	}

}

void tryMove()
{
	Position from, to;

	//get from position
	rewind(stdin);
	checkValidPos(from.x = _getche() - 'a' + 1);
	checkValidPos(from.y = _getche() - '0');

	if (board.GetPiece(from) == nullptr || board.GetPiece(from)->isWhite() != whiteTurn)
		throw std::exception("Pick another piece");

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
	else
		str += "Null";
	str += " " + board.GetPiece(to)->GetType();

	//try move piece
	/*std::cout << (board.GetPiece(from)->validMove(to) ? "true" : "false");
	std::cout << from.x << from.y << to.x << to.y << std::endl;
	system("pause");*/
	if (board.MovePiece(from, to)) {
		lastMove.push(str);
		Position king, cur;
		bool white = whiteTurn ? true : false;

		King* k;

		//check
		for (int i = 1; i < 9; i++)
			for (int j = 1; j < 9; j++) {
				cur = Position{ i,j };
				if (board.GetPiece(cur)->GetType() == "K" && board.GetPiece(cur)->isWhite() == white)
					king = cur;
			}
		k = dynamic_cast<King*>(board.GetPiece(king));
		if (k->inDanger()) {
			
			undoLastMove();
		}

		
		//check mate
		for (int i = 1; i < 9; i++)
			for (int j = 1; j < 9; j++) {
				cur = Position{ i,j };
				if (board.GetPiece(cur)->GetType() == "K" && board.GetPiece(cur)->isWhite() != white)
					king = cur;
			}
		k = dynamic_cast<King*>(board.GetPiece(king));

		bool checkMate = true;
		for (int i = 1; i < 9; i++)
		{
			for (int j = 1; j < 9; j++)
			{
				Position cur = Position{ i,j };
				BasePiece* p = board.GetPiece(cur);
				if(p != nullptr && p->isWhite() != whiteTurn)
					for (int x = 1; x < 9; x++)
					{
						for (int y = 1; y < 9; y++)
						{
							BasePiece* cp = board.GetPiece(Position{ x,y });
							if (cp != k && p->validMove(Position{ x,y }))
							{
								if (p->GetType() == "P") {
									Pawn* pawn = dynamic_cast<Pawn*>(p);
									pawn->setDoubleJump(true);
								}

								//board.SetPiece(cur, nullptr);
								//board.SetPiece(Position{ x,y }, p);
								if (!k->inDanger())
								{
									checkMate = false;
								}
								//board.SetPiece(cur, p);
								//board.SetPiece(Position{ x,y }, cp);
								
							}	
						}
					}
			}
		}
		if (checkMate)
		{
			std::cout << "Check mate! " << (whiteTurn ? "White win!" : "Black win!") << std::endl;
			exit(0);
		}
		whiteTurn = whiteTurn == false ? true : false;
		board.Draw();
		return;

	}
	else
		throw std::exception("Wrong move");

}

