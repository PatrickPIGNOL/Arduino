#ifndef Player_H
#define Player_H

#include "EColors.h"
#include "EPlayerType.h"
#include <Arduino.h>
#include "Piece.h"
typedef struct
{
    EPlayerType aPlayerType;
    EColors aColor;
    Piece** aPieces;
    int aPiecesCount;
    Piece** aJail;
    int aJailCount;
}Player;

#endif