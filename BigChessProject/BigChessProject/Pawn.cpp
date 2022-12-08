#include "Includes.h"
#include "Board.h"
#include "Pawn.h"

extern Board board;
extern std::stack<std::string> lastMove;

Pawn::Pawn(PieceColor color, Position position, bool doubleJump)
{
	this->color = color;
	this->type = "P";
	this->position = position;
	this->doubleJumpAvailable = doubleJump;
}

Pawn::~Pawn() {}

void Pawn::transformation()
{
    std::cout << "Pawn in corner of board, choose piece:\nQ - Queen\nB - Bishop\nN - Knight\nR - Rook" << std::endl;
    while (true)
    {
        switch (_getch())
        {
        case 'Q':case 'q':
            board.SetPiece(this->position, new Queen(this->GetColor(), this->position));
            return;
            break;
        case 'B':case 'b':
            board.SetPiece(this->position, new Bishop(this->GetColor(), this->position));
            return;
            break;
        case 'N':case 'n':
            board.SetPiece(this->position, new Knight(this->GetColor(), this->position));
            return;
            break;
        case 'R':case 'r':
            board.SetPiece(this->position, new Rook(this->GetColor(), this->position));
            return;
            break;
        default:
            break;
        }
    }
}

void Pawn::setDoubleJump(bool doubleJump)
{
    this->doubleJumpAvailable = doubleJump;
}

bool Pawn::validMove(Position moveTo)
{
    Position delta = moveTo - this->position;
    int move1 = this->IsWhite() ? 1 : -1,
        move2 = this->IsWhite() ? 2 : -2;

    //move 1 cell
    if (moveTo.y == this->position.y + move1 && moveTo.x == this->position.x && board.GetPiece(moveTo) == nullptr) {
       //this->doubleJumpAvailable = false;
        return true;
    }

    //move 2 cells
    else if (this->doubleJumpAvailable == true && moveTo.y == this->position.y + move2 && moveTo.x == this->position.x
        && board.GetPiece(moveTo) == nullptr && board.GetPiece(Position{position.x, position.y + move1}) == nullptr)
    {
        //this->doubleJumpAvailable = false;
        return true;
    }

    //diagonal attack
    else if (moveTo.y == this->position.y + move1 && (moveTo.x == this->position.x - 1 || moveTo.x == this->position.x + 1)) {

        if (board.GetPiece(moveTo) != nullptr && board.GetPiece(moveTo)->GetColor() != this->GetColor()) {
            return true;
        }
    }

    //en passant
    if (lastMove.size() >= 4)
    {
        Position from, to;
        std::string col1, col2, p1, save;
        std::stringstream strm;
        save = lastMove.top();
        lastMove.pop();
        strm << lastMove.top();
        lastMove.push(save);
        strm >> from.x >> from.y >> col1 >> p1 >> to.x >> to.y;

        PieceColor pieceCol1 = (col1 == "w" ? PieceColor::white : PieceColor::black);
        if (p1 == "P" && from.x - to.x == 0 && abs(from.y - to.y) == 2)
        {
            if ((this->position.x == to.x + 1 || this->position.x == to.x - 1) &&
                (moveTo.x == this->position.x + 1 || moveTo.x == this->position.x - 1) &&
                (moveTo.y == this->position.y + move1))
            {
                board.SetPiece(to, nullptr);
                return true;
            }
        }
    }

    return false;
}
