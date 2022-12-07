#include "Includes.h"
#include "Board.h"
#include "Pawn.h"

extern Board board;
extern std::stack<std::string> lastMove;

Pawn::Pawn(PieceColor color, Position pos, bool doubleJump)
{
	this->color = color;
	this->type = "P";
	this->pos = pos;
	this->doubleJumpAvailable = doubleJump;
}

Pawn::~Pawn() {}

void Pawn::transformation()
{

}

void Pawn::setDoubleJump(bool doubleJump)
{
    this->doubleJumpAvailable = doubleJump;
}

bool Pawn::validMove(Position moveTo)
{
    Position delta = moveTo - this->pos;
    bool valid = false;
    int move1 = this->isWhite() ? 1 : -1,
        move2 = this->isWhite() ? 2 : -2;

    //move 1 cell
    if (moveTo.y == this->pos.y + move1 && moveTo.x == this->pos.x && board.GetPiece(moveTo) == nullptr) {
        this->doubleJumpAvailable = false;
        valid = true;
    }

    //move 2 cells
    else if (this->doubleJumpAvailable == true && moveTo.y == this->pos.y + move2 && moveTo.x == this->pos.x
        && board.GetPiece(moveTo) == nullptr && board.GetPiece(Position{pos.x, pos.y + move1}) == nullptr)
    {
        this->doubleJumpAvailable = false;
        valid = true;
    }

    //diagonal attack
    else if (moveTo.y == this->pos.y + move1 && (moveTo.x == this->pos.x - 1 || moveTo.x == this->pos.x + 1)) {

        if (board.GetPiece(moveTo) != nullptr && board.GetPiece(moveTo)->GetColor() != this->GetColor()) {
            valid = true;
        }
    }

    //en passant

    return valid;
}
