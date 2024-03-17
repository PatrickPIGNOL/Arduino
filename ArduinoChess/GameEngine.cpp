#include "GameEngine.h"

GameEngine* NewGameEngine()
{
  GameEngine* vThis = (GameEngine*)malloc(sizeof(GameEngine));
  vThis->aGame = NewGame();
}

void FreeGameEngine(GameEngine* pThis)
{
  free(pThis->aGame);
  free(pThis);
}

void mGameEngineUpdate(GameEngine* pThis)
{
  mGameUpdate(pThis->aGame);
}

void mGameEngineRender(GameEngine* pThis)
{
  switch(pThis->aStatus)
  {
    case SGameEngineStatus::EGameEngineStatus::Menu : 
    {
      
    }break;
  }
}
