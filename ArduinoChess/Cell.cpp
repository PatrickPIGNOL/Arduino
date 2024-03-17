#include "Cell.h"
#include "Piece.h"

Cell* NewCell(int pX, int pY)
{
    Cell* vThis = (Cell*)malloc(sizeof(Cell));
    vThis->aX = pX;
    vThis->aY = pY;
    if((vThis->aX + vThis->aY) % 2 == 0)
    {
        vThis->aColor = SColors::EColors::White;
    }
    else
    {
        vThis->aColor = SColors::EColors::Black;      
    }
    vThis->aLetter = 'a' + vThis->aX;
    vThis->aDigit = '8' - vThis->aY;
    vThis->aPiece = NULL;
    return vThis;
}

void FreeCell(Cell* pThis)
{
  free(pThis);
}

void mPrintCell(Cell* pThis)
{
  if(pThis->aPiece != NULL)
  {
    (pThis->aPiece);
  }
  else
  {
    switch(pThis->aColor)
    {
      case SColors::EColors::White:
      {
          Serial.print("░");
      }break;
      default:
      {                
          Serial.print("▓");
      }break;
    };
  }
}
