/* #include "Cell.h"
#include "Piece.h"

void mBuildCell(Cell* this, int pX, int pY)
{
    this->aPiece = NULL;
    this->aX = pX;
    this->aY = pY;
    if((this->aX + this->aY) % 2 == 0)
    {
        this->aColor = EColors::White;
    }
    else
    {
        this->aColor = EColors::Black;      
    }
    this->aLetter = 'a' + this->aX;
    this->aDigit = '8' - this->aY;
}

void mPrintCell(Cell* this)
{
    if(this->aPiece != NULL)
    {
        mPrintPiece(this->aPiece);
    }
    else
    {
        switch(this->aColor)
        {
            case EColors::White:
            {
                Serial.print("░");
            }break;
            default:
            {                
                Serial.print("▓");
            }break;
        };
    }
} */