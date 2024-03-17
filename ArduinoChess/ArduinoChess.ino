#include <Arduino.h>
#include "GameEngine.h"

GameEngine* vGameEngine = NULL;

void setup() 
{
    Serial.begin(9600);
    mInit();
}

void loop() 
{
    //Serial.println("Loop:");
    Serial.println("Update:");
    mUpdate();
    Serial.println("Render:");
    mRender();
}

void mInit()
{
   vGameEngine = NewGameEngine();
}

void mUpdate()
{
   mGameEngineUpdate(vGameEngine); 
}

void mRender()
{
  mGameEngineRender(vGameEngine);
}
