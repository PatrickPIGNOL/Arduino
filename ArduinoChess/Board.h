#ifndef Board_H
#define Board_H
#include <Arduino.h>
#include "Cell.h"
#include "EPieceTypes.h"

const int cBoardSize = 8;
typedef struct Player;

typedef struct 
{
    Cell*** aCells;
    Player* aPlayer1;
    Player* aPlayer2;
    BoardMove* aBoardMoves;
} Board;

Board* NewBoard(Player* pPlayer1, Player* pPlayer2);
void FreeBoard(Board* pThis);
void mBoardPrint(Board* pThis);


#endif
