#ifndef Board_H
#define Board_H
#include <Arduino.h>
#include "Cell.h"
#include "Player.h"
#include "EPieceTypes.h"

typedef struct 
{
    Cell*** aCells;
    Player* aPlayer1;
    Player* aPlayer2;
}Board;

#endif