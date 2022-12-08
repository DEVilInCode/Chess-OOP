#include "Includes.h"
#include "Functions.h"
#include "ConsoleColor.h"
#include "Board.h"
#include "Pieces.h"

extern bool whiteTurn;
extern std::stack<std::string> lastMove;

Board::Board()
{
	InitializePieces();
}

Board::~Board()
{
	for (int i = 1; i < 9; i++)
	{
		for (int j= 1; j < 9; j++)
		{
			delete board.at(Position{ i,j });
			board.erase(Position{ i, j });
		}
	}
}

void Board::Draw()
{
	ConsoleColor current;

	int	rowS,
		rowE,
		diff;

	if (whiteTurn)
	{
		rowS = 8;
		rowE = 0;
		diff = -1;
	}
	else
	{
		rowS = 1;
		rowE = 9;
		diff = 1;
	}

	std::cout << "    a  b  c  d  e  f  g  h " << std::endl;
	for (int row = rowS; row < 9 && row > 0; row += diff)
	{
		std::cout << " " << row << " ";
		for (int column = 1; column < 9 && column > 0; column++)
		{
			if ((column + row) % 2 == 0)
				current = DarkGray;
			else
				current = Black;
			BasePiece* currentPiece = GetPiece(Position{ column, row });
			if (currentPiece->GetType() == " ")
			{
				SetColor(White, current);
				std::cout << "   ";
			}
			else
			{
				if (currentPiece->GetColor() == PieceColor::black)
					SetColor(LightRed, current);
				else
					SetColor(White, current); 
				std::cout << " " << currentPiece->GetType() << " ";
			}
			SetColor(White, Black);
				
		}
		std::cout << " " << row << " ";
		std::cout << std::endl;
	}
	std::cout << "    a  b  c  d  e  f  g  h \n\n";
}


void Board::TryMove()
{
	Position from, to;

	//get from position
	EnterPosition(from);

	if (GetPiece(from) == nullptr || GetPiece(from)->IsWhite() != whiteTurn)
		throw std::exception("Pick another piece");

	std::cout << "->";

	//get to position
	EnterPosition(to);
	std::cout << std::endl;

	//save move
	lastMove.push(MoveToString(from, to));

	//try move piece
	if (MovePiece(from, to)) {

		//for Pawns
		if (GetPiece(to)->GetType() == "P")
		{
			Pawn* pawn = dynamic_cast<Pawn*>(GetPiece(to));
			pawn->setDoubleJump(false);
			if (to.y == 1 || to.y == 8)
				pawn->transformation();
		}

		//check
		if (GetKing(whiteTurn ? PieceColor::white : PieceColor::black)->inDanger())
		{
			std::cout << "Change your move, king will be in danger!" << std::endl;
			UndoLastMove();
		}

		//check mate
		if (IsCheckmate(whiteTurn))
		{
			Draw();
			std::cout << "Check mate! " << (whiteTurn ? "White win!" : "Black win!") << std::endl;
			exit(0);
		}

		Draw();
		whiteTurn = whiteTurn == false ? true : false;
		return;
	}
	else
	{
		lastMove.pop();
		throw std::exception("Wrong move");
	}

}

bool Board::UndoLastMove()
{
	try {
		if (lastMove.empty() == true)
			throw std::exception("No one move was");

		int moveFromX, moveFromY, moveToX, moveToY;
		std::string pieceColor1, piece1, piece2, pieceColor2;
		std::stringstream strm;
		strm << lastMove.top();
		strm >> moveFromX >> moveFromY >> pieceColor1 >> piece1 >> moveToX >> moveToY >> pieceColor2 >> piece2;
		lastMove.pop();

		Position position[2] = { { moveFromX, moveFromY },//From position
							{ moveToX, moveToY } };//To position

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
					pColor[i] == PieceColor::black && position[i].y == 7)
					dJump = true;

				if (pieceColor2 == "Null" && abs(position[0].x - position[1].x) == 1 && abs(position[0].y - position[1].y) == 1)
				{
					pColor[0] == PieceColor::white ? SetPiece(Position{ position[1].x, position[1].y - 1 }, new Pawn(PieceColor::black, Position{ position[1].x, position[1].y - 1 }, false)):
						SetPiece(Position{ position[1].x, position[1].y + 1 }, new Pawn(PieceColor::white, Position{ position[1].x, position[1].y + 1 }, false));
				}

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

			SetPiece(position[i], p[i]);
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



void Board::Save()
{
	const std::string location = "D:\\file.txt";

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
			BasePiece* p = GetPiece(Position{ i, j });
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

void Board::Load()
{
	const std::string location = "D:\\file.txt";

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
	for (int i = 0; i < stackSize && strm; i++)
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
	else if (pColor1 == "w")
		whiteTurn = false;


	std::string color,
		piece;
	for (int i = 1; i < 9; i++)
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
				SetPiece(current, nullptr);
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

					SetPiece(current, new Pawn(pieceColor, current, dJump));
					break;
				case 'Q':
					SetPiece(current, new Queen(pieceColor, current));
					break;
				case 'B':
					SetPiece(current, new Bishop(pieceColor, current));
					break;
				case 'N':
					SetPiece(current, new Knight(pieceColor, current));
					break;
				case 'R':
					SetPiece(current, new Rook(pieceColor, current));
					break;
				case 'K':
					SetPiece(current, new King(pieceColor, current));
					break;
				default:
					SetPiece(current, nullptr);
					break;
				}
			}
		}

	}

	file.close();
}

bool Board::MovePiece(Position moveFrom, Position moveTo)
{
	if (GetPiece(moveFrom) != nullptr)
	{
		if (GetPiece(moveFrom)->validMove(moveTo))
		{
			SetPiece(moveTo, GetPiece(moveFrom));
			GetPiece(moveTo)->SetPosition(moveTo);
			SetPiece(moveFrom, nullptr);
			return true;
		}
		return false;
	}
	return false;
}

King* Board::GetKing(PieceColor kingColor)
{
	Position currentPosition, kingPosition;
	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 9; j++) {

			currentPosition = Position{ i,j };
			if (GetPiece(currentPosition)->GetType() == "K" && GetPiece(currentPosition)->GetColor() == kingColor)
			{
				kingPosition = currentPosition;
				return dynamic_cast<King*>(GetPiece(kingPosition));
			}
		}
	}
	std::cout << "KING IS NOT DETECTED!!!" << std::endl;
	return nullptr;
}

bool Board::IsCheckmate(bool whiteTurn)
{
	King* king = GetKing(whiteTurn ? PieceColor::black : PieceColor::white);
	Position currentPosition;
	BasePiece* currentPiece;
	bool isCheckmate = true;
	for (int i = 1; i < 9; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			currentPosition = Position{ i,j };
			currentPiece = GetPiece(currentPosition);

			if (currentPiece != nullptr && currentPiece->IsWhite() != whiteTurn)
				for (int x = 1; x < 9; x++)
				{
					for (int y = 1; y < 9; y++)
					{
						BasePiece* savePiece = GetPiece(Position{ x,y });
						if (savePiece != king && currentPiece->validMove(Position{ x,y }))
						{
							SetPiece(currentPosition, nullptr);
							currentPiece->SetPosition(Position{ x,y });
							SetPiece(Position{ x,y }, currentPiece);

							if (!king->inDanger())
								isCheckmate = false;

							SetPiece(currentPosition, currentPiece);
							currentPiece->SetPosition(currentPosition);
							SetPiece(Position{ x,y }, savePiece);

							if (!isCheckmate)
								return isCheckmate;
						}
					}
				}
		}
	}
	return isCheckmate;
}

void Board::InitializePieces()
{
	//Pawns
	for (int i = 1; i < 9; i++)
	{
		Position blackPawnPos = { i, 7 };
		board.insert(std::pair<Position, BasePiece*>(blackPawnPos, new Pawn(PieceColor::black, blackPawnPos)));


		Position whitePawnPos = { i, 2 };
		board.insert(std::pair<Position, BasePiece*>(whitePawnPos, new Pawn(PieceColor::white, whitePawnPos)));

		for (int j = 3; j < 7; j++)
		{
			board.insert(std::pair<Position, BasePiece*>(Position{ i, j }, nullptr));
		}
	}

	//Kings
	board.insert(std::pair<Position, BasePiece*>({ 4, 1 }, new King(PieceColor::white, {4, 1})));
	board.insert(std::pair<Position, BasePiece*>({ 4, 8 }, new King(PieceColor::black, {4, 8})));


	//Qeens
	board.insert(std::pair<Position, BasePiece*>({ 5, 1 }, new Queen(PieceColor::white, {5, 1})));
	board.insert(std::pair<Position, BasePiece*>({ 5, 8 }, new Queen(PieceColor::black, {5, 8})));

	//Bishops
	board.insert(std::pair<Position, BasePiece*>({ 3, 1 }, new Bishop(PieceColor::white, { 3, 1 })));
	board.insert(std::pair<Position, BasePiece*>({ 6, 1 }, new Bishop(PieceColor::white, { 6, 1 })));

	board.insert(std::pair<Position, BasePiece*>({ 3, 8 }, new Bishop(PieceColor::black, { 3, 8 })));
	board.insert(std::pair<Position, BasePiece*>({ 6, 8 }, new Bishop(PieceColor::black, { 6, 8 })));

	//Knights
	board.insert(std::pair<Position, BasePiece*>({ 2, 1 }, new Knight(PieceColor::white, {2, 1})));
	board.insert(std::pair<Position, BasePiece*>({ 7, 1 }, new Knight(PieceColor::white, {7, 1})));

	board.insert(std::pair<Position, BasePiece*>({ 2, 8 }, new Knight(PieceColor::black, {2, 8})));
	board.insert(std::pair<Position, BasePiece*>({ 7, 8 }, new Knight(PieceColor::black, {7, 8})));

	//Rooks
	board.insert(std::pair<Position, BasePiece*>({ 1, 1 }, new Rook(PieceColor::white, { 1,1 })));
	board.insert(std::pair<Position, BasePiece*>({ 8, 1 }, new Rook(PieceColor::white, { 8,1 })));

	board.insert(std::pair<Position, BasePiece*>({ 1, 8 }, new Rook(PieceColor::black, { 1,8 })));
	board.insert(std::pair<Position, BasePiece*>({ 8, 8 }, new Rook(PieceColor::black, { 8,8 })));
}
