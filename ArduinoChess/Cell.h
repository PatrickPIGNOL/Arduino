#ifndef Cell_H
#define Cell_H

#include "EColors.h"
#include <Arduino.h>
#include "Piece.h"
typedef struct _Cell
{
    int aX;
    int aY;
    char aLetter;
    char aDigit;
    EColors aColor;
    Piece* aPiece;
}Cell;

#endif