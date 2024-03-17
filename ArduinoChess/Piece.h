#ifndef Piece_H
#define Piece_H

/*
♔♕♗♘♖♙
♚♛♝♞♜♟
*/

#include <Arduino.h>
#include "EColors.h"
#include "EPieceTypes.h"
#include "Cell.h"
#include "Player.h"

typedef struct 
{
    char aSymbol;
    char aLetter;
    SPieceTypes::EPieceTypes aPieceType;
    SColors::EColors aColor;
    bool aMoved;
    bool aJailed;
    Cell* aCell;
    Player* aOwner;
}Piece;

Piece* NewPiece(Cell* pCell);
void FreePiece(Piece* pThis);
void mPrintPiece(Piece* pThis);

#endif
