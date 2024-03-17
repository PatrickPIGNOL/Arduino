#ifndef Player_H
#define Player_H

#include "EColors.h"
#include "EPlayerType.h"
#include "Board.h"
#include <Arduino.h>

typedef struct Piece Piece;

typedef struct Player
{
    SPlayerType::EPlayerType aPlayerType;
    SColors::EColors aColor;
    Piece** aPieces;
    int aPiecesCount;
    int aJailCount;
}Player;

Player* NewPlayer(Board* pBoard, SColors::EColors pColor, SPlayerType::EPlayerType pPlayerType);
void FreePlayer(Player* pThis);


#endif
