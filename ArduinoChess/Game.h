#ifndef Game_H
#define Game_H
#include <Arduino.h>
#include "EStates.h"
#include "EGameModes.h"
#include "Board.h"

typedef struct
{
    Board* aBoard;
    EStates aState;
    char aIncomingByte;
    EGameModes aGameMode;
    int aDifficulty;
    int aDepht;
}Game;

#endif
