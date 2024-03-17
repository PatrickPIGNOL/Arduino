#ifndef Game_H
#define Game_H
#include <Arduino.h>
#include "EStates.h"
#include "EGameModes.h"
#include "Board.h"

typedef struct
{
  Board* aBoard;
  SStates::EStates aState;
  char aIncomingByte;
  SGameModes::EGameModes aGameMode;
  int aDifficulty;
  int aDepht;
}Game;

Game* NewGame();
void FreeGame(Game* pThis);
void mGameUpdate(Game* pGame);
void mGameRender(Game* pGame);

#endif
