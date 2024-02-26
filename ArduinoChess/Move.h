#ifndef Move_H
#define Move_H

#include "Cell.h"
#include "EMoveSettings.h"
#include "Piece.h"

typedef struct
{
    Piece* aPiece;
    EMoveSettings aMoveSettings;
    int aXOfset;
    int aYOfset;
    int aCount;
}Move;

#endif