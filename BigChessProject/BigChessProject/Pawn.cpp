#include "Includes.h"
#include "Board.h"
#include "Pawn.h"

extern Board board;
extern std::stack<std::string> lastMove;

Pawn::Pawn(PieceColor color, Position pos, bool doubleJump)
{
	this->color = color;
	this->type = "P";//L'♙';
	this->pos = pos;
	this->doubleJumpAvailable = doubleJump;
}

Pawn::~Pawn() {}

void Pawn::transformation()
{

}

bool Pawn::validMove(Position moveTo)
{
    Position delta = moveTo - this->pos;
    bool valid = false;
    int move1 = 1,
        move2 = 2;

    if (!this->isWhite())
    {
        move1 *= -1;
        move2 *= -1;
    }

    //move 1 cell
    if (moveTo.y == this->pos.y + move1 && moveTo.x == pos.x && board.GetPiece(moveTo) == nullptr) {
        this->doubleJumpAvailable = false;
        valid = true;
    }

    //move 2 cells
    else if (this->doubleJumpAvailable == true && moveTo.y == this->pos.y + move2 && moveTo.x == pos.x
        && board.GetPiece(moveTo) == nullptr && board.GetPiece(Position{pos.x, pos.y + move1}) == nullptr) {
        this->doubleJumpAvailable = false;
        valid = true;
    }

    //diagonal attack
    else if (moveTo.y == pos.y + move1 && (moveTo.x == pos.x - 1 || moveTo.x == pos.x + 1)) {

        if (board.GetPiece(moveTo) != nullptr && (board.GetPiece(moveTo)->GetColor() != this->color)) {
            valid = true;
        }
    }

    //en passant

    return valid;
}
