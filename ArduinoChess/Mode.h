#ifndef MODE_H
#define MODE_H

typedef enum
{
    ModeSetup,
    PlayerVsPlayer,
    PlayerVsComputer, // Human = White, Computer = Black
    ComputerVsPlayer // Human = Black, Computer = White
}Mode;

#endif
