#ifndef MOVEPROPERTIES_H
#define MOVEPROPERTIES_H

typedef enum
{
    None = 0, // must not be used AKA bug !!!
    CanCapture = 1,
    CanJump = 2,
    Castle = 4,
    CantBeAttacked = 8,
    Jail = 16,
    Line = 32,
    MustCapture = 64,
    MustFirstMove = 128
}MoveProperties;

#endif
