#ifndef Cell_H
#define Cell_H

#include "EColors.h"
#include <Arduino.h>

typedef struct Piece Piece;

typedef struct
{
    int aX;
    int aY;
    char aLetter;
    char aDigit;
    SColors::EColors aColor;
    Piece* aPiece;
}Cell;

Cell* NewCell(int pX, int pY);
void FreeCell(Cell* vThis);
void mPrintCell(Cell* vThis);

#endif
