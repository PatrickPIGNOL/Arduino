#ifndef Piece_H
#define Piece_H

/*
♔♕♗♘♖♙
♚♛♝♞♜♟
*/

#include <Arduino.h>
#include "EColors.h"
#include "EPieceTypes.h"

struct _Cell;
typedef struct Piece
{
    char aSymbol;
    EPieceTypes aPieceType;
    EColors aColor;
    bool aMoved;
    bool aLastMoved;
    bool aJailed;
    struct _Cell* aMovedFrom;
}Piece;

#endif