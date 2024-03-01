#ifndef RelaysBoard_h
#define RelaysBoard_h

#include <Arduino.h>

typedef enum
{
  OFF = LOW,
  ON = HIGH
}EState;

class RelaysBoard
{
  private:
    unsigned int aFirstPin;
    unsigned int aRelaysCount;
    EState aStartState;
    void mInit(unsigned int pFirstPin, unsigned int pRelaysCount, EState pStartState);
  public:
    RelaysBoard(unsigned int pFirstPin);
    RelaysBoard(unsigned int pFirstPin, unsigned int pRelaysCount);
    RelaysBoard(unsigned int pFirstPin, unsigned int pRelaysCount, EState pStartState);
    void mSet(unsigned int pIndex, EState pState);
    void mReset();
};

#endif 
