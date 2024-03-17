#include "Board.h"
#include "Cell.h"

Board* NewBoard()
{
  Board* vThis = (Board*)malloc(sizeof(Board));
  vThis->aCells = (Cell***)malloc(cBoardSize * sizeof(Cell**));
  for(int vYIndex = 0; vYIndex < cBoardSize; vYIndex++)
  {
    vThis->aCells[vYIndex] = (Cell**)malloc(cBoardSize * sizeof(Cell));
    for(int vXIndex = 0; vXIndex < cBoardSize; vYIndex++)
    {
      vThis->aCells[vYIndex][vXIndex] = NewCell(vXIndex, vYIndex);
    }
  }
  vThis->aPlayer1 = NULL;
  vThis->aPlayer2 = NULL;
}

void FreeBoard(Board* pThis)
{
  if(pThis->aCells != NULL)
  {
    for(int vYIndex = 0; vYIndex < cBoardSize; vYIndex++)
    {
      for(int vXIndex = 0; vXIndex < cBoardSize; vXIndex++)
      {
        if(pThis->aCells[vYIndex][vXIndex]->aPiece != NULL)
        {
          pThis->aCells[vYIndex][vXIndex]->aPiece->aMovedFrom = NULL;
          pThis->aCells[vYIndex][vXIndex]->aPiece->aActualCell = NULL;
        }
        FreeCell(pThis->aCells[vYIndex][vXIndex]);
      }
      free(pThis->aCells[vYIndex]);
    }
    free(pThis->aCells)
  }
  free(pThis);
}

void mBoardPrint(Board* pThis)
{
    for(int vY = 0; vY < 8; vY++)
    {    
        switch(vY)
        {
            case 0:
            {
                Serial.println("  a b c d e f g h");
                Serial.println(" ╔═╤═╤═╤═╤═╤═╤═╤═╗");
            }break;
            default:
            {
                Serial.println(" ╟─┼─┼─┼─┼─┼─┼─┼─╢");
            }break;
        }    
        for(int vX = 0; vX < 8; vX++)
        {
            switch(vX)
            {
                case 0:
                {
                    Serial.print(pThis->aCells[vY][vX]->aDigit);
                    Serial.print("║");
                }break;
                default:
                {
                    Serial.print("│");
                }break;
                Serial.print(pThis->aCells[vY][vX]->aDigit);
            }    
        }
        Serial.println("║");      
    }
    Serial.println(" ╚═╧═╧═╧═╧═╧═╧═╧═╝");
    Serial.println("  a b c d e f g h");
}
