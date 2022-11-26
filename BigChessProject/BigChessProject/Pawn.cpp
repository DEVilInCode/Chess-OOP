#include <iostream>
#include "Cell.h"
#include "Board.h"
#include "BasePiece.h"
#include "Pawn.h"

extern Board board;

Pawn::Pawn(PieceColor color, Position pos)
{
	this->color = color;
	if (this->color == PieceColor::black)
		this->type = "bP";//L'♟';
	else
		this->type = "wP";//L'♙';
	this->pos = pos;
	this->doubleJumpAvailable = true;
}
Pawn::~Pawn(){}

bool Pawn::validMove(Position moveTo)
{
    // Iniit variables
    bool validMove = false;
    int validMove1 = 1;
    int validMove2 = 2;

    // If Black piece, the movement is downwards on board. Adjust for this
    if (color == PieceColor::black) {
        validMove1 = -1;
        validMove2 = -2;
    }

    //***********************  Move Validity Checks  **********************************

    // One square forward to empty square
    if (moveTo.y == pos.y + validMove1 && moveTo.x == pos.x && board.GetPiece(moveTo) == NULL) {
        validMove = true;

        // When this Validate move function evaluates true, the pawn will be moved. Here we
        // set the double jump avail variable to false, since the pawn can only double jump on opening move
        doubleJumpAvailable = false;

    }
    // Two squares forward to empty square. Only available on pawn's first move
    else if (doubleJumpAvailable == true && moveTo.y == (pos.y + validMove2) && moveTo.x == pos.x
        && board.GetPiece(moveTo) == NULL) {

        validMove = true;
    }
    // Diagonal left or right by one square. Must be another piece there to attack.
    else if (moveTo.y == pos.y + validMove1 && (moveTo.x == pos.x - 1 || moveTo.x == pos.x + 1)) {

        // Check if there is a piece in the diagonal position, if so, is it an opposite color
        if (board.GetPiece(moveTo) != NULL && (board.GetPiece(moveTo)->GetColor() != this->color)) {
            validMove = true;
        }
    }

    // Return status flag from checks
    return validMove;
		
}	
