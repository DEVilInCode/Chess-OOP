#include <iostream>
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

    if (moveTo.y == this->pos.y)
    {
        // Simple move forward
        if ((this->isWhite() && moveTo.x == this->pos.x + 1) ||
            (!this->isWhite() && moveTo.x == this->pos.x - 1))
        {
            if (board.GetPiece(moveTo) == nullptr)
            {
                validMove = true;
            }
        }

        // Double move forward
        else if ((this->isWhite() && moveTo.x == this->pos.x + 2) ||
                (!this->isWhite() && moveTo.x == this->pos.x - 2))
        {
            // This is only allowed if the pawn is in its original place
            if (this->isWhite())
            {
                if (board.GetPiece({moveTo.x - 1, moveTo.y}) == nullptr &&
                    board.GetPiece(moveTo) == nullptr &&
                    1 == this->pos.x)
                {
                    validMove = true;
                }
            }
            else // if ( !this->isWhite() )
            {
                if (board.GetPiece({moveTo.x +1,moveTo.y}) == nullptr &&
                    board.GetPiece(moveTo) == nullptr &&
                    6 == this->pos.x)
                {
                    validMove = true;
                }
            }
        }
        else
        {
            // This is invalid
            return false;
        }
    }

    // The "en passant" move
    else if ((this->isWhite() && 4 == this->pos.x && 5 == moveTo.x && 1 == abs(moveTo.y - this->pos.y)) ||
        (!this->isWhite() && 3 == this->pos.x && 2 == moveTo.x && 1 == abs(moveTo.y - this->pos.y)))
    {
        // It is only valid if last move of the opponent was a double move forward by a pawn on a adjacent column
        string last_move = current_game->getLastMove();

        // Parse the line
        Chess::Position LastMoveFrom;
        Chess::Position LastMoveTo;
        current_game->parseMove(last_move, &LastMoveFrom, &LastMoveTo);

        // First of all, was it a pawn?
        char chLstMvPiece = current_game->getPieceAtPosition(LastMoveTo.iRow, LastMoveTo.iColumn);

        if (toupper(chLstMvPiece) != 'P')
        {
            return false;
        }

        // Did the pawn have a double move forward and was it an adjacent column?
        if (2 == abs(LastMoveTo.iRow - LastMoveFrom.iRow) && 1 == abs(LastMoveFrom.iColumn - present.iColumn))
        {
            cout << "En passant move!\n";
            bValid = true;

            S_enPassant->bApplied = true;
            S_enPassant->PawnCaptured.iRow = LastMoveTo.iRow;
            S_enPassant->PawnCaptured.iColumn = LastMoveTo.iColumn;
        }
    }

    // Wants to capture a piece
    else if (1 == abs(moveTo.y - this->pos.y))
    {
        if ((this->isWhite() && moveTo.x == this->pos.x + 1) || (!this->isWhite() && moveTo.x == this->pos.x - 1))
        {
            // Only allowed if there is something to be captured in the square
            if (board.GetPiece(moveTo) != nullptr)
            {
                validMove = true;
                std::cout << "Pawn captured a piece!\n";
            }
        }
    }
    else
    {
        // This is invalid
        return false;
    }

    // If a pawn reaches its eight rank, it must be promoted to another piece
    if ((this->isWhite() && 7 == moveTo.x) ||
        (!this->isWhite() && 0 == moveTo.x))
    {
        std::cout << "Pawn must be promoted!\n";
        //S_promotion->bApplied = true;
    }
}

//    // If Black piece, the movement is downwards on board. Adjust for this
//    if (color == PieceColor::black) {
//        validMove1 = -1;
//        validMove2 = -2;
//    }
//
//    //***********************  Move Validity Checks  **********************************
//
//    // One square forward to empty square
//    if (moveTo.y == pos.y + validMove1 && moveTo.x == pos.x && board.GetPiece(moveTo) == nullptr) {
//        validMove = true;
//
//        // When this Validate move function evaluates true, the pawn will be moved. Here we
//        // set the double jump avail variable to false, since the pawn can only double jump on opening move
//        doubleJumpAvailable = false;
//
//    }
//    // Two squares forward to empty square. Only available on pawn's first move
//    else if (doubleJumpAvailable == true && moveTo.y == (pos.y + validMove2) && moveTo.x == pos.x
//        && board.GetPiece(moveTo) == nullptr) {
//
//        validMove = true;
//    }
//    // Diagonal left or right by one square. Must be another piece there to attack.
//    else if (moveTo.y == pos.y + validMove1 && (moveTo.x == pos.x - 1 || moveTo.x == pos.x + 1)) {
//
//        // Check if there is a piece in the diagonal position, if so, is it an opposite color
//        if (board.GetPiece(moveTo) != nullptr && (board.GetPiece(moveTo)->GetColor() != this->color)) {
//            validMove = true;
//        }
//    }
//
//    // Return status flag from checks
//    return validMove;
		
}	
