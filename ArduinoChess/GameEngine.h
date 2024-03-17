#ifndef GameEngine_h
#define GameEngine_h

#include "Game.h"
#include "EGameEngineStatus.h"

typedef struct 
{
  Game* aGame;
}GameEngine;

GameEngine* NewGameEngine();
void FreeGameEngine(GameEngine* pThis);
void mGameEngineUpdate(GameEngine* pThis);
void mGameEngineRender(GameEngine* pThis);

#endif
