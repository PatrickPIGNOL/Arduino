#ifndef MOVEPROPERTIES_H
#define MOVEPROPERTIES_H

typedef enum
{
    None = 0, // must not be used AKA bug !!!
    CanCapture = 1, // All
    CanJump = 2, // kNight only
    Castle = 4, //King only
    CantBeAttacked = 8, //King
    Jailed = 16, // All
    Line = 32, // Long range pieces (Rook, Bishop, Qween)
    MustCapture = 64, //Pawn
    MustFirstMove = 128, //Pawn's first move / King's castle
    Promote = 256 // Pawn only
    
}MoveProperties;

#endif
