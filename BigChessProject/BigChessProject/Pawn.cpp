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

}

void Pawn::setDoubleJump(bool doubleJump)
{
    this->doubleJumpAvailable = doubleJump;
}

bool Pawn::validMove(Position moveTo)
{
    Position delta = moveTo - this->position;
    bool valid = false;
    int move1 = this->IsWhite() ? 1 : -1,
        move2 = this->IsWhite() ? 2 : -2;

    //move 1 cell
    if (moveTo.y == this->position.y + move1 && moveTo.x == this->position.x && board.GetPiece(moveTo) == nullptr) {
        this->doubleJumpAvailable = false;
        valid = true;
    }

    //move 2 cells
    else if (this->doubleJumpAvailable == true && moveTo.y == this->position.y + move2 && moveTo.x == this->position.x
        && board.GetPiece(moveTo) == nullptr && board.GetPiece(Position{position.x, position.y + move1}) == nullptr)
    {
        this->doubleJumpAvailable = false;
        valid = true;
    }

    //diagonal attack
    else if (moveTo.y == this->position.y + move1 && (moveTo.x == this->position.x - 1 || moveTo.x == this->position.x + 1)) {

        if (board.GetPiece(moveTo) != nullptr && board.GetPiece(moveTo)->GetColor() != this->GetColor()) {
            valid = true;
        }
    }

    //en passant

    return valid;
}
