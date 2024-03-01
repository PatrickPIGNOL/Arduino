#include "RelaysBoard.h"

RelaysBoard::RelaysBoard(unsigned int pFirstPin)
{
  mInit(pFirstPin, 16, EState::OFF);
}

RelaysBoard::RelaysBoard(unsigned int pFirstPin, unsigned int pRelaysCount)
{
  mInit(pFirstPin, pRelaysCount, EState::OFF);
}

RelaysBoard::RelaysBoard(unsigned int pFirstPin, unsigned int pRelaysCount, EState pStartState)
{
  mInit(pFirstPin, pRelaysCount, pStartState);
}

void RelaysBoard::mInit(unsigned int pFirstPin, unsigned int pRelaysCount, EState pStartState)
{
  aFirstPin = pFirstPin;
  aRelaysCount = pRelaysCount;
  aStartState = pStartState;
  mReset();
}

void RelaysBoard::mSet(unsigned int pIndex, EState pState)
{
  if(pIndex < aRelaysCount)
  {
    digitalWrite(aFirstPin+pIndex, pState);
  }
  else
  {
    Serial.println("Set Error: pIndex out of bounds. pIndex >= RelaysCount");
  }
}

void RelaysBoard::mReset()
{
  for(unsigned int vIndex = 0; vIndex < aRelaysCount; vIndex++)
  {
    digitalWrite(aFirstPin + vIndex, aStartState);
  }
}
