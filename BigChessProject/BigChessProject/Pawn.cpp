#include <iostream>
#include <stack>
#include "Board.h"
#include "Pawn.h"

extern Board board;
//extern std::stack<std::string> lastMove;

Pawn::Pawn(PieceColor color, Position pos)
{
	this->color = color;
	this->type = "P";//L'♙';
	this->pos = pos;
	this->doubleJumpAvailable = true;
}

Pawn::~Pawn(){}

bool Pawn::validMove(Position moveTo)
{
    
    bool validMove = false;
    int validMove1 = 1;
    int validMove2 = 2;

    // If Black piece
    if (!this->isWhite()) {
        validMove1 = -1;
        validMove2 = -2;
    }

    //***********************  Move Validity Checks  **********************************

    // One square forward to empty square
    if (moveTo.y == pos.y + validMove1 && moveTo.x == pos.x && board.GetPiece(moveTo) == nullptr) {
        validMove = true;

        // When this Validate move function evaluates true, the pawn will be moved. Here we
        // set the double jump avail variable to false, since the pawn can only double jump on opening move
        doubleJumpAvailable = false;
    }
    // Two squares forward to empty square. Only available on pawn's first move
    else if (doubleJumpAvailable == true && moveTo.y == (pos.y + validMove2) && moveTo.x == pos.x
        && board.GetPiece(moveTo) == nullptr && board.GetPiece(Position{pos.x, pos.y + 1}) == nullptr) {

        validMove = true;
    }
    // Diagonal left or right by one square. Must be another piece there to attack.
    else if (moveTo.y == pos.y + validMove1 && (moveTo.x == pos.x - 1 || moveTo.x == pos.x + 1)) {

        // Check if there is a piece in the diagonal position, if so, is it an opposite color
        if (board.GetPiece(moveTo) != nullptr && (board.GetPiece(moveTo)->GetColor() != this->color)) {
            validMove = true;
        }
    }

    // Return status flag from checks
    return validMove;
}
